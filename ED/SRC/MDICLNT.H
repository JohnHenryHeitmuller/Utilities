#if !defined(__mdiclnt_h)              // Sentry, use file only if it's not already included.
#define __mdiclnt_h

/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         mdiclnt.h
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Class definition for TEdMDIClient (TMDIClient).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include "edapp.rh"            // Definition of all resources.


//{{TMDIClient = TEdMDIClient}}
class TEdMDIClient : public TMDIClient {
public:
   int                     ChildCount;                 // Number of child window created.

   TEdMDIClient(TModule* module = 0);
   virtual ~TEdMDIClient ();

   void OpenFile (const char *fileName = 0);

private:

//{{TEdMDIClientVIRTUAL_BEGIN}}
protected:
   virtual void SetupWindow ();
//{{TEdMDIClientVIRTUAL_END}}

//{{TEdMDIClientRSP_TBL_BEGIN}}
protected:
   void CmFileNew ();
   void CmFileOpen ();
   void CmFilePrint ();
   void CmFilePrintSetup ();
   void CmFilePrintPreview ();
   void CmPrintEnable (TCommandEnabler &tce);
   void EvDropFiles (TDropInfo);
//{{TEdMDIClientRSP_TBL_END}}
DECLARE_RESPONSE_TABLE(TEdMDIClient);
};    //{{TEdMDIClient}}


#endif                                      // __mdiclnt_h sentry.
