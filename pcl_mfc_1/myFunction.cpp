#include "StdAfx.h"
#include <stdio.h>
#include <iostream> 

void backslashCopy(char * srcString, char *dstString)
{
	int length;
	int i;
	int j;

	length = strlen(srcString);

	j = 0;
	for(i = 0; i < length; i++)
	{
		if('\\' == srcString[i])
		{
			dstString[j++] = '\\';
			dstString[j++] = '\\';
		}
		else
		{
			dstString[j++] = srcString[i];
		}
	}

	dstString[j++] = '\0';
	return;
}

void cstring2Char(CString srcString, char *dstString)
{
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,srcString,-1,NULL,NULL,0,NULL);
	char *c = new char[dwNum]; 
	WideCharToMultiByte(CP_OEMCP,NULL,srcString,-1,c,dwNum,0,NULL); 
	memcpy(dstString, c, dwNum); 
	delete c;
	c = NULL;
}
