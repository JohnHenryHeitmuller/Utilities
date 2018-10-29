/*  Project ed

    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         edwindow.cpp
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Source file for implementation of TEdTextBuffer ().
*/


#include <windows.h>
#pragma hdrstop
#include "textbuf.h"

//{{TEdTextBuffer Implementation}}


//////////////////////////////////////////////////////////
// TEdTextBuffer
// ==========
// Construction/Destruction handling.
TEdTextBuffer::TEdTextBuffer( TEdFile* _f )
{
	Initialize();
	f = _f;
	byteMore   = 0x8000;
	lineMore   = 0x1000;

	f->Lock();
	f->GetSize((DWORD)byteCnt);
	byteMax = byteCnt + byteMore;
	buf = (PBYTE)GlobalAlloc( GMEM_FIXED, byteMax);
	if( !buf)
		throw edEXCEPTION( INSUFFICIENT_MEMORY, edWINAPI | edCONTINUABLE);
	f->Read(buf);
	ScanBuffer();
}

TEdTextBuffer::~TEdTextBuffer()
{
	FreeResources();
}

void TEdTextBuffer::Initialize(void)
{
	f          = NULL;
	buf        = NULL;
	byteCnt    = 0;
	byteMax    = 0;
	colCnt     = 0;
	lineCnt    = 0;
	lineMax    = 0;
	lineTbl    = NULL;
}

void TEdTextBuffer::FreeResources(void)
{
	if(buf)
		delete[] buf;
	if(lineTbl)
		delete[] lineTbl;
}

void TEdTextBuffer::ScanBuffer(void)
{
	TEdLine* tmp;
	UINT     offset=0;

	lineMax = lineMore;
	lineTbl = (TEdLine*)GlobalAlloc( GMEM_FIXED, sizeof(TEdLine)*lineMax);
	if(!lineTbl)
		throw INSUFFICIENT_MEMORY;
	lineCnt = 0;
	for( UINT i=0; i < byteCnt; i++)
	{
		if( buf[i] == 0x0d || buf[i] == 0x0a)
		{
			if( lineCnt == lineMax )
			{	// ReAlloc into temp pointer to preserve lineTbl for GlobalFree() if fail
				lineMax += lineMore;
				tmp = (TEdLine*)GlobalReAlloc( lineTbl, sizeof(TEdLine)*lineMax, 0);
				if(!tmp)
					throw INSUFFICIENT_MEMORY;
				lineTbl = tmp;
			}
			lineTbl[ lineCnt].ptr = buf+offset;
			lineTbl[ lineCnt].length = i-offset;
			colCnt = (colCnt < lineTbl[ lineCnt].length ? lineTbl[ lineCnt].length : colCnt );
			lineCnt++;
			switch( buf[i] )
			{
				case 0x0d:  // CR
					if( buf[++i] == 0x0a && i < byteCnt)
						offset = i+1;
					else
						offset = i;
					break;
				case 0x0a:  // LF
					if( buf[++i] == 0x0d && i< byteCnt)
						offset = i+1;
					else
						offset = i;
					break;
			}
		}
	}
}


