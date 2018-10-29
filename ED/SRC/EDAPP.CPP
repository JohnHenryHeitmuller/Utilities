/*  Project ed
    
    Copyright © 1995. All Rights Reserved.

    SUBSYSTEM:    ed.exe Application
    FILE:         edapp.cpp
    AUTHOR:       John H. Heitmuller


    OVERVIEW
    ========
    Source file for implementation of TEdApp (TApplication).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include <dir.h>

#include "edapp.h"
#include "mdiclnt.h"
#include "aboutdlg.h"                        // Definition of about dialog.       


//
// Generated help file.
//
const char HelpFileName[] = "ed.hlp";


// Drag / Drop support:
TFileDrop::TFileDrop (char* fileName, TPoint& p, bool inClient, TModule*)
{
    char    exePath[MAXPATH];
    
    exePath[0] = 0;
    FileName = strcpy(new char[strlen(fileName) + 1], fileName);
    Point = p;
    InClientArea = inClient;
}

TFileDrop::~TFileDrop ()
{
    delete FileName;
}

const char *TFileDrop::WhoAmI ()
{
  return FileName;
}


//{{TEdApp Implementation}}


//
// Build a response table for all messages/commands handled
// by the application.
//
DEFINE_RESPONSE_TABLE1(TEdApp, TApplication)
//{{TEdAppRSP_TBL_BEGIN}}
    EV_COMMAND(CM_HELPCONTENTS, CmHelpContents),
    EV_COMMAND(CM_HELPUSING, CmHelpUsing),
    EV_COMMAND(CM_HELPABOUT, CmHelpAbout),
    EV_WM_DROPFILES,
    EV_WM_WININICHANGE,
//{{TEdAppRSP_TBL_END}}
END_RESPONSE_TABLE;


//////////////////////////////////////////////////////////
// TEdApp
// =====
//
TEdApp::TEdApp () : TApplication("ED")
{
    HelpState = false;
    ContextHelp = false;
    HelpCursor = 0;

    Printer = 0;
    Printing = 0;

    // INSERT>> Your constructor code here.
}


TEdApp::~TEdApp ()
{
    if (Printer)
        delete Printer;

    // INSERT>> Your destructor code here.
}


bool TEdApp::CanClose ()
{
    bool result = TApplication::CanClose();

    //
    // Close the help engine if we used it.
    //
    if (result && HelpState)
        GetMainWindow()->WinHelp(HelpFileName, HELP_QUIT, 0L);
 
    return result;
}


void TEdApp::SetupSpeedBar (TDecoratedMDIFrame *frame)
{ 
    //
    // Create default toolbar New and associate toolbar buttons with commands.
    //   
    TControlBar* cb = new TControlBar(frame);
    cb->Insert(*new TButtonGadget(CM_MDIFILENEW, CM_MDIFILENEW));
    cb->Insert(*new TButtonGadget(CM_MDIFILEOPEN, CM_MDIFILEOPEN));
    cb->Insert(*new TButtonGadget(CM_FILESAVE, CM_FILESAVE));
    cb->Insert(*new TSeparatorGadget(6));
    cb->Insert(*new TButtonGadget(CM_EDITCUT, CM_EDITCUT));
    cb->Insert(*new TButtonGadget(CM_EDITCOPY, CM_EDITCOPY));
    cb->Insert(*new TButtonGadget(CM_EDITPASTE, CM_EDITPASTE));
    cb->Insert(*new TSeparatorGadget(6));
    cb->Insert(*new TButtonGadget(CM_EDITUNDO, CM_EDITUNDO));
    cb->Insert(*new TSeparatorGadget(6));
    cb->Insert(*new TButtonGadget(CM_EDITFIND, CM_EDITFIND));
    cb->Insert(*new TButtonGadget(CM_EDITFINDNEXT, CM_EDITFINDNEXT));
    cb->Insert(*new TSeparatorGadget(6));
    cb->Insert(*new TButtonGadget(CM_FILEPRINT, CM_FILEPRINT));
    cb->Insert(*new TButtonGadget(CM_FILEPRINTPREVIEW, CM_FILEPRINTPREVIEW));
    cb->Insert(*new TSeparatorGadget(6));
    cb->Insert(*new TButtonGadget(CM_HELPCONTENTS, CM_HELPCONTENTS));

    // Add fly-over help hints.
    cb->SetHintMode(TGadgetWindow::EnterHints);

    frame->Insert(*cb, TDecoratedFrame::Top);
}


//////////////////////////////////////////////////////////
// TEdApp
// =====
// Application intialization.
//
void TEdApp::InitMainWindow ()
{
    if (nCmdShow != SW_HIDE)
        nCmdShow = (nCmdShow != SW_SHOWMINNOACTIVE) ? SW_SHOWNORMAL : nCmdShow;

    mdiClient = new TEdMDIClient;
    TDecoratedMDIFrame* frame = new TDecoratedMDIFrame(Name, MDI_MENU, *mdiClient, true);

    // Set the client area to the application workspace color.
    frame->SetBkgndColor(::GetSysColor(COLOR_APPWORKSPACE));

    //
    // Assign ICON w/ this application.
    //
    frame->SetIcon(this, IDI_MDIAPPLICATION);

    //
    // Menu associated with window and accelerator table associated with table.
    //
    frame->AssignMenu(MDI_MENU);
    
    //
    // Associate with the accelerator table.
    //
    frame->Attr.AccelTable = MDI_MENU;

    SetupSpeedBar(frame);

    TStatusBar *sb = new TStatusBar(frame, TGadget::Recessed,
                                    TStatusBar::CapsLock        |
                                    TStatusBar::NumLock         |
                                    TStatusBar::ScrollLock      |
                                    TStatusBar::Overtype);
    frame->Insert(*sb, TDecoratedFrame::Bottom);
  
    SetMainWindow(frame);

    frame->SetMenuDescr(TMenuDescr(MDI_MENU));

    //
    // Windows 3-D controls.
    //
    EnableCtl3d(true);
}


//////////////////////////////////////////////////////////
// TEdApp
// =====
// Menu Help Contents command
void TEdApp::CmHelpContents ()
{
    //
    // Show the help table of contents.
    //
    HelpState = GetMainWindow()->WinHelp(HelpFileName, HELP_CONTENTS, 0L);
}


//////////////////////////////////////////////////////////
// TEdApp
// =====
// Menu Help Using Help command
void TEdApp::CmHelpUsing ()
{
    //
    // Display the contents of the Windows help file.
    //
    HelpState = GetMainWindow()->WinHelp(HelpFileName, HELP_HELPONHELP, 0L);
}


//////////////////////////////////////////////////////////
// TEdApp
// ===========
// Menu Help About ed.exe command
void TEdApp::CmHelpAbout ()
{
    //
    // Show the modal dialog.
    //
    TEdAboutDlg(MainWindow).Execute();
}


void TEdApp::InitInstance ()
{
    TApplication::InitInstance();

    // Accept files via drag/drop in the frame window.
	 GetMainWindow()->DragAcceptFiles(true);
    GetSystemInfo( &sysInfo );
}


void TEdApp::EvDropFiles (TDropInfo drop)
{
    // Number of files dropped.
    int totalNumberOfFiles = drop.DragQueryFileCount();

    TFileList* files = new TFileList;

    for (int i = 0; i < totalNumberOfFiles; i++) {
        // Tell DragQueryFile the file interested in (i) and the length of your buffer.
        int     fileLength = drop.DragQueryFileNameLen(i) + 1;
        char    *fileName = new char[fileLength];

        drop.DragQueryFile(i, fileName, fileLength);

        // Getting the file dropped. The location is relative to your client coordinates,
        // and will have negative values if dropped in the non client parts of the window.
        //
        // DragQueryPoint copies that point where the file was dropped and returns whether
        // or not the point is in the client area.  Regardless of whether or not the file
        // is dropped in the client or non-client area of the window, you will still receive
        // the file name.
        TPoint  point;
        bool    inClientArea = drop.DragQueryPoint(point);
        files->Add(new TFileDrop(fileName, point, inClientArea, this));
    }

    // Open the files that were dropped.
    AddFiles(files);

    // Release the memory allocated for this handle with DragFinish.
    drop.DragFinish();
}

#pragma warn -aus
void TEdApp::AddFiles (TFileList* files)
{
	 // Open all files dragged in.
	 TFileListIter fileIter(*files);

	 TFrameWindow *tfw = TYPESAFE_DOWNCAST(GetMainWindow(), TFrameWindow);
	 if (tfw) {
		  TEdMDIClient *theClient = TYPESAFE_DOWNCAST(tfw->GetClientWindow(), TEdMDIClient);

		  if (theClient)
				while (fileIter) {
					 theClient->OpenFile(fileIter.Current()->WhoAmI());
					 fileIter++;
				}
	 }
}
#pragma warn +aus

bool TEdApp::ProcessAppMsg (MSG& msg)
{
    if (msg.message == WM_COMMAND) {
        if (ContextHelp || (::GetKeyState(VK_F1) < 0)) {
            ContextHelp = false;
            GetMainWindow()->WinHelp(HelpFileName, HELP_CONTEXT, msg.wParam);
            return true;
        }
    } else
        switch (msg.message) {
        case WM_KEYDOWN:
            if (msg.wParam == VK_F1) {
                // If the Shift/F1 then set the help cursor and turn on the modal help state.
                if (::GetKeyState(VK_SHIFT) < 0) {
                    ContextHelp = true;
                    HelpCursor = ::LoadCursor(GetMainWindow()->GetModule()->GetInstance(), MAKEINTRESOURCE(IDC_HELPCURSOR));
                    ::SetCursor(HelpCursor);
                    return true;        // Gobble up the message.
                } else {
                    // If F1 w/o the Shift key then bring up help's main index.
                    GetMainWindow()->WinHelp(HelpFileName, HELP_INDEX, 0L);
                    return true;        // Gobble up the message.
                }
            } else {
                if (ContextHelp && (msg.wParam == VK_ESCAPE)) {
                    if (HelpCursor)
                        ::DestroyCursor(HelpCursor);
                    ContextHelp = false;
                    HelpCursor = 0;
                    GetMainWindow()->SetCursor(0, IDC_ARROW);
                    return true;    // Gobble up the message.
                }
            }
            break;

        case WM_MOUSEMOVE:
        case WM_NCMOUSEMOVE:
            if (ContextHelp) {
                ::SetCursor(HelpCursor);
                return true;        // Gobble up the message.
            }
            break;

        case WM_INITMENU:
            if (ContextHelp) {
                ::SetCursor(HelpCursor);
                return true;        // Gobble up the message.
            }
            break;
        
        case WM_ENTERIDLE:
            if (msg.wParam == MSGF_MENU)
                if (GetKeyState(VK_F1) < 0) {
                    ContextHelp = true;
                    GetMainWindow()->PostMessage(WM_KEYDOWN, VK_RETURN, 0L);
                    return true;       // Gobble up the message.
                }
            break;
        
        default:
            ;
        };  // End of switch

    // Continue normal processing.

    return TApplication::ProcessAppMsg(msg);
}


void TEdApp::EvWinIniChange (char far* section)
{
    if (strcmp(section, "windows") == 0) {
        // If the device changed in the WIN.INI file then the printer
        // might have changed.  If we have a TPrinter (Printer) then
        // check and make sure it's identical to the current device
        // entry in WIN.INI.
        if (Printer) {
            char printDBuffer[255];
            LPSTR printDevice = printDBuffer;
            LPSTR devName;
            LPSTR driverName = 0;
            LPSTR outputName = 0;
        
            if (::GetProfileString("windows", "device", "", printDevice, sizeof(printDevice))) {
                // The string which should come back is something like:
                //
                //      HP LaserJet III,hppcl5a,LPT1:
                //
                // Where the format is:
                //
                //      devName,driverName,outputName
                //
                devName = printDevice;
                while (*printDevice) {
                    if (*printDevice == ',') {
                        *printDevice++ = 0;
                        if (!driverName)
                            driverName = printDevice;
                        else
                            outputName = printDevice;
                    } else
                        printDevice = ::AnsiNext(printDevice);
                }

                if ((Printer->GetSetup().Error != 0)                                ||
                    (strcmp(devName, Printer->GetSetup().GetDeviceName()) != 0)    ||
                    (strcmp(driverName, Printer->GetSetup().GetDriverName()) != 0) ||
                    (strcmp(outputName, Printer->GetSetup().GetOutputName()) != 0)) {
                
                    // New printer installed so get the new printer device now.
                    delete Printer;
                    Printer = new TPrinter(this);
                }
            } else {
                // No printer installed (GetProfileString failed).
                delete Printer;
                Printer = new TPrinter(this);
            }
        }
    }
}


int OwlMain (int , char* [])
{
    try {
        TEdApp    app;
        return app.Run();
    }
    catch (xmsg& x) {
        ::MessageBox(0, x.why().c_str(), "Exception", MB_OK);
    }

    return -1;
}
