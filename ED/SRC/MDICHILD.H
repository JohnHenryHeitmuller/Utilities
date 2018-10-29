#if !defined(__mdichild_h)              // Sentry, use file only if it's not already included.
#define __mdichild_h

/*  Project ed

    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         mdichild.h
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Class definition for TEdMDIChild (TMDIChild).
*/


#include <owl\owlpch.h>
#pragma hdrstop
#include "edapp.rh"            // Definition of all resources.
#include "ctrlwin.h"

//{{TMDIChild = TEdMDIChild}}
class TEdMDIChild : public TMDIChild {
public:
	TEdMDIChild( TMDIClient &parent, const char far *title, TEdCtrlWindow *_wndClienr,
					 bool shrinkToClient = false, TModule* module = 0);
	virtual ~TEdMDIChild ();
private:
	//{{TEdMDIChildVIRTUAL_BEGIN}}
	//{{TEdMDIChildVIRTUAL_END}}

//{{TEdMDIChildRSP_TBL_BEGIN}}
protected:
//{{TEdMDIChildRSP_TBL_END}}
DECLARE_RESPONSE_TABLE(TEdMDIChild);
};    //{{TEdMDIChild}}


#endif                                      // __mdichild_h sentry.
