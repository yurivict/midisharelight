/*
	OMSSerMgr.h
	
	Interfaces to Open Music System's serial manager
	Doug Wyatt, Opcode Systems
	Copyright �1990-95 Opcode Systems, Inc., All Rights Reserved
*/
#ifndef __OMSSerMgr__
#define __OMSSerMgr__
#pragma once


#include "OMSDriver.h"


/*
	Values for clockDivide parameter
*/
enum {
	clk500KHz = 0,
	clk1MHz = 1,
	clk2MHz = 2,
	clkFast = 3
};


/*
	Messages to Osdh serial hardware driver
*/
enum {
	omsSerInit,				/* return number of ports */
	omsSerDispose,
	omsSerPortAvailable,	/* only portID in port is valid */
	omsSerSetUpPort,
	omsSerAllSent,
	omsSerRestorePort,
	omsSerSetClockSpeed,
	omsSerGetPortInfo,		/* port is null, param is SerPortInfoParams */
	omsSerGetPairedPort
};

/*	Return values for OMSSerPortAvail */
enum {
	omsPortAvail,
	omsPortUserDisabled,
	omsPortInUse
};

/*	Error numbers */
enum {
	omsErrUnknownPort = 128,
	omsErrNoPairedPort = 129
};

/*	Messages to handshakeProc */
enum {
	omsSerSendHandshakeByte = 0,
	omsSerResumeXmitAfterXOFF = 1,
	omsSerStopXmitForXOFF = 2,
	omsSerSetXON = 3,
	omsSerSetXOFF = 4,
	omsSerSendXON = 5,
	omsSerSendXOFF = 6,
	omsSerEnableHandshake = 7
};

/* Values of hsByte to handshakeProc, omsSerEnableHandshake message */
enum {
	omsSerNoHandshake = 0,
	omsSerHandshakeInput = 1,
	omsSerHandshakeOutput = 2,
	omsSerHandshakeInputOutput = 3
};


#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=mac68k
#endif

/*
	Queues
*/
typedef struct OMSQueue {
	unsigned short	nitems;		/* make first since most frequently accessed */
	unsigned short	qhead;
	unsigned short	qtail;
	unsigned short	qsize;		/* always a multiple of 2 */
	unsigned short	qsizeMinus1;	/* so masking with this is easy way to wrap around */
	unsigned char	data[1];	/* variable-sized */
} OMSQueue;

#define QueueEmpty(qp) (qp->nitems == 0)
#define FlushQueue(qp) (qp->qhead = qp->qtail = qp->nitems = 0)

struct OMSSerialPort;

/* These procptrs are all C procedures -- sorry, not pascal */
typedef long (*OMSSerDrvrProc)(short msgNum, struct OMSSerialPort *port, long param);
typedef void (*OMSVBLProc)(struct OMSSerialPort *port);
typedef void (*OMSSerSendDataProc)(struct OMSSerialPort *port, unsigned char *data, short len);
typedef void (*OMSSerRcvByteProc)(struct OMSSerialPort *port, unsigned char rcvByte);
typedef void (*OMSSerSpecialRcvProc)(struct OMSSerialPort *port, OMSBool forceEnqueueing);
typedef void (*OMSSerHandshakeProc)(struct OMSSerialPort *port, short msg, unsigned char hsByte);

#include "OMSSerUPPs.h"

