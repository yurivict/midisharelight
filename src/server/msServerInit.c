/*
  Copyright � Grame 2002,2003

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

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "osglue.h"
#include "msCommChans.h"
#include "msServerInit.h"
#include "msSharedMem.h"
#include "msThreads.h"
#include "msLog.h"

static void * gShmem = 0;
static msThreadPtr gMPThread = 0;
static MeetingPointChan gMeetingPoint = 0;
static int gRun = 1;

//___________________________________________________________________
// global initialization
//___________________________________________________________________
static int siglist [] = {
	SIGABRT,
	SIGFPE,
	SIGILL,
	SIGINT,
	SIGSEGV,
	SIGTERM,
#ifndef WIN32
	SIGHUP,
	SIGQUIT,
	SIGBUS,
#endif
	0
};

static cdeclAPI(void) sigActions (int sig)
{
	LogWrite ("signal %d received", sig);
	LogWrite ("server exit...");
	msServerClose ();
	exit (1);
}

static cdeclAPI(void) msExit ()
{
	gRun = 0;
	if (gMeetingPoint) msThreadDelete (gMPThread);
	gMPThread = 0;
	if (gMeetingPoint) CloseMeetingPoint (gMeetingPoint);
	gMeetingPoint = 0;
	if (gShmem) msSharedMemDelete (gShmem);
	gShmem = 0;
}

void InitSignal ()
{
#ifndef WIN32
	int * sigs = siglist;

	while (*sigs) {
		struct sigaction sa;
		sa.sa_handler = sigActions;
		sigemptyset (&sa.sa_mask);
		sa.sa_flags = 0; 			//SA_RESETHAND;
		sigaction (*sigs++, &sa, 0);
	}
#endif
}

void * InitShMem (int shmemSize)
{
	gShmem = msSharedMemCreate(kShMemId, shmemSize);
	if (!gShmem) {
		LogWriteErr ("Can't initialize the shared memory segment");
		return 0;
	}
	atexit (msExit);
	return gShmem;
}

//___________________________________________________________________
// meeting point management thread
//___________________________________________________________________
static ThreadProc(mainServerCom, ptr)
{
	int tolerate = 3;
	NewClientProcPtr newclientproc = (NewClientProcPtr)ptr;
	gMeetingPoint = CreateMeetingPoint ();
	if (!gMeetingPoint) {
		LogWriteErr ("MeetingPoint thread: can't create the meeting point");
		goto err;
	}

	while (gRun) {
		CommunicationChan cc = HandleCommunicationChannelRequest(gMeetingPoint);
		if (cc) {
			newclientproc(cc);
		}
		else if (!tolerate--) goto err;
	}
	return 0;
err:
	if (gRun) LogWriteErr ("MeetingPoint thread: chan request error");
	msExit ();
	exit (1);
}

int InitMeetingPoint (NewClientProcPtr proc)
{
	if (!proc) return 0;

	gMPThread = msThreadCreate (mainServerCom, proc, kServerHighPriority);
	if (!gMPThread) {
		LogWriteErr ("InitMeetingPoint: can't create a new thread");
		return 0;
	}
	return 1;
}

void msServerClose ()
{
	msExit();
}