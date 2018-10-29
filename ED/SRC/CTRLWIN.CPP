/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         ctrlwin.cpp
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Source file for implementation of TEdCtrlWindow (TWindow).
*/


#include <owl\owlpch.h>
#pragma hdrstop
#include "edapp.h"
#include "ctrlwin.h"

//{{TEdCtrlWindow Implementation}}


//
// Build a response table for all messages/commands handled
// by TEdCtrlWindow derived from TWindow.
//
DEFINE_RESPONSE_TABLE1(TEdCtrlWindow, TWindow)
//{{TEdCtrlWindowRSP_TBL_BEGIN}}
	 EV_WM_GETMINMAXINFO,
	 EV_WM_SIZE,
    EV_WM_SETFOCUS,
//{{TEdCtrlWindowRSP_TBL_END}}
	 //EV_CHILD_NOTIFY_ALL_CODES(IDSB_VEDWINDOW, EvThermometer),
END_RESPONSE_TABLE;


//////////////////////////////////////////////////////////
// TEdCtrlWindow
// ==========
// Construction/Destruction handling.
TEdCtrlWindow::TEdCtrlWindow (TWindow* parent, const char far* title, const char far* filename, TModule* module)
	 : TWindow(parent, title, module)
{
	// INSERT>> Your constructor code here.

   winHScrollBar = NULL;
   winVScrollBar = NULL;
   winText = NULL;
	f = NULL;
	b = NULL;
	f = new TEdFile(filename);
	b = new TEdTextBuffer(f);
}


TEdCtrlWindow::~TEdCtrlWindow ()
{
	if(f)
		delete f;
	if(b)
		delete b;
	if(winText)
		delete winText;
	if(winHScrollBar)
		delete winHScrollBar;
	if(winVScrollBar)
		delete winVScrollBar;
	Destroy();
	// INSERT>> Your destructor code here.
}

//
// Paint routine for Window, Printer, and PrintPreview for an TWindow client.
//
void TEdCtrlWindow::Paint( TDC& dc, bool erase, TRect& rect)
{
	TWindow::Paint(dc, erase, rect);
	// INSERT>> Normal painting code goes here.
	TEdApp *app = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);
	if (app)
	{
		// Only paint if we're printing and we have something to paint, otherwise do nothing.
		if (app->Printing && app->Printer && !rect.IsEmpty())
			PaintToPrinter( *app, dc, erase, rect);
		else
			PaintToScreen( dc, erase, rect);
	}
}

void TEdCtrlWindow::PaintToPrinter( TEdApp& app, TDC& /*dc*/, bool, TRect& rect)
{
	// Use pageSize to get the size of the window to render into.  For a Window it's the client area,
	// for a printer it's the printer DC dimensions and for print preview it's the layout window.
	TSize   pageSize(rect.right - rect.left, rect.bottom - rect.top);

	TPrintDialog::TData &printerData = app.Printer->GetSetup();

	// Compute the number of pages to print.
	printerData.MinPage = 1;
	printerData.MaxPage = 1;

	// INSERT>> Special printing code goes here.
}
void TEdCtrlWindow::PaintToScreen( TDC& /*dc*/, bool /*erase*/, TRect& /*rect*/)
{
/*
	if(winText)
		winText->Paint(dc, erase, rect);
	if(winHScrollBar)
		winHScrollBar->Paint(dc, erase, rect);
	if(winVScrollBar)
		winVScrollBar->Paint(dc, erase, rect);
*/
}
void TEdCtrlWindow::EvGetMinMaxInfo (MINMAXINFO far& minmaxinfo)
{
	 TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);
	 if (theApp) {
		  if (theApp->Printing) {
				minmaxinfo.ptMaxSize = TPoint(32000, 32000);
				minmaxinfo.ptMaxTrackSize = TPoint(32000, 32000);
				return;
		  }
	 }
	 TWindow::EvGetMinMaxInfo(minmaxinfo);
}

void TEdCtrlWindow::SetupWindow ()
{
	TWindow::SetupWindow();
	// INSERT>> Your code here.
	TWindowDC* 	wdc;

	fontText = new TFont(
			(const char far*)NULL, //const char far* facename = 0
			(int)0, // int height = 0
			(int)0, // int width = 0
			(int)0, // int escapement = 0
			(int)0, // int orientation = 0
			(int)0, // int weight = FW_NORMAL
			FIXED_PITCH | FF_DONTCARE, //uint8 pitchAndFamily = DEFAULT_PITCH|FF_DONTCARE
			(uint8)0, // uint8 italic = false
			(uint8)0, // uint8 underline = false
			(uint8)0, // uint8 strikeout = false
			(uint8)OEM_CHARSET, // uint8 charSet = 1
			(uint8)0, // uint8 outputPrecision = OUT_DEFAULT_PRECIS
			(uint8)0, // uint8 clipPrecision = CLIP_DEFAULT_PRECIS
			(uint8)0);// uint8 quality = DEFAULT_QUALITY
	wdc = new TWindowDC(HWindow);
	brushBkGround = new TBrush(wdc->GetBkColor());
	delete wdc;
	winText       = new TEdTextWindow( this, b, fontText);
	winText->Create();
	winHScrollBar = new TEdScrollBar( this, winText, IDSB_HTEXTWINDOW, 0, 0, 0, 0, TRUE);
	winHScrollBar->Create();
	winVScrollBar = new TEdScrollBar( this, winText, IDSB_VTEXTWINDOW, 0, 0, 0, 0, FALSE);
	winVScrollBar->Create();
}

void TEdCtrlWindow::EvSize (uint sizeType, TSize& size)
{
	TWindow::EvSize(sizeType, size);
	// INSERT>> Your code here.
	if( size.cx || size.cy)
	{
		TSize vscroll(::GetSystemMetrics(SM_CXVSCROLL),::GetSystemMetrics(SM_CYVSCROLL));
		TSize hscroll(::GetSystemMetrics(SM_CXHSCROLL),::GetSystemMetrics(SM_CYHSCROLL));
		winVScrollBar->MoveWindow( size.cx-vscroll.cx, 0, size.cx, size.cy-hscroll.cy, TRUE);
		winHScrollBar->MoveWindow( 0, size.cy-hscroll.cy, size.cx-vscroll.cx, size.cy, TRUE);
		TSize cell;
		winText->GetCellSize(cell);
		TRect rect;
		rect.left = cell.cx/2;
		rect.top = ((size.cy-hscroll.cy) % cell.cy)/2;
		rect.right = size.cx-vscroll.cx;
		rect.bottom = rect.top + (((size.cy-hscroll.cy)/cell.cy)*cell.cy);
		winText->MoveWindow( rect, TRUE);
		winVScrollBar->Invalidate();
      winHScrollBar->Invalidate();
		Invalidate();
	}
}

void TEdCtrlWindow::EvSetFocus (HWND hWndLostFocus )
{
	TWindow::EvSetFocus(hWndLostFocus );
	// INSERT>> Your code here.
//	if(winText)
//   	winText->SetFocus();
}

