/*
  Copyright � Grame 2002

  This library is free software; you can redistribute it and modify it under 
  the terms of the GNU Library General Public License as published by the 
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License 
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  grame@grame.fr
  
  modifications history:
 
*/

#include "TPipe.h"

#define PipeErrCode		INVALID_HANDLE_VALUE
#define CreateMode		PIPE_ACCESS_OUTBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE
#define kBuffSize		1024

#ifndef FILE_FLAG_FIRST_PIPE_INSTANCE
#define FILE_FLAG_FIRST_PIPE_INSTANCE 0x00080000 
#endif 

//_____________________________________________________________________
TPipe::TPipe ()
{
	fPipe = PipeErrCode;
	fBuffSize = 0;
	fOwner = FALSE;
}

//_____________________________________________________________________
int TPipe::Create (const char * name)
{
	fPipe = CreateNamedPipe (name, CreateMode, 
						PIPE_TYPE_BYTE|PIPE_READMODE_BYTE, 
						PIPE_UNLIMITED_INSTANCES, kBuffSize, kBuffSize,
						NMPWAIT_USE_DEFAULT_WAIT, NULL);
	if (fPipe == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	fBuffSize = kBuffSize;
	fOwner = TRUE;
	SetName (name);
	return TRUE;
}

//_____________________________________________________________________
void TPipe::Close ()
{
	if (fPipe == PipeErrCode) return;
	if (fOwner) {
		FlushFileBuffers (fPipe);
		DisconnectNamedPipe (fPipe);
	}
    CloseHandle (fPipe);
	fPipe = PipeErrCode;
	fBuffSize = 0;
	fOwner = FALSE;
}

//_____________________________________________________________________
int TPipe::Open (const char *name, int perm)
{
	switch (perm) {
		case kReadWritePerm:
			perm = GENERIC_READ | GENERIC_WRITE;
			break;
		case kWritePerm:
			perm = GENERIC_WRITE;
			break;
		default:
			perm = GENERIC_READ;
	}
	if (fOwner) {
		if (ConnectNamedPipe (fPipe, NULL))
			return TRUE;
		if (GetLastError() == ERROR_PIPE_CONNECTED)
			return TRUE;
	}
	else {
		fPipe = CreateFile (name, perm, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (fPipe != INVALID_HANDLE_VALUE) {
			SetName (name);
			return TRUE;
		}
	}
	return FALSE;
}

//____________________________________________________________
long TPipe::Write (void *buff, long len)
{
	DWORD written;
	BOOL ret = WriteFile (fPipe, buff, len, &written, NULL);
	return ret ? written : 0;
}

//____________________________________________________________
long TPipe::Read (void *buff, long len)
{
	DWORD read;
	BOOL ret = ReadFile (fPipe, buff, len, &read, NULL);
	return ret ? read : 0;
}