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

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "TLog.h"

#define kMaxTimeString	30

//__________________________________________________________________________
TLog::TLog (const char * logpath)
{
	fLogFile = 0;
	if (logpath) Open (logpath);
}

//__________________________________________________________________________
char * TLog::DateString (char * buff, short len)
{
	time_t t;
	time(&t);
	strftime (buff, len, "[%D %T]", localtime(&t));
	return buff;
}

//__________________________________________________________________________
void TLog::Open (const char *logpath)
{
	Close ();
	if (logpath)
		fLogFile = fopen (logpath, "a");
}

//__________________________________________________________________________
void TLog::Close ()
{
	if (fLogFile) fclose (fLogFile);
	fLogFile = 0;
}

//__________________________________________________________________________
void TLog::Write (const char *msg)
{
	if (fLogFile) {
		char buff[kMaxTimeString];
		fprintf (fLogFile, "%s %s\n", DateString (buff, kMaxTimeString), msg);
	}
	else fprintf (stderr, "%s\n", msg);
}

//__________________________________________________________________________
void TLog::WriteErr (const char *msg)
{
	if (fLogFile) {
		char buff[kMaxTimeString];
		fprintf (fLogFile, "%s %s %s\n", DateString (buff, kMaxTimeString), msg, ErrorString());
	}
	else fprintf (stderr, "%s %s\n", msg, ErrorString());
}

//__________________________________________________________________________
char * TLog::DefaultDir (char *buff, int size)
{
	strncpy (buff, "/var/log", size);
	return buff;
}
