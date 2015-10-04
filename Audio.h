#pragma once

#include <mmsystem.h>
#include <dsound.h>

#define AUDIO_FFTBUFFERSIZE 4096
#define AUDIO_CHANNELS 2
#define AUDIO_FREQUENCY 44100
#define AUDIO_BITS 16
#define AUDIO_BUFFERSIZE 16384

#define ENTER_SECTION(dest) CCriticalSection criticalSection(*dest)

class CThreaded
{
public:
	CThreaded(void) { InitializeCriticalSection(&m_Section); }
	virtual ~CThreaded(void) { DeleteCriticalSection(&m_Section); }

	void EnterSection(void) { EnterCriticalSection(&m_Section); }
	void LeaveSection(void) { LeaveCriticalSection(&m_Section); }

protected:
	CRITICAL_SECTION m_Section;
};

class CCriticalSection
{
public:
	CCriticalSection(CThreaded& threaded) : m_Threaded(threaded) { m_Threaded.EnterSection(); }
	~CCriticalSection(void) { m_Threaded.LeaveSection(); }

protected:
	CThreaded&	m_Threaded;
};

class CAudio : public CThreaded
{
public:
	CAudio(void);
	~CAudio(void);

	HRESULT Initialize(void);
	HRESULT Uninitialize(void);

	HRESULT InitializeCapture(IAnalyzed* analyzed);
	HRESULT UninitializeCapture(void);

	HRESULT	Update(void);

	HRESULT	StartCapture(void);
	HRESULT	StopCapture(void);

	HRESULT	Capture(short* buffer, unsigned long bufferSize);

	VOID	GetSeperateChannels(double* left, double* right,const short* buffer,unsigned long bufferSize);

	VOID	GetPowerSpectrum(double* ps,const double* data,unsigned long size);
	VOID	GetScope(double* scope,const double* data,unsigned long size);

	DOUBLE	GetMagnitude(double level,double cutrange,double sharpness,unsigned long x,unsigned long size);

	DOUBLE	GetBlackmanHarrisWindow(unsigned long x,unsigned long size);

	DOUBLE	GetPowerSpectrum(unsigned char channel,unsigned long index) const { return m_PowerSpectrum[channel][index]; }
	DOUBLE	GetScope(unsigned char channel,unsigned long index) const { return m_Scope[channel][index]; }

protected:
	LPDIRECTSOUNDCAPTURE8		m_SoundCapture;	// Our sound capture interface
	LPDIRECTSOUNDCAPTUREBUFFER	m_CaptureBuffer;	// Our sound capture buffer

	DOUBLE	m_PowerSpectrum[2][AUDIO_FFTBUFFERSIZE/4 - 1];	// Our main buffer for the power spectrum
	DOUBLE	m_Scope[2][AUDIO_FFTBUFFERSIZE/2];				// Our scope buffer

	HANDLE	m_Capture;
	ULONG	m_CaptureId;

	HMODULE	m_DS;

	IAnalyzed*	m_Analyzed;
};

DWORD WINAPI CaptureThread(CAudio* audio);