#include <windows.h>
#include <stdio.h>
#include <Winbase.h>
#include  <Tlhelp32.h>


BOOL FindModule(DWORD pid,char *sz_Module,DWORD *pBase,DWORD *dwSize)     
{      
	bool bRet = false;
	HANDLE hSnapshot= NULL;      
	MODULEENTRY32 Module;          
	BOOL ret;      
	hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pid);      
	if (hSnapshot)
	{
		Module.dwSize = sizeof(MODULEENTRY32);      
		ret = Module32First(hSnapshot,&Module);     
		while(ret)     
		{         
			if (stricmp(Module.szModule,sz_Module)==0)
			{
				*(DWORD *)pBase=(DWORD)Module.modBaseAddr;
				*(DWORD *)dwSize=Module.modBaseSize;
				bRet = true;
				break;
			}
			ret = Module32Next(hSnapshot,&Module);     
		}     
		CloseHandle(hSnapshot);    
		return bRet;   
	}
	else
		return FALSE;
}



BOOL GetModuleInfo(DWORD dwPID,char *sz_Module,DWORD *pBase,DWORD *dwSize)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	
	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID );
	if( hModuleSnap == INVALID_HANDLE_VALUE )
	{
		return( FALSE );
	}
	me32.dwSize = sizeof( MODULEENTRY32 );
	if( !Module32First( hModuleSnap, &me32 ) )
	{
		CloseHandle( hModuleSnap );           
		return( FALSE );
	}
	do
	{
		if (dwPID==me32.th32ProcessID)
		{
			*(DWORD *)pBase=(DWORD)me32.modBaseAddr;
			*(DWORD *)dwSize=me32.modBaseSize;
			CloseHandle( hModuleSnap );
			return TRUE;
		}		
	} while( Module32Next( hModuleSnap, &me32 ) );
	CloseHandle( hModuleSnap );
	return( FALSE );
}



DWORD SUNDAY(unsigned char *lpBase, unsigned char *lpCmp,DWORD len,DWORD maxSize)
{
    size_t temp[256]; 
    size_t *shift = temp; 
    size_t i, patt_size = len, text_size = maxSize; 
	
    for( i=0; i < 256; i++ ) 
        *(shift+i) = patt_size+1; 
	
    for( i=0; i < patt_size; i++ ) 
        *(shift+unsigned char(*(lpCmp+i))) = patt_size-i; 
    size_t limit = text_size-patt_size+1; 
    for( i=0; i < limit; i += shift[ lpBase[i+patt_size] ] ) 
    { 
        if( lpBase[i] == *lpCmp ) 
        { 
            unsigned char *match_text = lpBase+i+1; 
            size_t match_size = 1; 
            do 
            {
                if( match_size == patt_size )
				{
                    return (DWORD)lpBase+i;
				}
            } 
            while( (*match_text++) == lpCmp[match_size++] ); 
        } 
    } 
	return NULL;
}

/*
EngineSingCode
{
  szProcName   进程名
  szSearchCode 内存特征码
  dwLen        内存分页特征码长度
  (此函数采用最快的内存字符特征匹配算法SunDay,搜索2GB内存只需1秒)
}
*/
DWORD WINAPI SignCodeEngine(LPSTR szProcName,char * szSearchCode,DWORD dwlen)
{
	DWORD PID=GetCurrentProcessId();
	DWORD pBase,dwSize;
	if (!GetModuleInfo(PID,szProcName,&pBase,&dwSize))
		return NULL;
	DWORD pAddr=SUNDAY((unsigned char *)pBase,(unsigned char *)szSearchCode,dwlen,dwSize);
	return pAddr;
}

DWORD WINAPI ModuleSignCodeEngine(LPSTR szProcName,char * szSearchCode,DWORD dwlen)
{
	DWORD PID=GetCurrentProcessId();
	DWORD pBase,dwSize;
	if (!FindModule(PID,szProcName,&pBase,&dwSize))
		return NULL;
	DWORD pAddr=SUNDAY((unsigned char *)pBase,(unsigned char *)szSearchCode,dwlen,dwSize);
	return pAddr;
}
