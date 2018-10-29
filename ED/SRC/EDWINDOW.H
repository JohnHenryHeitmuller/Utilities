#if !defined(__editctrl_h)              // Sentry, use file only if it's not already included.
#define __editctrl_h

/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         editctrl.h
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Class definition for TEdCtrlWindow (TWindow).
*/
#include <owl\owlpch.h>
#pragma hdrstop
#include "edapp.rh"            // Definition of all resources.
#include "editfile.h"
#include "textbuf.h"
#include "textwin.h"
#include "scrollbr.h"

//{{TWindow = TEdCtrlWindow}}
class TEdCtrlWindow : public TWindow {
public:
	TEdCtrlWindow (TWindow* parent, const char far* title = 0, const char far* filename = 0,
					TModule* module = 0);
	virtual ~TEdCtrlWindow ();
	void CalculatePosition( TSize& size, TRect& rect);
	inline TBrush& GetBackGroundBrush() { return *d.brushBackGround; }
//{{TEdCtrlWindowVIRTUAL_BEGIN}}
public:
	virtual void SetupWindow ();
	virtual void Paint (TDC& dc, bool erase, TRect& rect);
	inline virtual void PaintToPrinter( TEdApp& app, TDC& dc, bool erase, TRect& rect);
	inline virtual void PaintToScreen(TDC& dc, bool erase, TRect& rect);
//{{TEdCtrlWindowVIRTUAL_END}}
private:
	TEdFile*       f;
	TEdTextBuffer* b;
   TEdScrollBar*  winHScrollBar;
   TEdScrollBar*  winVScrollBar;
   TEdTextWin*    winText;

   TBrush*        brushBkGround;
   TFont*         fontText;

//{{TEdCtrlWindowRSP_TBL_BEGIN}}
protected:
	void EvGetMinMaxInfo (MINMAXINFO far& minmaxinfo);
	void EvSize (uint sizeType, TSize& size);
//{{TEdCtrlWindowRSP_TBL_END}}
DECLARE_RESPONSE_TABLE(TEdCtrlWindow);
};    //{{TEdCtrlWindow}}


#endif                                      // __editctrl_h sentry.
