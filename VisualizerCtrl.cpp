#include "Globals.h"
#include "Visualizer.h"
#include "VisualizerCtrl.h"
#include "VisualizerPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CVisualizerCtrl, COleControl)

// Message map

BEGIN_MESSAGE_MAP(CVisualizerCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// Dispatch map

BEGIN_DISPATCH_MAP(CVisualizerCtrl, COleControl)
	DISP_FUNCTION_ID(CVisualizerCtrl, "Initialize", 1L, Initialize, VT_BOOL, VTS_I4 VTS_BOOL)
	DISP_FUNCTION_ID(CVisualizerCtrl, "Uninitialize", 2L, Uninitialize, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "SetVisualization", 3L, SetVisualization, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetVisualizationCount", 4L, GetVisualizationCount, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetVisualizationName", 5L, GetVisualizationName, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetVisualization", 6L, GetVisualization, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "PackColor", 7L, PackColor, VT_I4, VTS_UI1 VTS_UI1 VTS_UI1 VTS_UI1)
	DISP_FUNCTION_ID(CVisualizerCtrl, "UnpackColorAlpha", 8L, UnpackColorAlpha, VT_UI1, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "UnpackColorRed", 9L, UnpackColorRed, VT_UI1, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "UnpackColorGreen", 10L, UnpackColorGreen, VT_UI1, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "UnpackColorBlue", 11L, UnpackColorBlue, VT_UI1, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetColorBackground", 12L, GetColorBackground, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "SetColorBackground", 13L, SetColorBackground, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetColorTop", 14L, GetColorTop, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "SetColorTop", 15L, SetColorTop, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetColorTopEnd", 16L, GetColorTopEnd, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "SetColorTopEnd", 17L, SetColorTopEnd, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetColorBottom", 18L, GetColorBottom, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "SetColorBottom", 19L, SetColorBottom, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetColorBottomEnd", 20L, GetColorBottomEnd, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "SetColorBottomEnd", 21L, SetColorBottomEnd, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(CVisualizerCtrl, "GetColorPeak", 22L, GetColorPeak, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CVisualizerCtrl, "SetColorPeak", 23L, SetColorPeak, VT_BOOL, VTS_I4)
END_DISPATCH_MAP()

// Event map

BEGIN_EVENT_MAP(CVisualizerCtrl, COleControl)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CVisualizerCtrl, 1)
	PROPPAGEID(CVisualizerPropPage::guid)
END_PROPPAGEIDS(CVisualizerCtrl)

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVisualizerCtrl, "MIHASOFTWARE.VisualizerCtrl.1",
	0x6f398387, 0xa0b, 0x42f0, 0xa4, 0xe0, 0xbc, 0xaf, 0x9e, 0xc8, 0x8d, 0xe5)

// Type library ID and version

IMPLEMENT_OLETYPELIB(CVisualizerCtrl, LIBID_Analyzed, 1, 0)

// Interface IDs

const IID BASED_CODE IID_DVisualizer =
		{ 0x825A1EE0, 0x97B6, 0x4EF2, { 0xAE, 0x7C, 0x54, 0x91, 0x64, 0x9E, 0xAD, 0x16 } };
const IID BASED_CODE IID_DVisualizerEvents =
		{ 0x96A638C5, 0xD627, 0x4D5F, { 0x96, 0xF3, 0xCD, 0x45, 0x77, 0x73, 0xCC, 0x42 } };

// Control type information

static const DWORD BASED_CODE _dwVisualizerOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CVisualizerCtrl, IDS_VISUALIZER, _dwVisualizerOleMisc)

// CVisualizerCtrl::CVisualizerCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CVisualizerCtrl

BOOL CVisualizerCtrl::CVisualizerCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_VISUALIZER,
			IDB_VISUALIZER,
			afxRegApartmentThreading,
			_dwVisualizerOleMisc,
			LIBID_Analyzed,
			1,
			0);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

// CVisualizerCtrl::CVisualizerCtrl - Constructor

CVisualizerCtrl::CVisualizerCtrl() :
m_Analyzed(NULL)
{
	InitializeIIDs(&IID_DVisualizer, &IID_DVisualizerEvents);
	// TODO: Initialize your control's instance data here.
}

// CVisualizerCtrl::~CVisualizerCtrl - Destructor

