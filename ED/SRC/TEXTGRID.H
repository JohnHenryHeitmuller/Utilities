#if !defined(__textgrid_h)              // Sentry, use file only if it's not already included.
#define __textgrid_h

/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         textgrid.h
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Class definition for TEdTextGrid ().
*/
#pragma hdrstop
#include "ederror.h"

class TEdTextGrid
{
public:
	TEdTextGrid( TWindowDC* wdc );
	~TEdTextGrid();
	virtual inline void Resize( TSize& size);
	virtual inline UINT GetRowCnt() { return rowCnt; }
	virtual inline UINT GetColCnt() { return colCnt; }
	virtual inline UINT GetCellHeight() { return cellHeight; }
	virtual inline UINT GetCellWidth() { return cellWidth; }
	virtual inline TRect& GetTextRect() { return textRect; }
	virtual inline TRect& GetRowRect( UINT row ) { return rowRect[row]; }
	virtual inline TRect& GetColRect( UINT col ) { return colRect[col]; }

private:
	int    cellHeight;
	int    cellWidth;
	TRect  textRect;
	TRect* rowRect;
	TRect* colRect;
	UINT   rowMax;
	UINT 	 rowCnt;
	UINT   colMax;
	UINT 	 colCnt;
};
#endif                                      // __textgrid_h sentry.
