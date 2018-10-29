/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.apx Application
	 FILE:         textwin.cpp
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Source file for implementation of TEdTextWindow (TWindow).
*/

#include <owl\owlpch.h>
#pragma hdrstop
#include "textwin.h"


//
// Build a response table for all messages/commands handled
// by the application.
//
DEFINE_RESPONSE_TABLE1(TEdTextWindow, TWindow)
//{{TEdTextWindowRSP_TBL_BEGIN}}
	 EV_WM_KEYDOWN,
	 EV_WM_KILLFOCUS,
	 EV_WM_SETFOCUS,
	 EV_WM_SIZE,
//{{TEdTextWindowRSP_TBL_END}}
END_RESPONSE_TABLE;


//{{TEdTextWindow Implementation}}


TEdTextWindow::TEdTextWindow (TWindow* parent, TEdTextBuffer* _b, TFont* _font, const char far* title, TModule* module):
	 TWindow(parent, title, module)
{
	// INSERT>> Your constructor code here.
	b    = _b;
	font = _font;

	rowCnt        = 0;
	colCnt        = 0;
	bufLine		  = 0;
	bufCol		  = 0;
	lineTop       = 0;
	lineBottom    = 0;
	colLeft       = 0;
	colRight      = 0;
	brushBkGround = NULL;
	rowRect		  = NULL;
	colRect       = NULL;
	CaretDataInit();
}

TEdTextWindow::~TEdTextWindow ()
{
	Destroy();
	// INSERT>> Your destructor code here.
	if(brushBkGround)
		delete brushBkGround;
	if(rowRect)
		delete[] rowRect;
	if(colRect)
		delete[] colRect;
}

void TEdTextWindow::CaretDataInit(void)
{
	c.row = 0;
	c.col = 0;
	c.state = 0;
}

TPoint& TEdTextWindow::CaretGetXY(void)
{
	c.p.x = colRect[c.col].left;
	c.p.y = rowRect[c.row].top+c.rowAdj;
	return(c.p);
}

int TEdTextWindow::CaretMoveCol(int cnt)
{
	int adjustDisplay = 0;
	c.col += cnt;
	if( c.col < 0)
	{
		adjustDisplay = c.col;
		c.col = 0;
	}
	else if( c.col > colCnt-1)
	{
		adjustDisplay = c.col;
		c.col = colCnt-1;
	}
	SetCaretPos( CaretGetXY());
	return(adjustDisplay);
}

int TEdTextWindow::CaretMoveRow(int cnt)
{
	int adjustDisplay = 0;
	c.row += cnt;
	if( c.row < 0)
	{
		adjustDisplay = c.row;
		c.row = 0;
	}
	else if( c.row > rowCnt-1)
	{
		adjustDisplay = c.row;
		c.row = rowCnt-1;
	}
	SetCaretPos( CaretGetXY());
	return(adjustDisplay);
}

void TEdTextWindow::EvKeyDown (uint key, uint repeatCount, uint flags)
{
   TWindow::EvKeyDown(key, repeatCount, flags);
   // INSERT>> Your code here.
	switch(key)
	{
		case VK_LEFT:
			if(CaretMoveCol(repeatCount*-1))
				PanLeft(repeatCount);
			break;
		case VK_RIGHT:
			if(CaretMoveCol(repeatCount))
				PanRight(repeatCount);
			break;
		case VK_UP:
			if( CaretMoveRow(repeatCount*-1))
				ScrollUp(repeatCount);
			break;
		case VK_DOWN:
			if( CaretMoveRow(repeatCount) )
				ScrollDown(repeatCount);
			break;
		case VK_NEXT: // page down
			PageDown(repeatCount);
			break;
		case VK_PRIOR: // page up
			PageUp(repeatCount);
			break;
	}

}

void TEdTextWindow::ScrollDown( UINT cnt)
{
	if( lineBottom + cnt > b->GetLineCnt()-1)
	{
		if( (cnt = (b->GetLineCnt()-1)-lineBottom) == 0)
			return;
	}
	lineBottom += cnt;
	lineTop    += cnt;
	if( cnt > rowCnt )
	{
		Invalidate();	// jumped past bottom of display data, force
		return;			//    repaint of whole client area
	}
	HideCaret();
	TWindowDC *wdc = new TWindowDC(HWindow);
	wdc->SelectObject(*font);
	ScrollWindow( 0, cell.cy*cnt*-1);
	UINT row = rowCnt - cnt;
	wdc->FillRect( rowRect[row]| rowRect[rowCnt-1], *brushBkGround);
	for( int i = (lineBottom - cnt)+1; row < rowCnt; i++)
	{
		if( b->GetLineLength(i) > colLeft)
			wdc->TextOut( 0, rowRect[row].top, b->GetLinePtr(i)+colLeft,
							b->GetLineLength(i)-colLeft);
		row++;
	}
	Validate();
	delete wdc;
	ShowCaret();
}

