/*
	OMSDriver.h
	
	Driver interface for Open Music System
	Doug Wyatt, Opcode Systems
	Copyright �1990-95 Opcode Systems, Inc., All Rights Reserved
*/
#ifndef __OMSDriver__
#define __OMSDriver__
#pragma once

#include "OMS.h"



/*
	Messages to OMdv driver code resource:
		pascal long OMdv(short msg, long par1, long par2);
*/
enum {
	omdvInit				= 0,	/* par1: OMSFileSpec *file
										return OSErr */
	omdvDispose				= 1,	/* no parameters */
	omdvAddDevices			= 2,	/* search for interfaces/cards:
									if compat level 0
										par1: OMSDvrAdd1DevProc0UPP
										par2: Byte *portsUsed (0=modem, 1=printer...)
									if compat level >= 1
										par1: OMSDvrAdd1DevProc1
										par2: OMSAddDevParams */
	omdvConfigure			= 3,	/* config dialog */
	omdvSetInterfaceList	= 4,	/* par1: list of interfaces */
	omdvGetMenu				= 5,	/* return MenuHandle or null */
	omdvDoMenu				= 6,	/* par1: menu item number */
	omdvCloseUserInterface	= 7,
	omdvStartMIDI			= 16,	/* par1: port usage */
	omdvStopMIDI			= 17,
	omdvGetPortSendProc		= 18,	/*	par1: OMSPortID *
										par2: OMSSendParams *,
									should return send proc & param */
	omdvSetPortReceiveRefNum = 19,	/* par1: ptr to OMSPortID,
										par2: low word=refNum, high word=uniqueID in 2.0 */
	omdvStartupComplete		= 30,
	omdvStartMIDI2			= 35,
	omdvClosedMIDISetup		= 36,
	omdvStudioSetupChanged	= 37,
	omdvTestDevice			= 39,
	omdvDifferentStudioSetup = 40,
	omdvRemoveOutput		= 41,	/* par1: ptr to OMSPortID */
	omdvConnectsChanged		= 42,	/* par1: OMSConnectionListH */
	omdvGetCommSpeed		= 43	/* par1: OMSPortID *, return speed in bytes/sec or 0 for 3125 */
};

/*
	Types of error codes passed to OMSSerialDriverErr
*/
enum {
	omdvPortInUseErr = 1,
	omdvXmitStuckErr = 2,
	omdvDriverOutOfMemory = 3,
	omdvOverrunErr = 4,
	omdvFramingErr = 5
};

/*
	WindowKind of driver-owned windows.
*/
#define omsDriverWindowKind 981

/*
	 Bits in OMSDriverParams.flags
	 0x40 is reserved; some 1.1 drivers may have this set
*/
enum {
	kNoSyncRouting 			= 0x80, 
	kUseDeviceInfoDialog	= 0x20,
	kAllowIDEditing			= 0x10,
	kAlwaysLoad				= 0x08,
	kOmitFromAutoSetup		= 0x04
};


TYPEDEF_OMSPROC(long, OMSDriverProc)(short msg, long par1, long par2);
TYPEDEF_OMSPROC(void, OMSDriverEventHandler)(OMSWindowPtr activeDriverWindow, OMSEventRecord *evt);
TYPEDEF_OMSPROC(OMSDeviceH, OMSDvrAdd1DevProc0)(OMSDevice *device);
TYPEDEF_OMSPROC(OMSDeviceH, OMSDvrAdd1DevProc1)(OMSDevice *device, short devSize);
TYPEDEF_OMSPROC(void, OMSSerErrResponseProc)(short portNum, short errNum, short userChoice);



#include "OMSDrvUPPs.h"

#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=mac68k
#endif

/*
	OMSDeviceList - stores lists of interfaces in drivers, lists of driver devices
		to OMS Setup.
*/
typedef struct OMSDeviceList {
	short		numDevices;
	OMSDeviceH	device[20];			/* open-ended; 20 is arbitrary value for debugger */
} OMSDeviceList, ** OMSDeviceListH;


/*
	OMSAddDevParams

	Used for searching for interfaces.
*/
typedef struct OMSAddDevParams {
	unsigned char	*portsUsed;
	unsigned char	*baudRatePerPort;
	OMSBool			addHardwareManually;
} OMSAddDevParams;


/*
	OMSSendParams
	
	Drivers give OMS one of these to describe how to send to a destination.
	If the driver's compatibility level is 0, the procedure is called
		with registers D0 and D1 set up as indicated.
	Otherwise, the procedure must be an OMSReadHook2.  paramD0 is passed as
		the readHookRefCon, paramD1's low word is in pkt->appConnRefCon.
*/
typedef struct OMSSendParams {
	OMSReadHook2UPP	proc;				/* returned by driver */
	long			paramD0, paramD1;	/* returned by driver */
	OMSUniqueID		omsUniqueID;		/* passed by system */
} OMSSendParams;


/*
	Structure of driver's OMdi resource.
*/

typedef struct OMSDriverParams {
	short			id;					/* determines driver load order; assigned by Opcode */
	OMSBool			xxisSmart;
	OMSBool			hasMenuOrWindows;
	short			xxportNumM, xxportNumB;	/* obsolete */
	unsigned char	flags;
	unsigned char	driverCompatibilityLevel;
	unsigned char	reservedFlags[6];
} OMSDriverParams;


/*
	OMSDriverTableEntry
	
	OMS's internal data maintained per driver.
*/
typedef struct OMSDriverTableEntry {
	OMSDriverProcUPP		driverEntryPt;			/* invalid when unloaded */
	char					**driverCode;				/* invalid when unloaded */
	OMSSignature			driverCreator;
	OMSString				driverFileName;
	char					**xxdriverSicns;
	OMSDriverParams			params;					/* always valid */
	OMSDeviceListH			driverInterfaces;		/* invalid when unloaded */
	unsigned char			driverPortUsage[2];		/* 0=not using, 1=unavailable, 2=using it */
	short					xxdriverMenuID;
	OMSBool					driverLoaded;			/* new as of 1.2a19 */
	OMSBool					driverRunning;			/* 1.2b15 */
	short					xxdriverRFOpenCount;	/* 1.2a19 */
	short					xxdriverRFRefNum;		/* 1.2a19 */
} OMSDriverTableEntry;

/* xx fields are obsolete in 2.0 */

/*
	OMSDriverList
*/
typedef struct OMSDriverList {
	short					numDrivers;
	short					driverTableEntrySize;
	OMSDriverTableEntry		driver[1];					/* variable-length */
} OMSDriverList, **OMSDriverListH;
#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=reset
#endif


#ifdef __cplusplus
extern "C" {
#endif

OMSAPI(void)	OMSSerialDriverErr(OMSSerErrResponseProcUPP errorResponse, short portNum, short errNum);

OMSAPI(short) OMSOpenDriverResFile(OMSSignature driverID);

OMSAPI(void)	OMSCloseDriverResFile(OMSSignature driverID);

OMSAPI(void) OMSChangeDriverSendProcs(OMSSignature driverID);

#ifndef powerc
#ifdef __MWERKS__
#pragma parameter OMSReceivedFromPort(__A1, __D0)
#endif
OMSAPI(void)	OMSReceivedFromPort(OMSPacket *pkt, short destRefNum);
#endif

OMSAPI(OMSDriverListH) OMSGetDriverList(void);

#ifdef __cplusplus
}
#endif

#endif /* __OMSDriver__ */
