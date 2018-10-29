/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.apx Application
    FILE:         scrollbr.cpp
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Source file for implementation of TEdScrollBar (TScrollBar).      
*/

#include <owl\owlpch.h>
#pragma hdrstop

#include "scrollbr.h"


//
// Build a response table for all messages/commands handled
// by the application.
//
DEFINE_RESPONSE_TABLE1(TEdScrollBar, TScrollBar)
//{{TEdScrollBarRSP_TBL_BEGIN}}
    EV_WM_SETFOCUS,
//{{TEdScrollBarRSP_TBL_END}}
END_RESPONSE_TABLE;


//{{TEdScrollBar Implementation}}


TEdScrollBar::TEdScrollBar (TWindow* parent, TWindow* _target, int id, int x, int y, int w, int h, bool _isHScrollBar, TModule* module):
	 TScrollBar(parent, id, x, y, w, h, _isHScrollBar, module)
{
	// INSERT>> Your constructor code here.
	target = _target;
	isHScrollBar = _isHScrollBar;
}


TEdScrollBar::~TEdScrollBar ()
{
	 Destroy();

	 // INSERT>> Your destructor code here.

}


void TEdScrollBar::EvSetFocus (HWND hWndLostFocus )
{
	 TScrollBar::EvSetFocus(hWndLostFocus );
	 // INSERT>> Your code here.
	 target->SetFocus();
}


