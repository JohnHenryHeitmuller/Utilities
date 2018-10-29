#if !defined(__textbuf_h)              // Sentry, use file only if it's not already included.
#define __textbuf_h

/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         textgrid.h
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Class definition for TEdTextBuffer ().
*/
#pragma hdrstop
#include "ederror.h"
#include "editfile.h"
typedef struct TEdLinetag
{
	PBYTE	ptr;
	UINT  length;
} TEdLine;

//{{TEdTextBuffer=}}
class TEdTextBuffer
{
public:
	TEdTextBuffer( TEdFile* _f=NULL);
	~TEdTextBuffer();
	//{{TEdTextBufferVIRTUAL_BEGIN}}
	inline virtual void Initialize(void);
	inline virtual void FreeResources(void);

	inline virtual LPCTSTR GetLinePtr( UINT line) { return (LPCTSTR)(lineTbl[line].ptr); }
	inline virtual UINT    GetLineLength( UINT line) { return lineTbl[line].length; }
			 virtual void    ScanBuffer(void);
	inline virtual UINT    GetLineCnt() { return lineCnt; }
	inline virtual UINT    GetColCnt() { return colCnt; }
	//{{TEdTextBufferVIRTUAL_END}}
private:
	TEdFile* f;
	PBYTE 	buf;
	UINT		byteCnt;
	UINT     byteMore;
	UINT		byteMax;
	UINT     colCnt;     // col count 1 base (the length of the file's longest text line)
	UINT		lineCnt;    // line count 1 base
	UINT		lineMax;
	UINT		lineMore;
	TEdLine*	lineTbl;
};    //{{TEdTextBuffer}}

#endif                                      // __textbuf_h sentry.
