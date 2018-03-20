#pragma once
#include <windows.h>
#include <STDIO.H>
#include <TLHELP32.H>


BOOL WINAPI InstallHardHook(ULONG DetourPoint, ULONG NewAddress);
BOOL WINAPI SetHardHook(ULONG DetourPoint, ULONG NewAddress);
long WINAPI VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo);


#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD_PTR)(ptr) + (DWORD_PTR)(addValue))
#define MakeDelta(cast, x, y) (cast) ( (DWORD_PTR)(x) - (DWORD_PTR)(y))
#define EXCEPTION_DEBUG_STRING 0x40010006


extern HANDLE g_hVectorHandle;
extern ULONG  g_NewAddress, g_DetourPoint;
typedef long LONG_PTR;
typedef unsigned long ULONG_PTR;
typedef ULONG_PTR DWORD_PTR;