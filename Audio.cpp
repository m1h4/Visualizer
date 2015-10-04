#include "Globals.h"
#include "Audio.h"

#include "fftsg.h"

typedef HRESULT (WINAPI * LPDIRECTSOUNDCAPTURECREATE8) (LPCGUID,LPDIRECTSOUNDCAPTURE8*,LPUNKNOWN);

#define DSDLL "dsound.dll"

CAudio::CAudio() :
m_SoundCapture(NULL),
m_CaptureBuffer(NULL),
m_Capture(NULL),
m_CaptureId(NULL),
m_DS(NULL)
{
	ZeroMemory(m_PowerSpectrum,sizeof(m_PowerSpectrum));
    ZeroMemory(m_Scope,sizeof(m_Scope));
}

CAudio::~CAudio(void)
{
	Uninitialize();
}

HRESULT CAudio::Initialize(void)
{
	ENTER_SECTION(this);

	m_DS = LoadLibrary(DSDLL);
	if(!m_DS)
	{
		TRACE("Failed to load \"%s\".\n",DSDLL);
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CAudio::InitializeCapture(IAnalyzed* analyzed)
{
	ENTER_SECTION(this);

	m_Analyzed = analyzed;

	// Get the address of the create function
	LPDIRECTSOUNDCAPTURECREATE8 DirectSoundCaptureCreate8 = (LPDIRECTSOUNDCAPTURECREATE8)GetProcAddress(m_DS,"DirectSoundCaptureCreate8");
	if(!DirectSoundCaptureCreate8)
	{
		TRACE("Failed to find \"DirectSoundCaptureCreate8\" in \"%s\".\n",DSDLL);
		return E_FAIL;
	}

	// Create our main capture object
	HRESULT hr = DirectSoundCaptureCreate8(&DSDEVID_DefaultCapture, &m_SoundCapture, NULL);
	if(FAILED(hr))
	{
		TRACE("Failed to load create direct sound capture.\n",DSDLL);
		return E_FAIL;
	}

	// Create the wave format description
	WAVEFORMATEX waveform;
	ZeroMemory(&waveform,sizeof(waveform));
	waveform.cbSize = sizeof(waveform);
	waveform.nChannels = AUDIO_CHANNELS;
	waveform.nSamplesPerSec = AUDIO_FREQUENCY;
	waveform.wBitsPerSample = AUDIO_BITS;
	waveform.nBlockAlign = (waveform.nChannels * waveform.wBitsPerSample) / 8;
	waveform.nAvgBytesPerSec = waveform.nSamplesPerSec * waveform.nBlockAlign;
	waveform.wFormatTag = WAVE_FORMAT_PCM;

	// Create the record buffer format description
	DSCBUFFERDESC bufferdesc;
	ZeroMemory(&bufferdesc,sizeof(bufferdesc));
	bufferdesc.dwSize = sizeof(bufferdesc);
	bufferdesc.dwFlags = 0;
	bufferdesc.dwBufferBytes = AUDIO_BUFFERSIZE;
	bufferdesc.dwFXCount = 0;
	bufferdesc.lpDSCFXDesc = 0;
	bufferdesc.lpwfxFormat = &waveform;

	// Create the capture buffer
	hr = m_SoundCapture->CreateCaptureBuffer(&bufferdesc, &m_CaptureBuffer, NULL);
	if(FAILED(hr))
	{
		TRACE("Failed to create direct sound capture buffer.");
		return E_FAIL;
	}

	if(FAILED(StartCapture()))
	{
		TRACE("Failed to start capture.\n");
		return E_FAIL;
	}

	// Create the renderer thread
	m_Capture = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)CaptureThread,this,NULL,&m_CaptureId);
	if(!m_Capture)
		return E_FAIL;

	return S_OK;
}

HRESULT CAudio::UninitializeCapture(void)
{
	ENTER_SECTION(this);

	StopCapture();

	// Check if uninitialized
	if(!m_Capture)
		return S_FALSE;

	// Tell the thread to close
	PostThreadMessage(m_CaptureId,WM_QUIT,NULL,NULL);

	if(WaitForSingleObject(m_Capture,2000) == WAIT_TIMEOUT)
		TerminateThread(m_Capture,0x000000FF);

	CloseHandle(m_Capture);
	m_Capture = NULL;
	m_CaptureId = NULL;

	SAFERELEASE(m_CaptureBuffer);
	SAFERELEASE(m_SoundCapture);

	return S_OK;
}

HRESULT CAudio::Uninitialize(void)
{
	ENTER_SECTION(this);

	FreeLibrary(m_DS);
	m_DS = NULL;

	return S_OK;
}

