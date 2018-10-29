#if !defined(__edapp_h)              // Sentry, use file only if it's not already included.
#define __edapp_h

/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         edapp.h
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Class definition for TEdApp (TApplication).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include <classlib\bags.h>

#include "mdiclnt.h"
#include "edapp.rh"            // Definition of all resources.

// TFileDrop class Maintains information about a dropped file, its name, where it was dropped,
// and whether or not it was in the client area
class TFileDrop {
public:
    operator == (const TFileDrop& other) const {return this == &other;}

    char*   FileName;
    TPoint  Point;
    bool    InClientArea;

    TFileDrop (char*, TPoint&, bool, TModule*);
    ~TFileDrop ();

    const char* WhoAmI ();
private:
    //
    // hidden to prevent accidental copying or assignment
    //
    TFileDrop (const TFileDrop&);
    TFileDrop & operator = (const TFileDrop&);
};

typedef TIBagAsVector<TFileDrop> TFileList;
typedef TIBagAsVectorIterator<TFileDrop> TFileListIter;


//{{TApplication = TEdApp}}
class TEdApp : public TApplication {
private:
   bool            HelpState;                          // Has the help engine been used.
   bool            ContextHelp;                        // SHIFT-F1 state (context sensitive HELP)
   HCURSOR         HelpCursor;                         // Context sensitive help cursor
   SYSTEM_INFO		 sysInfo;

   void SetupSpeedBar (TDecoratedMDIFrame *frame);
   void AddFiles (TFileList* files);

public:
   TEdApp ();
   virtual ~TEdApp ();

   TOpenSaveDialog::TData  FileData;                   // Data to control open/saveas standard dialog.

   TEdMDIClient  *mdiClient;

   // Public data members used by the print menu commands and Paint routine in MDIChild.
   TPrinter        *Printer;                           // Printer support.
   int             Printing;                           // Printing in progress.

//{{TEdAppVIRTUAL_BEGIN}}
public:
   virtual void InitMainWindow();
   virtual void InitInstance();
   virtual bool CanClose ();
   virtual bool ProcessAppMsg (MSG& msg);
//{{TEdAppVIRTUAL_END}}

//{{TEdAppRSP_TBL_BEGIN}}
protected:
   void CmHelpContents ();
   void CmHelpUsing ();
   void CmHelpAbout ();
   void EvDropFiles (TDropInfo drop);
   void EvWinIniChange (char far* section);
//{{TEdAppRSP_TBL_END}}
DECLARE_RESPONSE_TABLE(TEdApp);
};    //{{TEdApp}}


#endif                                      // __edapp_h sentry.
