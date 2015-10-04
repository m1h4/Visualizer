#include "Globals.h"
#include "Visualizer.h"
#include "VisualizerPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CVisualizerPropPage, COlePropertyPage)

// Message map

BEGIN_MESSAGE_MAP(CVisualizerPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVisualizerPropPage, "MIHASOFTWARE.VisualizerPropPage.1", 0xed41b0fe, 0x4503, 0x4ea1, 0xb6, 0x19, 0xed, 0x64, 0x22, 0xbe, 0xb3, 0xa3)

// CVisualizerPropPage::CVisualizerPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CVisualizerPropPage

BOOL CVisualizerPropPage::CVisualizerPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if(bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),m_clsid, IDS_VISUALIZER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CVisualizerPropPage::CVisualizerPropPage - Constructor

CVisualizerPropPage::CVisualizerPropPage() :
	COlePropertyPage(IDD, IDS_VISUALIZER_PPG_CAPTION)
{
}

// CVisualizerPropPage::DoDataExchange - Moves data between page and properties

void CVisualizerPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CVisualizerPropPage message handlers