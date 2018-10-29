/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         edwindow.cpp
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Source file for implementation of TEdTextGrid (TWindow).
*/
#include <owl\owlpch.h>
#pragma hdrstop
#include "textgrid.h"

TEdTextGrid::TEdTextGrid( TWindowDC* wdc )
{
	TEXTMETRIC tm;

	rowCnt	= 0;
	colMax   = 0;
	textRect.Set(0,0,0,0);

	wdc->GetTextMetrics(tm);
	cellHeight = tm.tmHeight;
	cellWidth  = tm.tmAveCharWidth;

	colMax 	= (cellWidth  ? ::GetSystemMetrics(SM_CXFULLSCREEN)/ cellWidth  : 0);
	rowMax 	= (cellHeight ? ::GetSystemMetrics(SM_CYFULLSCREEN)/ cellHeight : 0);
	rowRect 	= new TRect[rowMax];
	colRect 	= new TRect[colMax];
}

TEdTextGrid::~TEdTextGrid()
{
	delete[] rowRect;
	delete[] colRect;
}

void TEdTextGrid::Resize( TSize& size)
{
	textRect.left   = Min( (int)size.cx, (int)(cellWidth/2));
	int tmp         = size.cy % cellHeight;
	textRect.top    = (tmp)/2;
	textRect.bottom = size.cy - ((tmp)-textRect.top);
	textRect.right  = size.cx;

	colCnt    		 = (cellWidth  ? textRect.Width() / cellWidth : 0);
	rowCnt    		 = (cellHeight ? size.cy / cellHeight : 0);
	for(int i=0; i < rowMax; i++)
	{
		tmp = textRect.top+(i*cellHeight);
		rowRect[i].Set( textRect.left, tmp, textRect.right, tmp + cellHeight);
	}
	for( i=0; i < colMax; i++)
	{
		tmp = textRect.left+(i*cellWidth);
		colRect[i].Set( tmp, textRect.top, tmp + cellWidth, textRect.bottom );
	}
}
