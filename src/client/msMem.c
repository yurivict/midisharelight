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

#ifdef WIN32
#	include <windows.h>
#else
#	include <stdlib.h>
#endif

#include "msMem.h"

/*_________________________________________________________________________*/
/* memory allocation implementation                                        */
/*_________________________________________________________________________*/
FarPtr(void) AllocateMemory (unsigned long size)
{ 
#ifdef WIN32
	return LocalAlloc (LMEM_FIXED, size);
#else
	return (void*)malloc(size);
#endif
}

void DisposeMemory (FarPtr(void) memPtr) 
{
	if (!memPtr) return;
#ifdef WIN32
	LocalFree ((HANDLE)memPtr);
#else
	free(memPtr);
#endif
}

FarPtr(void) AllocateFilter (unsigned long size)
{
	return 0;
}

void FreeFilter (FarPtr(void) filter)
{
	if (filter)
		;
}
