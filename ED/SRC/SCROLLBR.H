#if !defined(__scrollbr_h)              // Sentry, use file only if it's not already included.
#define __scrollbr_h

/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.apx Application
    FILE:         scrollbr.h
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Class definition for TEdScrollBar (TScrollBar).      
*/

#include <owl\owlpch.h>
#pragma hdrstop


#include "edapp.rh"            // Definition of all resources.


//{{TScrollBar = TEdScrollBar}}
class TEdScrollBar : public TScrollBar {
public:
   TEdScrollBar (TWindow* parent, TWindow* _target, int id, int x, int y, int w, int h, bool _isHScrollBar, TModule* module = 0);
   virtual ~TEdScrollBar ();
private:
	TWindow* target;
	bool isHScrollBar;
//{{TEdScrollBarRSP_TBL_BEGIN}}
protected:
    void EvSetFocus (HWND hWndLostFocus );
//{{TEdScrollBarRSP_TBL_END}}
DECLARE_RESPONSE_TABLE(TEdScrollBar);
};    //{{TEdScrollBar}}


#endif                                      // __scrollbr_h sentry.

