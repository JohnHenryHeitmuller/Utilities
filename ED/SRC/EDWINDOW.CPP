/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         edwindow.cpp
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Source file for implementation of TEdCtrlWindow (TWindow).
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include "edapp.h"
#include "edwindow.h"

//{{TEdCtrlWindow Implementation}}


//
// Build a response table for all messages/commands handled
// by TEdCtrlWindow derived from TWindow.
//
DEFINE_RESPONSE_TABLE1(TEdCtrlWindow, TWindow)
//{{TEdCtrlWindowRSP_TBL_BEGIN}}
	 EV_WM_GETMINMAXINFO,
	 EV_WM_SIZE,
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
	Destroy();
	// INSERT>> Your destructor code here.
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
}

void TEdCtrlWindow::CalculatePosition( TSize& size, TRect& rect)
{
	/*
	rect.left   = min( (int)size.cx, (int)(g->GetCellWidth()/2));
	int tmp     = size.cy % g->GetCellHeight();
	rect.top    = (tmp)/2;
	rect.bottom = size.cy - ((tmp)-rect.top);
	rect.right  = size.cx;
	*/
   rect.Set( 0,0, size.cx, size.cy);
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
//		else
//			PaintToScreen( dc, erase, rect);
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

	d.fontText = new TFont(
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
	wdc->SelectObject( *d.fontText);
	brushBackGround = new TBrush(wdc->GetBkColor());
	delete wdc;
}

void TEdCtrlWindow::EvSize (uint sizeType, TSize& size)
{
	TWindow::EvSize(sizeType, size);
	// INSERT>> Your code here.
	g->Resize( size);
}


