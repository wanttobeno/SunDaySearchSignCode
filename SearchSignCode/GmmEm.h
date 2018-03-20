#pragma once
#include <windows.h>

//ËÑË÷DLL´úÂë¹Ø¼üÌØÕ÷Âë
DWORD WINAPI ModuleSignCodeEngine(LPSTR szProcName,char * szSearchCode,DWORD dwlen);


//ËÑË÷EXE´úÂë¶Î
DWORD WINAPI SignCodeEngine(LPSTR szProcName,char * szSearchCode,DWORD dwlen);


/*
6C2EF029    6A 03           push    3
6C2EF02B    53              push    ebx
6C2EF02C    6A 08           push    8
6C2EF02E    6A 06           push    6
6C2EF030    FFB5 84EFFFFF   push    dword ptr [ebp-107C]
6C2EF036    FFB5 88EFFFFF   push    dword ptr [ebp-1078]
6C2EF03C    6A 00           push    0
6C2EF03E    51              push    ecx
6C2EF03F    50              push    eax
6C2EF040    FFB5 80EFFFFF   push    dword ptr [ebp-1080]
6C2EF046    E8 3E4FFFFF     call    6C2E3F89
*/
//Æ«ÒÆ+0x1D
unsigned char DQ10_Singcode1[]=
{
	0x6A, 0x03, 0x53, 0x6A, 0x08, 0x6A, 0x06
}; 

/*
00450548    8160 0C FF7FFFF>and     dword ptr [eax+C], FFFF7FFF
0045054F    2BC1            sub     eax, ecx
00450551    C1F8 05         sar     eax, 5
00450554    83C0 10         add     eax, 10
00450557    50              push    eax
00450558    E8 75D20000     call    0045D7D2
0045055D    59              pop     ecx
0045055E    5D              pop     ebp
0045055F    C3              retn
*/
//Æ«ÒÆ+0x10
unsigned char DQ10_Singcode2[]=
{
	0x81, 0x60, 0x0C, 0xFF, 0x7F, 0xFF, 0xFF, 0x2B, 0xC1, 0xC1, 
	0xF8, 0x05, 0x83, 0xC0, 0x10, 0x50
};


/*
006257F5    8B06            mov     eax, dword ptr [esi]
006257F7    8D48 04         lea     ecx, dword ptr [eax+4]
006257FA    3B4E 04         cmp     ecx, dword ptr [esi+4]
006257FD  - E9 C063DC02     jmp     033EBBC2
00625802    CC              int3
00625803    8B10            mov     edx, dword ptr [eax]
*/
//Æ«ÒÆ+0x10
unsigned char DQ10_Singcode3[]=
{
	0x8B, 0x06, 0x8D, 0x48, 0x04, 0x3B, 0x4E, 0x04, 0xE9, 0xC0, 
	0x63, 0xDC, 0x02, 0xCC, 0x8B, 0x10
};


/*
6AAECC59    2BCB            sub     ecx, ebx
6AAECC5B    D1F9            sar     ecx, 1
6AAECC5D    52              push    edx
6AAECC5E    51              push    ecx
6AAECC5F    EB 04           jmp     short 6AAECC65
6AAECC61    52              push    edx
6AAECC62    FF76 04         push    dword ptr [esi+4]
6AAECC65    FF36            push    dword ptr [esi]
6AAECC67    E8 16000000     call    6AAECC82                    [ÕÊºÅÃÜÂë]
6AAECC6C    8BD0            mov     edx, eax
6AAECC6E    83C6 14         add     esi, 14
6AAECC71    4F              dec     edi
*/
//Æ«ÒÆ+0xE

unsigned char DQ10_Singcode4[]=
{
	0x2B, 0xCB, 0xD1, 0xF9, 0x52, 0x51
};