CVisualizerCtrl::~CVisualizerCtrl()
{
	// TODO: Cleanup your control's instance data here.
	Uninitialize();
}

// CVisualizerCtrl::OnDraw - Drawing function

void CVisualizerCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if(!pdc)
		return;

	if(m_Analyzed)
		return;

	DeleteObject(pdc->SelectObject(GetStockObject(DEFAULT_GUI_FONT)));

	pdc->FillRect(rcBounds,&CBrush(GetSysColor(COLOR_3DFACE)));

	TCHAR string[256] = "Marko Mihovilic Visualizer is not initialized";

	pdc->SetBkMode(TRANSPARENT);
	pdc->DrawText(string,(LPRECT)&rcBounds,DT_CENTER|DT_SINGLELINE|DT_VCENTER);

	pdc->MoveTo(0,5);
	pdc->LineTo(0,0);
	pdc->LineTo(5,0);

	pdc->MoveTo(rcBounds.right-1-5,0);
	pdc->LineTo(rcBounds.right-1,0);
	pdc->LineTo(rcBounds.right-1,5);

	pdc->MoveTo(rcBounds.right-1-5,rcBounds.bottom-1);
	pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1);
	pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1-5);

	pdc->MoveTo(0,rcBounds.bottom-1-5);
	pdc->LineTo(0,rcBounds.bottom-1);
	pdc->LineTo(5,rcBounds.bottom-1);
}



// CVisualizerCtrl::DoPropExchange - Persistence support

void CVisualizerCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(1, 0));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}

// CVisualizerCtrl::OnResetState - Reset control to default state

void CVisualizerCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}

VARIANT_BOOL CVisualizerCtrl::Initialize(LONG resolution,VARIANT_BOOL blur)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_Analyzed)
		return VARIANT_TRUE;
	
	if(FAILED(m_Analyzed.CoCreateInstance(CLSID_AnalyzedImplementation)))
	{
		TRACE(TEXT("Failed to cocreate instance.\n"));
		return VARIANT_FALSE;
	}

	if(FAILED(m_Analyzed->Initialize(GetHwnd(),resolution,blur)))
	{
		TRACE(TEXT("Failed to analyzer initialize.\n"));
		m_Analyzed.Release();
		m_Analyzed = NULL;
		return VARIANT_FALSE;
	}

	if(FAILED(m_Audio.Initialize()))
	{
		TRACE(TEXT("Failed to autdio initialize.\n"));
		m_Analyzed.Release();
		m_Analyzed = NULL;
		return VARIANT_FALSE;
	}

	if(FAILED(m_Audio.InitializeCapture(m_Analyzed)))
	{
		TRACE(TEXT("Failed to audio initialize capture.\n"));
		m_Analyzed.Release();
		m_Analyzed = NULL;
		return VARIANT_FALSE;
	}

	m_Audio.Update();

	return VARIANT_TRUE;
}

VARIANT_BOOL CVisualizerCtrl::Uninitialize(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
		return VARIANT_TRUE;

	m_Audio.UninitializeCapture();
	m_Audio.Uninitialize();

	m_Analyzed->Uninitialize();

	m_Analyzed.Release();
	m_Analyzed = NULL;

	InvalidateControl();

	return VARIANT_TRUE;
}

VARIANT_BOOL CVisualizerCtrl::SetVisualization(LONG index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return VARIANT_FALSE;
	}

	if(FAILED(m_Analyzed->SetVisualization(index)))
	{
		TRACE(TEXT("Failed to set visualization.\n"));
		return VARIANT_FALSE;
	}

	return VARIANT_TRUE;
}

LONG CVisualizerCtrl::GetVisualizationCount(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG count = 0;

	if(FAILED(m_Analyzed->GetVisualizationCount(&count)))
	{
		TRACE(TEXT("Failed to get visualization count.\n"));
		return count;
	}

	return count;
}

BSTR CVisualizerCtrl::GetVisualizationName(LONG index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CComBSTR strResult;

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return strResult.Detach();
	}

	if(FAILED(m_Analyzed->GetVisualizationName(&strResult,index)))
	{
		TRACE(TEXT("Failed to get visualization name.\n"));
		return strResult.Detach();
	}

	return strResult.Detach();
}

