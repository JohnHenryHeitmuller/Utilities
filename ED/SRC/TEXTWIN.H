#if !defined(__textwin_h)              // Sentry, use file only if it's not already included.
#define __textwin_h

/*  Project ed

    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.apx Application
    FILE:         textwin.h
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Class definition for TEdTextWindow (TWindow).
*/

#include <owl\owlpch.h>
#pragma hdrstop
#include "edapp.rh"            // Definition of all resources.
#include "editfile.h"
#include "textbuf.h"

typedef struct TEdCaretDatatag
{
	int    row;
	int    col;
	int	 height;
	int	 rowAdj;
	UINT   state;
	TPoint p;
} TEdCaretData;

//{{TWindow = TEdTextWindow}}
class TEdTextWindow : public TWindow {
public:
	TEdTextWindow (TWindow* parent, TEdTextBuffer* _b, TFont* _font, const char far* title = 0, TModule* module = 0);
	virtual ~TEdTextWindow ();

	inline void GetCellSize( TSize& _cell) { _cell.cx=cell.cx; _cell.cy=cell.cy; }

	// screen movement functions
	inline void    ScrollDown( UINT cnt);
	inline void    ScrollUp( UINT cnt);
	inline void    PageDown( UINT cnt);
	inline void    PageUp( UINT cnt);
	inline void    PanLeft( UINT cnt );
	inline void    PanRight( UINT cnt );
	// caret movement functions
	inline int		CaretMoveCol(int cnt);
	inline int		CaretMoveRow(int cnt);
	inline TPoint& CaretGetXY(void);

private:
	TEXTMETRIC tm;
	TSize		cell;
	TRect*   rowRect;
	TRect*   colRect;
	UINT     rowMax;			// allocated size
	UINT 	   rowCnt;			// population count
	UINT     colMax;			// allocated size
	UINT 	   colCnt;			// population count

	UINT	   bufLine;       // kb cursor file line
	UINT	   bufCol;        // kb cursor file col

	UINT	   lineTop;		    // file line # (0 base) of text line at top of window
	UINT	   lineBottom;
	UINT	   colLeft;
	UINT	   colRight;

	TFont*   font;
	TBrush*  brushBkGround;

	TEdTextBuffer* b;
	TEdCaretData   c;
	inline void    CaretDataInit(void);

//{{TEdTextWindowVIRTUAL_BEGIN}}
public:
    virtual void Paint (TDC& dc, bool erase, TRect& rect);
    virtual void SetupWindow ();
//{{TEdTextWindowVIRTUAL_END}}

//{{TEdTextWindowRSP_TBL_BEGIN}}
protected:
    void EvKeyDown (uint key, uint repeatCount, uint flags);
    void EvKillFocus (HWND hWndGetFocus );
    void EvSetFocus (HWND hWndLostFocus );
    void EvSize (uint sizeType, TSize& size);
//{{TEdTextWindowRSP_TBL_END}}
DECLARE_RESPONSE_TABLE(TEdTextWindow);
};    //{{TEdTextWindow}}

#endif                                      // __textwin_h sentry.

