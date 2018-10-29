#if !defined(__aboutdlg_h)              // Sentry, use file only if it's not already included.
#define __aboutdlg_h

/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         aboutdlg.h
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Class definition for TEdAboutDlg (TDialog).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include "edapp.rh"                  // Definition of all resources.


//{{TDialog = TEdAboutDlg}}
class TEdAboutDlg : public TDialog {
public:
    TEdAboutDlg (TWindow *parent, TResId resId = IDD_ABOUT, TModule *module = 0);
    virtual ~TEdAboutDlg ();

//{{TEdAboutDlgVIRTUAL_BEGIN}}
public:
    void SetupWindow ();
//{{TEdAboutDlgVIRTUAL_END}}
};    //{{TEdAboutDlg}}


// Reading the VERSIONINFO resource.
class ProjectRCVersion {
public:
    ProjectRCVersion (TModule *module);
    virtual ~ProjectRCVersion ();

    bool GetProductName (LPSTR &prodName);
    bool GetProductVersion (LPSTR &prodVersion);
    bool GetCopyright (LPSTR &copyright);
    bool GetDebug (LPSTR &debug);

protected:
    LPBYTE      TransBlock;
    void FAR    *FVData;

private:
    // Don't allow this object to be copied.
    ProjectRCVersion (const ProjectRCVersion &);
    ProjectRCVersion & operator =(const ProjectRCVersion &);
};


#endif                                      // __aboutdlg_h sentry.