LONG CVisualizerCtrl::GetVisualization(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG index = 0xFFFFFFFF;

	if(FAILED(m_Analyzed->GetVisualization(&index)))
	{
		TRACE(TEXT("Failed to get visualization index.\n"));
		return 0xFFFFFFFF;
	}

	return index;
}

LONG CVisualizerCtrl::PackColor(BYTE alpha, BYTE red, BYTE green, BYTE blue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (alpha & 0xFF) << 24 | (red & 0xFF) << 16  | (green & 0xFF) << 8 | (blue & 0xFF);
}

BYTE CVisualizerCtrl::UnpackColorAlpha(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (BYTE)(color >> 24);
}

BYTE CVisualizerCtrl::UnpackColorRed(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (BYTE)(color >> 16 & 0xFF);
}

BYTE CVisualizerCtrl::UnpackColorGreen(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (BYTE)(color >> 8 & 0xFF);
}

BYTE CVisualizerCtrl::UnpackColorBlue(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (BYTE)(color & 0xFF);
}

LONG CVisualizerCtrl::GetColorBackground(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG color = 0;

	if(FAILED(m_Analyzed->GetColorBackground(&color)))
	{
		TRACE(TEXT("Failed to get color.\n"));
		return color;
	}

	return color;
}

VARIANT_BOOL CVisualizerCtrl::SetColorBackground(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return VARIANT_FALSE;
	}

	return SUCCEEDED(m_Analyzed->SetColorBackground(color)) ? VARIANT_TRUE : VARIANT_FALSE;
}

LONG CVisualizerCtrl::GetColorTop(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG color = 0;

	if(FAILED(m_Analyzed->GetColorTop(&color)))
	{
		TRACE(TEXT("Failed to get color.\n"));
		return color;
	}

	return color;
}

VARIANT_BOOL CVisualizerCtrl::SetColorTop(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return VARIANT_FALSE;
	}

	return SUCCEEDED(m_Analyzed->SetColorTop(color)) ? VARIANT_TRUE : VARIANT_FALSE;
}

LONG CVisualizerCtrl::GetColorTopEnd(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG color = 0;

	if(FAILED(m_Analyzed->GetColorTopEnd(&color)))
	{
		TRACE(TEXT("Failed to get color.\n"));
		return color;
	}

	return color;
}

VARIANT_BOOL CVisualizerCtrl::SetColorTopEnd(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return VARIANT_FALSE;
	}

	return SUCCEEDED(m_Analyzed->SetColorTopEnd(color)) ? VARIANT_TRUE : VARIANT_FALSE;
}

LONG CVisualizerCtrl::GetColorBottom(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG color = 0;

	if(FAILED(m_Analyzed->GetColorBottom(&color)))
	{
		TRACE(TEXT("Failed to get color.\n"));
		return color;
	}

	return color;
}

VARIANT_BOOL CVisualizerCtrl::SetColorBottom(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return VARIANT_FALSE;
	}

	return SUCCEEDED(m_Analyzed->SetColorBottom(color)) ? VARIANT_TRUE : VARIANT_FALSE;
}

LONG CVisualizerCtrl::GetColorBottomEnd(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG color = 0;

	if(FAILED(m_Analyzed->GetColorBottomEnd(&color)))
	{
		TRACE(TEXT("Failed to get color.\n"));
		return color;
	}

	return color;
}

VARIANT_BOOL CVisualizerCtrl::SetColorBottomEnd(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return VARIANT_FALSE;
	}

	return SUCCEEDED(m_Analyzed->SetColorBottomEnd(color)) ? VARIANT_TRUE : VARIANT_FALSE;
}

LONG CVisualizerCtrl::GetColorPeak(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return 0;
	}

	LONG color = 0;

	if(FAILED(m_Analyzed->GetColorPeak(&color)))
	{
		TRACE(TEXT("Failed to get color.\n"));
		return color;
	}

	return color;
}

VARIANT_BOOL CVisualizerCtrl::SetColorPeak(LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_Analyzed)
	{
		TRACE(TEXT("Analyzer interface is null.\n"));
		return VARIANT_FALSE;
	}

	return SUCCEEDED(m_Analyzed->SetColorPeak(color)) ? VARIANT_TRUE : VARIANT_FALSE;
}