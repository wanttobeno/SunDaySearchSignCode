

####  Tip

在[看雪](https://bbs.pediy.com/thread-192985.htm)上看到一段代码注释“此函数采用最快的内存字符特征匹配算法SunDay,搜索2GB内存只需1秒”。


#### 功能

SunDay算法实现的Dll或者EXE的指定特征码地址获取,不支持模糊搜索。


#### 补充

可根据需要修改SUNDAY返回值类型，返回的是指针地址。

```c++
/**
 *  参数一：内存的起点
 *  参数二：查找的二进制
 *  参数三：查找二进制的大小
 *  参数四：最大查找字节
 */
DWORD SUNDAY(unsigned char *lpBaseBuf, unsigned char *pFindData,DWORD nFindDataSize,DWORD nMaxSize)
```

```c++
unsigned char* szFindStart = (unsigned char*)pbuf;
unsigned char* szFindRet; 
int nMaxLen = nLen;
do
{
	szFindRet = SUNDAY(szFindStart,(unsigned char*)"FindMe",nFindLen1,nMaxLen);	
	if (!szFindRet) {
		break;
	}
	szFindStart = szFindRet;
	nMaxLen = nLen - (szFindRet-(unsigned char*)pbuf);	
	// Do something
			
}while(1);
```