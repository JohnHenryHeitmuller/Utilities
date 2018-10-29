/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         mdiclnt.cpp
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Source file for implementation of TEdMDIClient (TMDIClient).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include <dir.h>

#include "edapp.h"
#include "ctrlwin.h"
#include "mdichild.h"
#include "mdiclnt.h"
#include "apxprint.h"
#include "apxprev.h"


//{{TEdMDIClient Implementation}}


//
// Build a response table for all messages/commands handled
// by TEdMDIClient derived from TMDIClient.
//
DEFINE_RESPONSE_TABLE1(TEdMDIClient, TMDIClient)
//{{TEdMDIClientRSP_TBL_BEGIN}}
    EV_COMMAND(CM_MDIFILENEW, CmFileNew),
    EV_COMMAND(CM_MDIFILEOPEN, CmFileOpen),
    EV_COMMAND(CM_FILEPRINT, CmFilePrint),
    EV_COMMAND(CM_FILEPRINTERSETUP, CmFilePrintSetup),
    EV_COMMAND(CM_FILEPRINTPREVIEW, CmFilePrintPreview),
    EV_COMMAND_ENABLE(CM_FILEPRINT, CmPrintEnable),
    EV_COMMAND_ENABLE(CM_FILEPRINTERSETUP, CmPrintEnable),
    EV_COMMAND_ENABLE(CM_FILEPRINTPREVIEW, CmPrintEnable),
    EV_WM_DROPFILES,
//{{TEdMDIClientRSP_TBL_END}}
END_RESPONSE_TABLE;


//////////////////////////////////////////////////////////
// TEdMDIClient
// ===========
// Construction/Destruction handling.
TEdMDIClient::TEdMDIClient (TModule* module)
 : TMDIClient (module)
{
    ChildCount = 0;

    // INSERT>> Your constructor code here.

}


TEdMDIClient::~TEdMDIClient ()
{
    Destroy();

    // INSERT>> Your destructor code here.

}


//////////////////////////////////////////////////////////
// TEdMDIClient
// ===========
// MDIClient site initialization.
void TEdMDIClient::SetupWindow ()
{
    // Default SetUpWindow processing.
    TMDIClient::SetupWindow ();

	 TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);

    // Common file file flags and filters for Open/Save As dialogs.  Filename and directory are
    // computed in the member functions CmFileOpen, and CmFileSaveAs.
    theApp->FileData.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    theApp->FileData.SetFilter("All Files (*.*)|*.*|");

    // Accept files via drag/drop in the client window.
    DragAcceptFiles(true);
}


//////////////////////////////////////////////////////////
// TEdMDIClient
// ===========
// Menu File New command
void TEdMDIClient::CmFileNew ()
{
	 char    title[255];
	 char    numberStr[16];

	 // Generate a title for the MDI child window.
	 if (GetModule()->LoadString(IDS_UNTITLED, title, sizeof(title))) {
		  wsprintf(numberStr, " - %d", ChildCount++);
		  strcat(title, numberStr);
	 } else
		  title[0] = '\0';

	 TEdMDIChild* child = new TEdMDIChild(*this, title, NULL, 0);

	 // Associate ICON w/ this child window.
	 child->SetIcon(GetApplication(), IDI_DOC);

	 // If the current active MDI child is maximize then this one should be also.
	 TEdMDIChild *curChild = (TEdMDIChild *)GetActiveMDIChild();
	 if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
		  child->Attr.Style |= WS_MAXIMIZE;

	 child->Create();
}


void TEdMDIClient::OpenFile (const char *fileName)
{
	 TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);

	 if (fileName)
		  strcpy(theApp->FileData.FileName, fileName);

	 //
	 // Create a MDIChild window whose client is TEdCtrlWindow.
	 //
	 TEdMDIChild* child = new TEdMDIChild( *this, theApp->FileData.FileName,
								 new TEdCtrlWindow( 0, theApp->FileData.FileName, theApp->FileData.FileName));

	 // Associate ICON w/ this child window.
	 child->SetIcon(GetApplication(), IDI_DOC);

	 // If the current active MDI child is maximize then this one should be also.
	 TEdMDIChild *curChild = (TEdMDIChild *)GetActiveMDIChild();
    if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
        child->Attr.Style |= WS_MAXIMIZE;

	 child->Create();
}


//////////////////////////////////////////////////////////
// TEdMDIClient
// ===========
// Menu File Open command
void TEdMDIClient::CmFileOpen ()
{
    TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);

    //
	 // Display standard Open dialog box to select a file name.
	 //
	 *(theApp->FileData.FileName) = 0;
	 if (TFileOpenDialog(this, theApp->FileData).Execute() == IDOK)
		  OpenFile();
}

//////////////////////////////////////////////////////////
// TEdMDIClient
// ==========
// Menu File Print command
void TEdMDIClient::CmFilePrint ()
{
	 //
	 // Create Printer object if not already created.
	 //
    TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);
    if (theApp) {
        if (!theApp->Printer)
            theApp->Printer = new TPrinter(GetApplication());

        //
        // Create Printout window and set characteristics.
        //
        APXPrintOut printout(theApp->Printer, Title, GetActiveMDIChild()->GetClientWindow(), true);

        theApp->Printing++;

        //
        // Bring up the Print dialog and print the document.
        //
        theApp->Printer->Print(GetWindowPtr(GetActiveWindow()), printout, true);

        theApp->Printing--;
    }
}


//////////////////////////////////////////////////////////
// TEdMDIClient
// ==========
// Menu File Print Setup command
void TEdMDIClient::CmFilePrintSetup ()
{
    TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);
    if (theApp) {
        if (!theApp->Printer)
            theApp->Printer = new TPrinter(GetApplication());

        //
        // Bring up the Print Setup dialog.
        //
        theApp->Printer->Setup(this);
    }
}


//////////////////////////////////////////////////////////
// TEdMDIClient
// ==========
// Menu File Print Preview command
void TEdMDIClient::CmFilePrintPreview ()
{
    TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);
    if (theApp) {
        if (!theApp->Printer)
            theApp->Printer = new TPrinter(GetApplication());

        theApp->Printing++;

        PreviewWindow *prevW = new PreviewWindow(Parent, theApp->Printer, GetActiveMDIChild()->GetClientWindow(), "Print Preview", new TLayoutWindow(0));
        prevW->Create();

        GetApplication()->BeginModal(GetApplication()->GetMainWindow());

        // We must destroy the preview window explicitly.  Otherwise, the window will not be destroyed until
        // it's parent the MainWindow is destroyed.
        prevW->Destroy();
        delete prevW;

        theApp->Printing--;
    }
}


//////////////////////////////////////////////////////////
// TEdMDIClient
// ==========
// Menu enabler used by Print, Print Setup and Print Preview.
void TEdMDIClient::CmPrintEnable (TCommandEnabler &tce)
{
    if (GetActiveMDIChild()) {
        TEdApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), TEdApp);
        if (theApp) {
            // If we have a Printer already created just test if all is okay.
            // Otherwise create a Printer object and make sure the printer
            // really exists and then delete the Printer object.
            if (!theApp->Printer) {
                theApp->Printer = new TPrinter(GetApplication());
                
                tce.Enable(theApp->Printer->GetSetup().Error == 0);
            } else
                tce.Enable(theApp->Printer->GetSetup().Error == 0);
        }
    } else
        tce.Enable(false);
}


void TEdMDIClient::EvDropFiles (TDropInfo)
{
    Parent->ForwardMessage();
}


