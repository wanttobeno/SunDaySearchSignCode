// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TESTDL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TESTDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTDL_EXPORTS
#define TESTDLL_API __declspec(dllexport)
#else
#define TESTDLL_API __declspec(dllimport)
#endif

// This class is exported from the TestDl.dll
class TESTDLL_API CTestDll {
public:
	CTestDll(void);
	// TODO: add your methods here.
};


namespace Dll
{
	extern TESTDLL_API int nTestDl;

	TESTDLL_API int fnTestDl(void);


	extern TESTDLL_API int Add(int a,int b);

	extern TESTDLL_API char* GetSignCode(DWORD* dwLen);

	extern TESTDLL_API void PrintSignCode();
}  //namespace Dll


