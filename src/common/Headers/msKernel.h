/*

  Copyright � Grame 1999-2002

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
   [08-09-99] DF - adaptation to the new memory management
   [04-08-02] DF - memory organization in private and public sections

*/

#ifndef __msKernel__
#define __msKernel__

#include "lffifo.h"
#include "msDefs.h"
#include "msAppls.h"
#include "msDriver.h"
#include "msTypes.h"
#include "msMemory.h"
#include "msSorter.h"

/*------------------------------------------------------------------------*/
/* data types                                                             */
/*------------------------------------------------------------------------*/
typedef struct TMSGlobalPublic {
	unsigned long  	time;      /* the current 32 bits (milliseconds) date */
	short 			version;   /* the current kernel version              */
	unsigned long  	size;      /* the current public segment size         */
	TClientsPublic 	clients;   /* clients applications information        */
} TMSGlobalPublic;

typedef struct TMSGlobal FAR *  TMSGlobalPtr;

/*------------------------------------------------------------------------*/
/* public fields access macros                                            */
/*------------------------------------------------------------------------*/
#define CurrTime(g)         pub(g, time)
#define Version(g)          pub(g, version)
#define Size(g)             pub(g, size)

/* common fields access macros */
#define Memory(g)           (&g->memory)
#define Clients(g)          (&g->clients)

#ifndef MSKernel

	typedef struct TMSGlobal {
		TMSGlobalPublic * pub;
		TMSMemory     memory;          /* kernel memory management        */
		TApplPtr      appls[MaxAppls]; /* clients applications management */
    	TApplContextPtr context;       /* system dependent context        */
	} TMSGlobal;

#else

	typedef struct THorloge  FAR *  THorlogePtr;
	typedef FarPtr(void)			THost;   /* reserved for platform dependant
	                                            storage */

/*------------------------------------------------------------------------*/
/* realtime clock */
	typedef struct {
		long	sec;
		long	usec;
	} TimeInfo, *TimeInfoPtr;

	typedef struct THorloge{          /* time management (no public section) */
		 long           reenterCount; /* count of clockHandler reenters      */
		 short          timeMode;     /* indicates the time management mode  */		
		 short          timeRes ;     /* define the time resolution (in ms)  */		
	} THorloge;

	typedef struct TMSGlobal {
		TMSGlobalPublic * pub;
		TMSMemory     memory;        /* kernel memory management            */
		THorloge      clock;         /* time management (no public section) */
		TClients      clients;       /* clients applications management     */
		TSorter       sorter;        /* sorter specific storage             */
		fifo          toSched;       /* events to be scheduled              */
		THost         local;         /* for implementation specific purpose */
        short		 running;
	} TMSGlobal;

/*--------------------------------------------------------------------------*/
/* fields access macros                                                     */
/*--------------------------------------------------------------------------*/
#	define SorterList(g)       (&g->toSched)
#	define Sorter(g)           (&g->sorter)
//#	define TimeOffset(g)       (g->clock.rtOffset)
#	define Appls(g)       	   (g->clients.appls)
#	define ActiveAppl(g)       (g->clients.activesAppls)
#	define NextActiveAppl(g)   (g->clients.nextActiveAppl)

//#	define kClockAdjustCount	1000

/*--------------------------------------------------------------------------*/
/* function declaration                                                     */
/*--------------------------------------------------------------------------*/
	void ClockHandler (TMSGlobalPtr g);
#endif

#endif