void TEdTextWindow::ScrollUp( UINT cnt)
{
	cnt = min( lineTop, cnt);
	if( !cnt  )
		return;
	lineTop    -= cnt;
	lineBottom -= cnt;
	if( cnt > rowCnt )
	{
		Invalidate();	// jumped past top of displayed data, force
		return;			//    repaint of whole client area
	}
	HideCaret();
	TWindowDC *wdc = new TWindowDC(HWindow);
	wdc->SelectObject(*font);
	ScrollWindow( 0, cell.cy*cnt);
	wdc->FillRect( rowRect[0]| rowRect[cnt-1], *brushBkGround);
	int i = lineTop;
	for( int row=0; row < cnt; i++)
	{
		if( b->GetLineLength(i) > colLeft)
			wdc->TextOut( 0, rowRect[row].top, b->GetLinePtr(i)+colLeft,
							b->GetLineLength(i)-colLeft);
		row++;
	}
	Validate();
	delete wdc;
	ShowCaret();
}
void TEdTextWindow::PageDown( UINT /*cnt*/)
{
	if( lineBottom < b->GetLineCnt()-1)
	{
		lineBottom += min( rowCnt, (b->GetLineCnt()-1)-lineBottom);
		lineTop = lineBottom-rowCnt-1;
		Invalidate();
	}
}
void TEdTextWindow::PageUp( UINT/* cnt*/)
{
	if( lineTop )
	{
		lineTop = (lineTop < rowCnt ? 0 : lineTop-rowCnt);
		lineBottom = lineTop+rowCnt-1;
		Invalidate();
	}
}

void TEdTextWindow::PanLeft( UINT cnt)
{
	cnt = min( colLeft, cnt);
	if(!cnt)
		return;

	colRight -= cnt;
	colLeft  -= cnt;
	HideCaret();
	TWindowDC *wdc = new TWindowDC(HWindow);
	ScrollWindow( cell.cx, 0);
	delete wdc;
	InvalidateRect(colRect[0] | colRect[cnt-1] );
	ShowCaret();
}

void TEdTextWindow::PanRight( UINT cnt)
{
	if( colRight + cnt > b->GetColCnt()-1)
	{
		if( (cnt = (b->GetColCnt()-1)-colRight) == 0)
			return;
	}
	colRight += cnt;
	colLeft  += cnt;
	HideCaret();
	TWindowDC *wdc = new TWindowDC(HWindow);
	ScrollWindow( cell.cx*cnt*-1, 0);
	delete wdc;
	InvalidateRect( colRect[colCnt - cnt] | colRect[colCnt-1]);
	ShowCaret();
}




void TEdTextWindow::EvKillFocus (HWND hWndGetFocus )
{
	TWindow::EvKillFocus(hWndGetFocus );

	// INSERT>> Your code here.
	HideCaret();
	DestroyCaret();
}


void TEdTextWindow::EvSetFocus (HWND hWndLostFocus )
{
	TWindow::EvSetFocus(hWndLostFocus );

	// INSERT>> Your code here.
	c.height = max((int)2,(int)(cell.cy/5));
	c.rowAdj = cell.cy - c.height;
	CreateCaret(0, cell.cx, c.height);
	SetCaretPos( CaretGetXY());
	ShowCaret();
}


void TEdTextWindow::Paint (TDC& dc, bool erase, TRect& rect)
{
	TWindow::Paint(dc, erase, rect);
	// INSERT>> Your code here.
	dc.SelectObject(*font);
	int cnt = lineTop + min( rowCnt, b->GetLineCnt());
	int row=0;
	for( int i=lineTop; i<cnt; i++)
	{
		if( b->GetLineLength(i) > colLeft)
			dc.TextOut( 0, rowRect[row].top, b->GetLinePtr(i)+colLeft,
							b->GetLineLength(i)-colLeft);
		row++;
	}
	lineBottom = min( lineTop + rowCnt-1, b->GetLineCnt()-1);
	colRight   = min( colLeft + colCnt-1, b->GetColCnt()-1);
}

void TEdTextWindow::SetupWindow ()
{
	TWindow::SetupWindow();
	// INSERT>> Your code here.
	TWindowDC* wdc = new TWindowDC( HWindow);
	wdc->SelectObject( *font);
	wdc->GetTextMetrics( tm );
	brushBkGround = new TBrush(wdc->GetBkColor());
	delete wdc;

	cell.cy = tm.tmHeight;
	cell.cx = tm.tmAveCharWidth;
	rowMax  = ::GetSystemMetrics( SM_CYFULLSCREEN)/cell.cy;
	colMax  = ::GetSystemMetrics( SM_CXFULLSCREEN)/cell.cx;
	rowRect = new TRect[rowMax];
	colRect = new TRect[colMax];
}


void TEdTextWindow::EvSize (uint sizeType, TSize& size)
{
	TWindow::EvSize(sizeType, size);
	// INSERT>> Your code here.
	rowCnt = min( rowMax, (UINT)(size.cy/cell.cy));
	for( int i=0; i < rowCnt; i++)
	{
		rowRect[i].left   = 0;
		rowRect[i].top    = i*cell.cy;
		rowRect[i].right  = size.cx;
		rowRect[i].bottom = rowRect[i].top+cell.cy;
	}
	colCnt = min( colMax, (UINT)(size.cx/cell.cx));
	for( i=0; i < colCnt; i++)
	{
		colRect[i].left   = i*cell.cx;
		colRect[i].top    = 0;
		colRect[i].right  = rowRect[i].left+cell.cx;
		colRect[i].bottom = size.cy;
	}
}

