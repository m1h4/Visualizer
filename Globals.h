#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0400	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Comon Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define _USE_MATH_DEFINES
#include <math.h>

#define SAFEDELETE(ptr) { if(ptr) { delete ptr; ptr = NULL; } }
#define SAFERELEASE(ptr) { if(ptr) { ptr->Release(); ptr = NULL; } }

#include "..\Analyzed\Analyzed.h"
#include "..\Analyzed\Effects.h"

#pragma comment (lib, "dxguid.lib")		/* link with DirectX GUID lib */

// Debug help function for assigning a name to a thread
typedef struct
{
	DWORD dwType;		// Must be 0x1000
	LPCSTR szName;		// Pointer to name (in user address space)
	DWORD dwThreadID;	// Thread ID (-1 = caller thread)
	DWORD dwFlags;		// Reserved for future use, must be zero
} THREADNAMEINFO,*LPTHREADNAMEINFO;

VOID SetThreadName(LPCSTR szThreadName);

#ifdef _DEBUG
#define SETTHREADNAME SetThreadName
#else
#define SETTHREADNAME __noop
#endif