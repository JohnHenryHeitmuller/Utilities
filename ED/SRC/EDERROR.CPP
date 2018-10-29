/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         edwindow.cpp
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Source file for implementation of TEdException ().
*/
#include "ederror.h"

#ifdef edDEBUG
	TEdException::TEdException( DWORD _error, UINT _type, PCSTR _module, UINT _line)
#else
	TEdException::TEdException( DWORD _error, UINT _type)
#endif
	{
		error  = _error;
		type   = _type;
#ifdef edDEBUG
		module = _module;
		line   = _line;
#endif
	}


#ifdef edDEBUG
int TEdException::DisplayMessage()
{  // \nModule:\tXXXXXXXX.XXX\nLine:\t9999999999\nError::\t999999999\0
	char szMsg[256+64];
	int len;
	if( type &= edWINAPI )
	{
		DWORD lastError = GetLastError();
		len = FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, lastError,
											NULL, szMsg, sizeof(szMsg)-64, NULL);
	}
	wsprintf( &szMsg[len], "\nModule:\t%s\nLine:\t%d\nError:\t%ld", module, line, error);
//	return( MessageBox( ghAppWin, szMsg, "FAPITEST EXCEPTION",
//							 MB_APPLMODAL | MB_ICONSTOP | MB_OK));
	return(0);
}
#endif