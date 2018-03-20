
#include <stdio.h>
#include "GmmEm.h"
#include "GmmHDPoint.h"

// TestDll
#define TESTDL_EXPORTS
#include "../TestDll/TestDll.h"
#ifdef _DEBUG
#pragma  comment(lib,"../Debug/TestDll.lib")
#else
#pragma  comment(lib,"../Release/TestDll.lib")
#endif // _DEBUG

unsigned char Test_Singcode[]=
{
	0x6A, 0x03, 0x53, 0x6A, 0x08, 0x6A, 0x06
}; 

int main(int agrc,char** agrv)
{
	DWORD dwLen = 0;
	char * dllSignCode = Dll::GetSignCode(&dwLen);	
	// 搜索dll
	DWORD dwRetAddr1 = ModuleSignCodeEngine("TestDll.dll",dllSignCode,dwLen);
	if (dwRetAddr1)
	{
		printf("Find SignCode at 0x%X\n",dwRetAddr1);
		Dll::PrintSignCode();
		// 修改数据
		printf("Change the data\n");
		memcpy((void*)dwRetAddr1,Test_Singcode,sizeof(Test_Singcode)/sizeof(Test_Singcode[0]));	
		Dll::PrintSignCode();
	}
	printf("\n");
	// 搜索程序
	DWORD dwRetAddr2 = SignCodeEngine("GmmTest.exe",(char*)Test_Singcode,sizeof(Test_Singcode)/sizeof(Test_Singcode[0]));
	if (dwRetAddr1)
		printf("Find SignCode at 0x%X: %s\n",dwRetAddr2,(char*)dwRetAddr2);

	getchar();
	return 0;
}