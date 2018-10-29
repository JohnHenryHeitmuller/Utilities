#if !defined(__editfile_h)              // Sentry, use file only if it's not already included.
#define __editfile_h

/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         editfile.h
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Class definition for TEdFile ().
*/
#include <windows.h>
#pragma hdrstop
#include "ederror.h"

class TEdFile
{
public:
	TEdFile(PCSTR _name = NULL);
	~TEdFile();

	virtual void Read( PBYTE buf );
	virtual void Write( PBYTE buf );
	virtual BOOL GetSize( DWORD& size);
	virtual BOOL Changed();
	virtual void Lock();
	virtual void Unlock();
	virtual void Close();

private:
	BOOL						locked;
	HANDLE 					hdl;
	WIN32_FIND_DATA 		info;
	PCSTR  					name;
};

#endif                                      // __editfile_h sentry.
