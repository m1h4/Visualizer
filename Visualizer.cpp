#include "Globals.h"
#include "Visualizer.h"
#include "Visualizer_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisualizerApp NEAR theApp;

// CVisualizerApp::InitInstance - DLL initialization

BOOL CVisualizerApp::InitInstance()
{
	return COleControlModule::InitInstance();
}

// CVisualizerApp::ExitInstance - DLL termination

INT CVisualizerApp::ExitInstance()
{
	return COleControlModule::ExitInstance();
}

// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if(!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), LIBID_Visualizer))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if(!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}

// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if(!AfxOleUnregisterTypeLib(LIBID_Analyzed, 1, 0))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if(!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}