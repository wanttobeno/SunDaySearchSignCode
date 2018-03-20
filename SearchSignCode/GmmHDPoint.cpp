#include "GmmHDPoint.h"


HANDLE g_hVectorHandle;
ULONG  g_NewAddress, g_DetourPoint;


BOOL WINAPI InstallHardHook(ULONG DetourPoint, ULONG NewAddress)
{
	g_hVectorHandle = AddVectoredExceptionHandler(1, (PVECTORED_EXCEPTION_HANDLER)VectoredHandler);	
	return SetHardHook(DetourPoint, NewAddress);
}

BOOL WINAPI SetHardHook(ULONG DetourPoint, ULONG NewAddress)
{
	BOOL bRet;
	HANDLE thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	THREADENTRY32 te;


	te.dwSize = sizeof(THREADENTRY32);

	g_NewAddress = NewAddress;
	g_DetourPoint=DetourPoint;
	Thread32First(thSnap, &te);
	do
	{  
		DWORD dwErrCode;
		if(te.th32OwnerProcessID != GetCurrentProcessId()||
			te.th32ThreadID == GetCurrentThreadId())
			continue;
		HANDLE hThread =  OpenThread(THREAD_SET_CONTEXT|THREAD_GET_CONTEXT|THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
		if (!hThread){
			dwErrCode = GetLastError();
			continue;
		}
		SuspendThread(hThread);
		CONTEXT ctx;
		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
		GetThreadContext(hThread, &ctx);
		if(!ctx.Dr0)
		{
			ctx.Dr0 = MakePtr(UINT, DetourPoint, 0);
			ctx.Dr7 |= 0x00000001;
			bRet = TRUE;
		}
		else if(!ctx.Dr1)
		{
			ctx.Dr1 = MakePtr(UINT, DetourPoint, 0);
			ctx.Dr7 |= 0x00000004;
			bRet = TRUE;
		}
		else if(!ctx.Dr2)
		{
			ctx.Dr2 = MakePtr(UINT, DetourPoint, 0);
			ctx.Dr7 |= 0x00000010;
			bRet = TRUE;
		}
		else if(!ctx.Dr3)
		{
			ctx.Dr3 = MakePtr(UINT, DetourPoint, 0);
			ctx.Dr7 |= 0x00000040;
			bRet = TRUE;
		}
		else
			bRet = FALSE;

		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
		SetThreadContext(hThread, &ctx);
		ResumeThread(hThread);
		CloseHandle(hThread);
	} while(Thread32Next(thSnap, &te));
	return bRet;
}

void WINAPI ClearHardHook()
{
	bool retval=false;
	HANDLE thSnap, hThread;
	THREADENTRY32 te;

	te.dwSize = sizeof(THREADENTRY32);

	thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	Thread32First(thSnap, &te);
	do
	{
		if(te.th32OwnerProcessID != GetCurrentProcessId()|| te.th32ThreadID == GetCurrentThreadId())
			continue;
		hThread = OpenThread(THREAD_SET_CONTEXT|THREAD_GET_CONTEXT|THREAD_SUSPEND_RESUME,  FALSE, te.th32ThreadID);
		if (!hThread)
			continue;
		SuspendThread(hThread);
		CONTEXT ctx;
		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
		GetThreadContext(hThread, &ctx);
		ctx.Dr0 = 0;
		ctx.Dr7 &= 0xFFF0FFFE; // Clear the 16-19th and 1st bits
		ctx.Dr1 = 0;
		ctx.Dr7 &= 0xFF0FFFFB;
		ctx.Dr2 = 0;
		ctx.Dr7 &=0xF0FFFFEF;
		ctx.Dr3 = 0;
		ctx.Dr7 &=0xFFFFFBF;
		SetThreadContext(hThread, &ctx);
		ResumeThread(hThread);
		CloseHandle(hThread);
	} while(Thread32Next(thSnap, &te));

	if (g_hVectorHandle)
	{
		RemoveVectoredExceptionHandler(g_hVectorHandle);
	}

}

long WINAPI VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
	switch(ExceptionInfo->ExceptionRecord->ExceptionCode)
	{
	case EXCEPTION_DEBUG_STRING:
		return EXCEPTION_CONTINUE_EXECUTION;
	case EXCEPTION_SINGLE_STEP:
		{
			if(ExceptionInfo->ContextRecord->Eip != MakePtr(UINT, g_DetourPoint, 0))
				return EXCEPTION_CONTINUE_SEARCH;
			ExceptionInfo->ContextRecord->Eip = MakePtr(UINT, g_NewAddress, 0);
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		break;
	default:
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