HRESULT CAudio::Update(void)
{
	ENTER_SECTION(this);

	// Our buffers
	static short fft_buffer[AUDIO_FFTBUFFERSIZE];

	static double fft_in_left[AUDIO_FFTBUFFERSIZE/2];
	static double fft_in_right[AUDIO_FFTBUFFERSIZE/2];

	static double fft_out_left[AUDIO_FFTBUFFERSIZE/2];
	static double fft_out_right[AUDIO_FFTBUFFERSIZE/2];

	static double fft_work_left[AUDIO_FFTBUFFERSIZE/4];
	static double fft_work_right[AUDIO_FFTBUFFERSIZE/4];

	static int ip1[18] = {0};
	static int ip2[18] = {0};

	ZeroMemory(fft_buffer,sizeof(fft_buffer));

	// Capture the audio data into the main buffer
	if(FAILED(Capture(fft_buffer,sizeof(fft_buffer))))
		return E_FAIL;

	// Volume magnifier
	for(unsigned long i = 0; i < AUDIO_FFTBUFFERSIZE; ++i)
		fft_buffer[i] = (unsigned short)(fft_buffer[i] * 1.0001);

	// Seperate the main buffer into the left and right chanels
	GetSeperateChannels(fft_in_left,fft_in_right,fft_buffer,AUDIO_FFTBUFFERSIZE);

	// Copy the input data to the input-output buffer
	CopyMemory(fft_out_left,fft_in_left,sizeof(fft_out_left));
	CopyMemory(fft_out_right,fft_in_right,sizeof(fft_out_right));

	// Use the Blackman-Harris window
	for(unsigned long i = 0; i < AUDIO_FFTBUFFERSIZE/2; ++i)
	{
		double mag = GetBlackmanHarrisWindow(i,AUDIO_FFTBUFFERSIZE/2);

		fft_out_left[i] *= mag;
		fft_out_right[i] *= mag;
	}

	// Calculate the Real Discrete Fourier Transform
	rdft(AUDIO_FFTBUFFERSIZE/2, 1, fft_out_left, ip1, fft_work_left);
	rdft(AUDIO_FFTBUFFERSIZE/2, 1, fft_out_right, ip2, fft_work_right);

	// Calculate the Power Spectrum by suming the square of the real and the square of the imaginary part
	for(unsigned long i = 0; i < AUDIO_FFTBUFFERSIZE/4 - 1; ++i)
	{
		static const double magScale = 4000;
		static const int yScale = 1000;

		fft_out_left[i] = -sqrt(fft_out_left[i*2] * fft_out_left[i*2] + fft_out_left[i*2+1] * fft_out_left[i*2+1]) / (AUDIO_FFTBUFFERSIZE/4 - 1) / (magScale / yScale);
		fft_out_right[i] = -sqrt(fft_out_right[i*2] * fft_out_right[i*2] + fft_out_right[i*2+1] * fft_out_right[i*2+1]) / (AUDIO_FFTBUFFERSIZE/4 - 1) / (magScale / yScale);
	}

	// Calc the power spectrum array
	GetPowerSpectrum(m_PowerSpectrum[0],fft_out_left,AUDIO_FFTBUFFERSIZE/4 - 1);
	GetPowerSpectrum(m_PowerSpectrum[1],fft_out_right,AUDIO_FFTBUFFERSIZE/4 - 1);

	// Calc the average of the left and right channel for our scope
	GetScope(m_Scope[0],fft_in_left,AUDIO_FFTBUFFERSIZE/2);
	GetScope(m_Scope[1],fft_in_right,AUDIO_FFTBUFFERSIZE/2);

	TIMEDLEVEL levels;

	ZeroMemory(&levels,sizeof(levels));

	levels.state = play_state;

	for(unsigned int i = 0; i < AUDIO_FFTBUFFERSIZE/4 - 1; ++i)
	{
		levels.frequency[0][i] = (unsigned char)(m_PowerSpectrum[0][i] / -1.5);
		levels.frequency[1][i] = (unsigned char)(m_PowerSpectrum[1][i] / -1.5);
	}

	for(unsigned int i = 0; i < AUDIO_FFTBUFFERSIZE/4; ++i)
	{
		levels.waveform[0][i] = (unsigned char)((m_Scope[0][i*2] + m_Scope[0][i*2+1])/2.0);
		levels.waveform[1][i] = (unsigned char)((m_Scope[1][i*2] + m_Scope[1][i*2+1])/2.0);
	}

	m_Analyzed->Update((OLE_HANDLE)&levels);

	return S_OK;
}