typedef struct OMSSerialPort {
	/* Variables owned by the Serial manager */
	/* Procedures linking MIDI driver and serial driver */
	OMSSerSendDataProcUPP	sendDataProc;	/* proc in hw driver for sending packets */
	OMSSerRcvByteProcUPP	rcvByteProc;	/* MIDI driver proc called when byte received */
	OMSSerSpecialRcvProcUPP	specialRcvProc;	/* used for forcing queueing of input */
	OMSSerHandshakeProcUPP	handshakeProc;	/* MIDI driver can call this to restart sending
												when using software handshaking. */
	
	/* general */
	struct OMSSerialPort *nextPort;		/* chain link, used by driver manager */
	short			globalPortNum;		/* across all serial drivers */
	OMSSerPortID	portID;
	OMSBool			portInitialized;
	OMSBool			usingPort;			/* initialized and not stuck */
	short			clockSpeed;			/* last speed SCC programmed to */
	unsigned short	myTimeDBRA;			/* same as TimeDBRA, but valid even on machines which
											don't have TimeDBRA */
	OMSVBLProcUPP		vblProc;		/* For VBL tasks in MIDI driver */
	long				driverVar;		/* for use of driver */
	OMSSerDrvrProcUPP	hwDriverProc;	/* main message-handler of hardware driver */
	
	/* transmitting */
	OMSQueue		*xmtQ;				/* transmit queue */
	OMSBool			xoffSendingSuspended;
	
	/* receiving */
	unsigned char	serialErr;			/* posted in rcverr ISR, cleared in VBL task */
	OMSQueue 		*rcvQ;				/* receive queue */
	OMSBool			xoffReceivingSuspended;	/* for convenience and orthogonality; serial
												drivers don't touch */
	
	/* no generic code touches packet, but it's of universal applicability */
	OMSMIDIPacket	packet;				/* may accumulate received data here */

	/* Variables owned by the hardware driver -- must not be touched by MIDI drivers!! */
	unsigned char	*hwSCCRCtl;			/* SCCRBase + xCtl */
	unsigned char	*hwSCCWCtl;			/* SCCWBase + xCtl */
	unsigned char	*hwSCCWData;		/* SCCWBase + xData */
	OMSProcPtr		hwVector[4];		/* modem/printer uses these for saved vectors
											nubus cards may use these as actual vectors */
	OMSBool			hwSending;
	OMSBool			hwReceiving;
	OMSBool			needToSendHandshake;
	unsigned char	handshakeByteToSend;
	unsigned char	xonByte;
	unsigned char	xoffByte;
	unsigned char	hsEnable;
	unsigned char	reserved[13];
} OMSSerialPort, *OMSSerialPortPtr;


/*
	SerPortInfoParams - used in omsSerGetPortInfo message to serial hardware
	driver.
*/
typedef struct SerPortInfoParams {
	OMSSerPortID	portID;
	OMSBool			looped;
	short			locIconID;
	OMSStringPtr	shortLocName;
	OMSStringPtr	fullLocName;
} SerPortInfoParams;

#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=reset
#endif


#ifdef __cplusplus
extern "C" {
#endif
OMSAPI(short)	OMSSerGetNumPorts(void);
OMSAPI(void)	OMSSerGetIndPort(short globalPortNum, OMSSerPortID *portID);
					/* globalPortNum is zero-based */
OMSAPI(short)	OMSSerPortIDToPortNum(OMSSerPortID portID);
OMSAPI(OMSErr)	OMSSerGetPortInfo(OMSSerPortID portID, OMSBool looped, 
					OMSDevice *devInfo, OMSStringPtr shortLocName);
OMSAPI(OMSErr)	OMSSerGetPairedPort(OMSSerPortID portID, OMSSerPortID *itsPairedPortID);
#if OMS_MACINTOSH
OMSAPI(void)	OMSSerGetIcon(OMSSerPortID portID, short locationIconID, char *sicn);
#endif
OMSAPI(OMSIcon)	OMSSerGetCIcon(OMSSerPortID portID, short locationIconID, char iconType, OMSPoint *iconSize);
OMSAPI(char)	OMSSerPortInUse(OMSSerPortID portID);

OMSAPI(OMSErr)	OMSSerSetUpPort(OMSSerialPort *port, OMSSerPortID portID,
					short xmitQueueSize, short rcvQueueSize, 
					short clockDivideOrBaud, OMSSerRcvByteProcUPP rcvByteProc);
OMSAPI(void)	OMSSerRestorePort(OMSSerialPort *port);
OMSAPI(void)	OMSSerWaitForXQueueEmpty(OMSSerialPort *port);
OMSAPI(void)	OMSSerSetPortSpeed(OMSSerialPort *port, short clockDivideOrBaud,
					OMSSerRcvByteProcUPP rcvByteProc);
#ifdef __cplusplus
}
#endif

#endif /* __OMSSerMgr__ */
