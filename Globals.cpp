// stdafx.cpp : source file that includes just the standard includes
//  Visualizer.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "Globals.h"
#include "..\Analyzed\Analyzed_i.c"

VOID SetThreadName(LPCSTR szThreadName )
{
	THREADNAMEINFO info;
	info.dwType = 0x1000;
	info.szName = szThreadName;
	info.dwThreadID = -1;
	info.dwFlags = 0;

	__try
	{
		RaiseException(0x406D1388,0,sizeof(info)/sizeof(DWORD),(LPDWORD)&info);
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}