HRESULT CAudio::Capture(short* buffer, unsigned long bufferSize)
{
	ENTER_SECTION(this);

	unsigned long readCursor, lockOffset;
	void* firstBuf, *secondBuf;
	unsigned long firstLen, secondLen;

	// Get the position of the read cursor in the capture buffer
	// We can read everything up to this point (and not including it)
	m_CaptureBuffer->GetCurrentPosition(NULL, &readCursor);

	// Calculate a starting point in the buffer behind the read cursor to lock at
	if(readCursor < bufferSize)
		lockOffset = AUDIO_BUFFERSIZE - readCursor - bufferSize;
	else
		lockOffset = readCursor - bufferSize;

	// Ovak je bilo prije :		KRIVO!
	// lockOffset = readCursor - bufferSize;

	// if(readCursor < bufferSize)
	//	lockOffset = SETTINGS_BUFFERSIZE + lockOffset;

	// Lock the capture buffer and grab some data, ah yeah!
	if(FAILED(m_CaptureBuffer->Lock(lockOffset, bufferSize, &firstBuf, &firstLen, &secondBuf, &secondLen, 0)))
	{
		TRACE("IDirectSoundCaptureBuffer8::Lock() failed! lockOffset=%d readCursor=%d\n",lockOffset,readCursor);
		return E_FAIL;
	}

	// Copy the data out of the first buffer
	if(firstLen)
		memcpy(buffer, firstBuf, firstLen);

	// Is there more (wrapped) data to copy?  If so, append it to the first chunk of copied data
	if(secondLen)
		memcpy(buffer + firstLen, secondBuf, secondLen);

	// Unlock the buffer
	if(FAILED(m_CaptureBuffer->Unlock(firstBuf, firstLen, secondBuf, secondLen)))
	{
		TRACE("IDirectSoundCaptureBuffer8::Unlock() failed!\n");
		return E_FAIL;
	}

	return S_OK;
}

void CAudio::GetPowerSpectrum(double* ps,const double* data,unsigned long size)
{
	ENTER_SECTION(this);

	// Just lerp-copy the array
	for(unsigned long x = 0; x < size; ++x)
	{
		// Get magnitude of this band
		double mag = GetMagnitude(-data[x],1.35,2.0,x,size);

		// We put - so we get bands jumpung up instead of down
		ps[x] = -max(140.0 * mag,0.0);
	}
}

void CAudio::GetScope(double* scope,const double* data,unsigned long size)
{
	ENTER_SECTION(this);

	// Calc the level of the scope line
	for(unsigned long x = 0; x < size; ++x)
		scope[x] = data[x] / 200.0f;
}

void CAudio::GetSeperateChannels(double* left, double* right,const short* buffer,unsigned long bufferSize)
{
	// Seperate the left chanel from the main buffer
	for(unsigned long i = 0, j = 0; i < bufferSize; i += 2, ++j)
		left[j] = (double)buffer[i];

	// Seperate the right chanel from the main buffer
	for(unsigned long i = 1, j = 0; i < bufferSize; i += 2, ++j)
		right[j] = (double)buffer[i];
}

double CAudio::GetBlackmanHarrisWindow(unsigned long x,unsigned long size)
{
	ENTER_SECTION(this);

	static const double a0 = 0.35875;
	static const double a1 = 0.48829;
	static const double a2 = 0.14128;
	static const double a3 = 0.01168;
	static const double twopi = M_PI * 2.0;
	static const double fourpi = M_PI * 4.0;
	static const double sixpi = M_PI * 6.0;

	return a0 - a1 * cos(twopi * (double)(x + 0.5) / (double)(size)) +
			a2 * cos(fourpi * (double)(x + 0.5) / (double)(size)) - 
			a3 * cos(sixpi * (double)(x + 0.5) / (double)(size));
}

double CAudio::GetMagnitude(double level,double cutrange,double sharpness,unsigned long x,unsigned long size)
{
	ENTER_SECTION(this);

	double powerbase = log10(1.0 + cutrange) / pow((double)size - 1.0,sharpness);
	double power = pow(10.0,powerbase);

	// Compute how much to clip this band and clip it
	return log10(level) - pow(power,pow((double)size - 1.0 - (double)x,sharpness)) + 1.0;
}

HRESULT CAudio::StartCapture()
{
	ENTER_SECTION(this);

	if(FAILED(m_CaptureBuffer->Start(DSCBSTART_LOOPING)))
	{
		TRACE("Failed to start sound capture.\n");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CAudio::StopCapture()
{
	ENTER_SECTION(this);

	if(FAILED(m_CaptureBuffer->Stop()))
	{
		TRACE("Failed to stop sound capture.\n");
		return E_FAIL;
	}

	return S_OK;
}

DWORD WINAPI CaptureThread(CAudio* audio)
{
	// This should be done automatically but it somehow isn't
	SETTHREADNAME(__FUNCTION__);

	MSG msg;
	ZeroMemory(&msg,sizeof(msg));

	SetTimer(NULL,NULL,20,NULL);

	while(GetMessage(&msg,NULL,NULL,NULL) > 0)
	{
		if(msg.message == WM_QUIT)
			break;

		if(msg.message != WM_TIMER)
			TRACE(TEXT("Warning: Got non-timer message: %d\n"),msg.message);

		// Capture the audio
		audio->Update();
	}

	KillTimer(NULL,NULL);

	return 0x0000000;
}