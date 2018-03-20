// TestDl.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include "TestDll.h"

namespace Dll
{

// This is an example of an exported variable
TESTDLL_API int nTestDl=0;

// This is an example of an exported function.
TESTDLL_API int fnTestDl(void)
{
	return 42;
}

TESTDLL_API int Add(int a,int b)
{
	return a + b;
}


unsigned char Test_Singcode[]=
{
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39
}; 


TESTDLL_API char* GetSignCode(DWORD* dwLen)
{
	*dwLen = sizeof(Test_Singcode) /sizeof(Test_Singcode[0]);
	return (char*)Test_Singcode;
}

TESTDLL_API void PrintSignCode()
{
	printf("SignCode:%s\n",Test_Singcode);
}


}  // namespace Dll

// This is the constructor of a class that has been exported.
// see TestDl.h for the class definition
CTestDll::CTestDll()
{
	return;
}


