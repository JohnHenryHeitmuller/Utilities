/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         mdichild.cpp
    AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Source file for implementation of TEdMDIChild (TMDIChild).
*/


#include <owl\owlpch.h>
#include <mem.h>
#pragma hdrstop

#include "edapp.h"
#include "ctrlwin.h"
#include "mdichild.h"


//
// Build a response table for all messages/commands handled
// by the application.
//
DEFINE_RESPONSE_TABLE1(TEdMDIChild, TMDIChild)
//{{TEdMDIChildRSP_TBL_BEGIN}}
//{{TEdMDIChildRSP_TBL_END}}
END_RESPONSE_TABLE;


//{{TEdMDIChild Implementation}}


//////////////////////////////////////////////////////////
// TEdMDIChild
// ==========
// Construction/Destruction handling.
TEdMDIChild::TEdMDIChild( TMDIClient &parent, const char far *title, TEdCtrlWindow *_wndClient,
								  bool shrinkToClient, TModule *module) :
								  TMDIChild (parent, title, _wndClient == 0 ? new TEdCtrlWindow(0, "") :
								  _wndClient, shrinkToClient, module)
{
	// INSERT>> Your constructor code here.
}

TEdMDIChild::~TEdMDIChild ()
{
	Destroy();
	// INSERT>> Your destructor code here.
}


