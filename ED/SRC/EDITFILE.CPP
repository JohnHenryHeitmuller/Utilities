/*  Project ed

	 Copyright © 1995. All Rights Reserved.

	 SUBSYSTEM:    ed.exe Application
	 FILE:         edwindow.cpp
	 AUTHOR:       John H. Heitmuller


	 OVERVIEW
	 ========
	 Source file for implementation of TEdFile ().
*/

#include <mem.h>
#include "editfile.h"

TEdFile::TEdFile( PCSTR _name)
{
	name   = _name;
	hdl    = INVALID_HANDLE_VALUE;
	locked = FALSE;
}

TEdFile::~TEdFile()
{
	if(hdl != INVALID_HANDLE_VALUE)
		CloseHandle(hdl);
}

void TEdFile::Close()
{
	if(hdl != INVALID_HANDLE_VALUE)
		CloseHandle(hdl);
	hdl = INVALID_HANDLE_VALUE;
}

void TEdFile::Lock()
{
	Close();
	hdl = CreateFile( name, GENERIC_READ | GENERIC_WRITE,
							0 /* prevent share, this locks file*/,
							NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if( hdl == INVALID_HANDLE_VALUE)
		throw edEXCEPTION( FILEOPEN_FAILED, edWINAPI | edCONTINUABLE);
	locked = TRUE;
}

void TEdFile::Unlock()
{
	Close();
	locked = FALSE;
}

void  TEdFile::Read( PBYTE buf )
{
	BOOL  callClose=FALSE, ret;
	DWORD size, bytesRead;

	GetSize(size);
	if( IsBadWritePtr( buf, size) )
		throw edEXCEPTION( BUFFER_TOO_SMALL, edWINAPI | edCONTINUABLE);
	if(!size)
	{
		buf[0] = NULL;
		return;
	}
	if( hdl == INVALID_HANDLE_VALUE)
	{
		hdl = CreateFile( name, GENERIC_READ, 0,
							NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if( hdl == INVALID_HANDLE_VALUE)
			throw edEXCEPTION( FILEOPEN_FAILED, edWINAPI | edCONTINUABLE);
		callClose = TRUE;
	}
	ret = ReadFile( hdl, buf, size, &bytesRead, NULL);
	if( callClose )
		Close();
	if( ret == FALSE || bytesRead != size)
		throw edEXCEPTION( FILEREAD_FAILED, edWINAPI | edCONTINUABLE);
}

void 	TEdFile::Write( PBYTE /*buf*/ )
{
}

BOOL TEdFile::GetSize(DWORD& size)
{
	if( FindFirstFile( name, &info) == INVALID_HANDLE_VALUE)
	{
		size = 0;
		return(FALSE);
	}
	size = info.nFileSizeLow;
	return(TRUE);
}

BOOL  TEdFile::Changed()
{
	FILETIME lastTime = info.ftLastWriteTime;
	if( FindFirstFile( name, &info) != INVALID_HANDLE_VALUE)
	{
		if( memcmp( (char*)&(info.ftLastWriteTime), (char*)&lastTime, sizeof(FILETIME))==0)
			return(FALSE);
	}
	return(TRUE);
}

