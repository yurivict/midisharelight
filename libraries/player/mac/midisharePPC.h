#define _H_MidiShare

#ifndef __MidiShare__
#define __MidiShare__

#ifndef THINK_C
#ifndef __TYPES__
#include <Types.h>
#endif
#endif

#include <MixedMode.h>

#ifndef __MIDISHAREPPC_H__
#define __MIDISHAREPPC_H__


/*****************************************************************************
 *                                MIDI SHARE									
 *----------------------------------------------------------------------------
 * MidiShare is a multi-tasking, real-time software environment, specially 
 * devised for the developing of MIDI applications with a triple target :
 * 
 * 	�To propose solutions to currently met problems when developing 
 * 	 a real-time MIDI application : memory management, communication management, 
 *	 time management, task management. 
 * 
 * 	�To enable the real-time and multi-tasking functioning of these applications, 
 * 	 i.e. to enable the sharing of all the necessary resources and their 
 * 	 simultaneous access.
 *
 * 	�To make easier cooperation between independent MIDI applications by  proposing 
 * 	 a real-time mechanism of inter-application communications.
 * 
 * This file contains a complete description of all the MidiShare functions and 
 * procedures, as well as all the data structures in use.
 *----------------------------------------------------------------------------
 * 		            � GRAME 1989, 1990, 1991, 1992 
 *	          [Yann Orlarey, Herv� Lequay, Dominique fober]						
 *----------------------------------------------------------------------------
 *
 *	version 1.20 
 *	version Lightspeed C version 3.01 G. Bloch Aout 1989 (modif YO 9-9-89)
 *	version Think C 4.0 : YO [13-11-89]
 *  extensions t�ches diff�r�es : YO [05-12-89]
 *	version MPW C++ 3.1 : YO [09-03-90]
 *	harmonisation prototypes: YO [12-05-90]
 *	harmonisation MPW & TC: YO [12-05-90]
 *	impl�mentation de 'MidiShare()' sous forme de macro: YO [15-03-91]
 *  english version : YO [29-01-92]
 *    PPC version :  SL [11-06-95]
******************************************************************************/

/*******************************************************************************
 * 							MIDISHARE EVENTS									
 *------------------------------------------------------------------------------
 * 	The listing below presents the different types of MidiShare handled events. 
 * 	This typology contains the whole of the standard Midi messages, plus specific 
 * 	messages such as typeNote corresponding to a note with its duration;  
 * 	or typeStream corresponding to a series of arbitrary bytes, possibly including 
 * 	data and status codes, sent directly without any processing; or typePrivate 
 * 	that are application private messages.
 * 	
 * 	All these codes may be used in the MidiNewEv function to allocate an event
 * 	of the desirable type and are accessible in an event evType field.
 *******************************************************************************/
			
#define typeNote		0 	/* note with pitch, velocity and duration		*/	
		
#define typeKeyOn		1 	/* Note On with pitch, velocity 				*/
#define typeKeyOff		2 	/* Note Off with pitch, velocity 				*/
#define typeKeyPress 	3 	/* Poly Key Pressure with pitch and pressure	*/
#define typeCtrlChange	4 	/* Control Change with controller ID and value	*/
#define typeProgChange	5 	/* Program Change with program ID number		*/
#define typeChanPress	6 	/* Channel Pressure with pressure value			*/
#define typePitchWheel	7 	/* Pitch Bend Change with LSB and MSB values	*/
		
#define typeSongPos		8 	/* Song Position Pointer with LSB and MSB values*/
#define typeSongSel		9 	/* Song Select with song ID number				*/
#define typeClock		10 	/* Timing Clock									*/
#define typeStart		11 	/* Start										*/
#define typeContinue	12 	/* Continue										*/
#define typeStop		13	/* Stop											*/
		
#define typeTune		14 	/* Tune Request									*/
#define typeActiveSens	15 	/* Active Sensing								*/
#define typeReset		16	/* System Reset									*/
	
#define typeSysEx		17 	/* System Exclusive (only data bytes)			*/
#define typeStream		18 	/* arbitrary midi bytes (data and status codes)	*/
		
#define typePrivate		19	/*19..127 Private events for applications internal use*/
#define typeProcess		128	/* used by MidiShare for MidiCall and MidiTask	*/
#define typeDProcess	129	/* used by MidiShare for MidiDTask				*/
#define typeQuarterFrame 130 /* Midi time code quarter frame				*/

#define typeCtrl14b		131	
#define typeNonRegParam	132
#define typeRegParam	133

#define typeSeqNum		134		/* num�ro de s�quence					*/
#define typeText		135		/* �v�nement texte						*/
#define typeCopyright	136		/* message copyright					*/
#define typeSeqName		137		/* nom de s�quence ou de piste			*/
#define typeInstrName	138		/* nom d'instrument						*/
#define typeLyric		139		/* paroles d�stin�es � etre chant�es	*/
#define typeMarker		140		/* marqueur								*/
#define typeCuePoint	141		/* cue point							*/
#define typeChanPrefix	142		/* Midi Channel Prefix					*/
#define typeEndTrack	143		/* fin de piste							*/
#define typeTempo		144		/* changement de tempo					*/
#define typeSMPTEOffset	145		/* offset smpte							*/

#define typeTimeSign	146		/* indication de mesure					*/
#define typeKeySign		147		/* signature tonale						*/
#define typeSpecific	148		/* m�ta evt sp�cifique � un s�quenceur	*/

#define typeReserved	149	/*149..254	reserved for future extensions		*/
		
#define typeDead		255	/* dead Task or DTask							*/
		


/******************************************************************************
* 								 MIDI STATUS CODE								
*******************************************************************************/

#define NoteOff		0x80	
#define NoteOn		0x90
#define PolyTouch	0xa0
#define ControlChg	0xb0
#define ProgramChg	0xc0
#define AfterTouch	0xd0
#define PitchBend	0xe0
#define SysRealTime	0xf0
#define SysEx		0xf0
#define QFrame		0xf1
#define SongPos		0xf2
#define SongSel		0xf3
#define UnDef2		0xf4
#define UnDef3		0xf5
#define Tune		0xf6
#define EndSysX		0xf7
#define MClock		0xf8
#define UnDef4		0xf9
#define MStart		0xfa
#define MCont		0xfb
#define MStop		0xfc
#define UnDef5		0xfd
#define ActSense	0xfe
#define MReset		0xff


/*******************************************************************************
* 									SERIAL PORTS									
*------------------------------------------------------------------------------
* The Modem and printer serial ports ID numbers.							
*******************************************************************************/
			
#define ModemPort	0
#define PrinterPort	1
		

/******************************************************************************
* 									ERROR CODES								
*------------------------------------------------------------------------------
* List of the error codes returned by some MidiShare functions.																	
*******************************************************************************/
		
#define MIDIerrSpace 	-1		/* plus de place dans la freeList */
#define MIDIerrRefNum	-2		/* mauvais numero de reference */
#define MIDIerrBadType	-3		/* mauvais type d'�v�nement */
#define MIDIerrIndex	-4		/* mauvais index d'acces � un �v�nement */
		

/******************************************************************************
* 								SYNCHRONISATION CODES								
*------------------------------------------------------------------------------
* List of the error codes returned by some MidiShare functions.																	
*******************************************************************************/
		
#define MIDISyncExternal 	0x8000		/* bit-15 for external synchronisation */
#define MIDISyncAnyPort		0x4000		/* bit-14 for synchronisation on any port */


/******************************************************************************
* 								  CHANGE CODES							
*------------------------------------------------------------------------------
When an application need to know about context modifications like opening and
closing of applications, opening and closing of midi ports, changes in 
connections between applications, it can install an ApplAlarm (with 
MidiSetApplAlarm). This ApplAlarm is then called by MidiShare every time a 
context modification happens with a 32-bits code describing the modification. 
The hi 16-bits part of this code is the refNum of the application involved in 
the context modification, the low 16-bits part describe the type of change as
listed here.
*******************************************************************************/
	 	
enum{	MIDIOpenAppl=1,
		MIDICloseAppl,
		MIDIChgName,
		MIDIChgConnect,
		MIDIOpenModem,
		MIDICloseModem,
		MIDIOpenPrinter,
		MIDIClosePrinter,
		MIDISyncStart,
		MIDISyncStop,
		MIDIChangeSync
};
	
		
/******************************************************************************
* 							    EVENTS STRUCTURES							
*------------------------------------------------------------------------------
* Tous les �v�nements sont construits � l'aide d'une ou plusieurs cellules de	
* taille fixe (16 octets). La plupart n�cessitent une seule cellule. D'autres	
* comme les System Exclusive n�cessitent plusieurs cellules cha�n�es.			
*******************************************************************************/


/*------------------------ System Exclusive extension cell ----------------------*/

	typedef struct TMidiSEX *MidiSEXPtr;	
	typedef struct TMidiSEX
	{
		MidiSEXPtr link;					/* link to next cell				*/
		Byte data[12];						/* 12 data bytes					*/
	}	TMidiSEX;						
	

/*------------------------------ Private extension cell -------------------------*/

	typedef struct TMidiST *MidiSTPtr;		
	typedef struct TMidiST					
	{
		Ptr ptr1;							/* 4 32-bits fields 				*/
		Ptr ptr2;							
		Ptr ptr3;
		Ptr ptr4;						
	}	TMidiST;						
		

/*------------------------- Common Event Structure ----------------------*/

	typedef struct TMidiEv *MidiEvPtr;		
	typedef struct TMidiEv
	{
		MidiEvPtr link;						/* link to next event				*/
		unsigned long date;					/* event date (in ms)		 		*/
		Byte evType;						/* event type		 				*/
		Byte refNum;						/* sender reference number		 	*/
		Byte port;							/* Midi port 						*/
		Byte chan;							/* Midi channel					 	*/
		union {								/* info depending of event type :	*/
			struct {							/* for notes					*/
				Byte pitch;							/* pitch  					*/
				Byte vel;							/* velocity 				*/
				unsigned short dur;					/* duration 				*/
			} note;

			struct {							/* for MidiFile time signature  */
				Byte numerator;						/* numerator				*/
				Byte denominator;					/* denominator as neg power	*/
													/* of 2. (2= quarter note)	*/
				Byte nClocks;						/* number of Midi clocks in */
													/* a metronome click		*/
				Byte n32nd;							/* number of 32nd notes in	*/
													/* a Midi quarter note		*/
			} timeSign;

			struct {							/* for MidiFile key signature	*/
				char ton;							/* 0: key of C, 1: 1 sharp	*/
													/* -1: 1 flat etc...		*/
				Byte mode;							/* 0: major 1: minor		*/
				Byte unused[2];
			} keySign;

			struct {							/* for MidiFile sequence number */
				unsigned short number;
				short unused;
			} seqNum;
			long tempo;							/* MidiFile tempo in			*/
												/* microsec/Midi quarter note	*/
			Byte data[4];						/* for other small events	 	*/
			MidiSEXPtr linkSE;					/* link to last sysex extension	*/
			MidiSTPtr linkST;					/* link to private extension	*/
		} info;
	} TMidiEv;		

	
/*------------------------------ sequence header ---------------------------*/

	typedef struct TMidiSeq *MidiSeqPtr;	
	typedef struct TMidiSeq
	{
		MidiEvPtr first;					/* first event pointer 				*/
		MidiEvPtr last;						/* last event pointer 				*/
		Ptr undef1;
		Ptr undef2;
	}	TMidiSeq;
	

/*-------------------------------- input Filter -------------------------------*/

	typedef struct TFilter *FilterPtr;
	typedef struct TFilter
	{
		char port[32];						/* 256 bits	*/
		char evType[32];					/* 256 bits */
		char channel[2];					/*  16 bits	*/
		char unused[2];						/*  16 bits */
	} TFilter; 
	

/*------------------------ MidiShare application name ------------------------*/

#ifdef THINK_C
	typedef char* MidiName;
#else
	typedef unsigned char* MidiName;
#endif
	

/*------------------------ Synchronisation informations -----------------------*/

	typedef struct TSyncInfo *SyncInfoPtr;
	typedef struct TSyncInfo
	{
 		long		time;
 		long		reenter;
 		unsigned short	syncMode;
 		Byte		syncLocked; 
 		Byte		syncPort;
		long		syncStart;
		long		syncStop;
		long		syncOffset;
		long		syncSpeed;
		long		syncBreaks;
		short		syncFormat;
	} TSyncInfo; 

	typedef struct TSmpteLocation *SmpteLocPtr;
	typedef struct TSmpteLocation
	{
 		short		format;			// (0:24f/s, 1:25f/s, 2:30DFf/s, 3:30f/s)
 		short		hours;			// 0..23
 		short		minutes;		// 0..59
 		short		seconds;		// 0..59
 		short		frames;			// 0..30 (according to format)
 		short		fracs;			// 0..99 (1/100 of frames)
	} TSmpteLocation; 
	
	
/*----------------------------- Alarms prototypes ----------------------------*/

#ifdef THINK_C
	typedef  void (* TaskPtr)( long date, short refNum, long a1,long a2,long a3 );
	typedef  void (* RcvAlarmPtr)( short refNum);
	typedef  void (* ApplAlarmPtr)( short refNum, long code);
	typedef  void (* ApplyProcPtr)( MidiEvPtr e);
#else
	typedef pascal void (* TaskPtr)( long date, short refNum, long a1,long a2,long a3 );
	typedef pascal void (* RcvAlarmPtr)( short refNum);
	typedef pascal void (* ApplAlarmPtr)( short refNum, long code);
	typedef pascal void (* ApplyProcPtr)( MidiEvPtr e);

typedef UniversalProcPtr UPPTaskPtr;
typedef UniversalProcPtr UPPRcvAlarmPtr;
typedef UniversalProcPtr UPPApplAlarmPtr;
typedef UniversalProcPtr UPPApplyProcPtr;

	
enum {
	
	uppTaskPtrProcInfo = kPascalStackBased
		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(long)))
		 | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(short)))
		 | STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(long)))
		 | STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(long)))
		 | STACK_ROUTINE_PARAMETER(5, SIZE_CODE(sizeof(long)))
,
		 
	uppRcvAlarmPtrProcInfo = kPascalStackBased
		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,		 
	
	uppApplAlarmPtrProcInfo = kPascalStackBased
		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
		 | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(long)))
		 
,	 

		 
	uppApplyProcPtrProcInfo = kPascalStackBased
		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr)))
};

#define NewTaskPtr(userRoutine)		\
		(UPPTaskPtr) NewRoutineDescriptor((ProcPtr)(userRoutine), uppTaskPtrProcInfo, GetCurrentISA())


#define NewRcvAlarmPtr(userRoutine)		\
		(UPPRcvAlarmPtr) NewRoutineDescriptor((ProcPtr)(userRoutine), uppRcvAlarmPtrProcInfo, GetCurrentISA())

#define NewApplAlarmPtr(userRoutine)		\
		(UPPApplAlarmPtr) NewRoutineDescriptor((ProcPtr)(userRoutine), uppApplAlarmPtrProcInfo, GetCurrentISA())

#define NewApplyProcPtr(userRoutine)		\
		(UPPApplyProcPtr) NewRoutineDescriptor((ProcPtr)(userRoutine), uppApplyProcPtrProcInfo, GetCurrentISA())

/* use:

definition
----------

pascal void MyTask ( long date, short refNum, long a1,long a2,long a3 );
UPPTaskPtr UPPMyTask = NewTaskPtr(MyTask);


call
-----
MidiTask(UPPMyTask , .....)

*/

#endif


/******************************************************************************
* 							   FIELD MACROS							
*------------------------------------------------------------------------------
* Somes macros to read and write event's fields					 
*******************************************************************************/

	#define Link(e) 	( (e)->link )
	#define Date(e) 	( (e)->date )
	#define EvType(e) 	( (e)->evType )
	#define RefNum(e) 	( (e)->refNum )	
	#define Port(e) 	( (e)->port )
	#define Canal(e)	( (e)->chan )
	#define Chan(e)		( (e)->chan )
	#define Pitch(e) 	( (e)->info.note.pitch ) 
	#define Vel(e) 		( (e)->info.note.vel ) 
	#define Dur(e) 		( (e)->info.note.dur )
	#define Data(e) 	( (e)->info.data )
	#define LinkSE(e) 	( (e)->info.linkSE )
	#define LinkST(e) 	( (e)->info.linkST )

	#define TSNum(e)	( (e)->info.timeSign.numerator )
	#define TSDenom(e)	( (e)->info.timeSign.denominator )
	#define TSClocks(e)	( (e)->info.timeSign.nClocks )
	#define TS32nd(e)	( (e)->info.timeSign.n32nd )

	#define KSTon(e)	( (e)->info.keySign.ton )
	#define KSMode(e)	( (e)->info.keySign.mode )

	#define Tempo(e)	( (e)->info.tempo )
	#define SeqNum(e)	( (e)->info.seqNum.number )
	#define ChanPrefix(e) ((e)->info.data[0] )

	#define First(e)	( (e)->first )
	#define Last(e)		( (e)->last )
	#define FirstEv(e)	( (e)->first )
	#define LastEv(e)	( (e)->last )


/******************************************************************************
* 							  FILTER MACROS							
*------------------------------------------------------------------------------
* somes macros to set and reset filter's bits. 
*******************************************************************************/

#ifdef __cplusplus
inline void 	AcceptBit( char* a, Byte n) 		{ (a)[(n)>>3] |=  (1<<((n)&7)); }
inline void 	RejectBit( char* a, Byte n) 		{ (a)[(n)>>3] &= ~(1<<((n)&7)); }
inline void 	InvertBit( char* a, Byte n) 		{ (a)[(n)>>3] ^=  (1<<((n)&7)); }

inline Boolean 	IsAcceptedBit( char* a, Byte n) 	{ return (a)[(n)>>3] & (1<<((n)&7)); }

#else

	#define AcceptBit(a,n) 			( ((char*) (a))[(n)>>3] |=   (1<<((n)&7)) )
	#define RejectBit(a,n) 			( ((char*) (a))[(n)>>3] &=  ~(1<<((n)&7)) )
	#define InvertBit(a,n) 			( ((char*) (a))[(n)>>3] ^=   (1<<((n)&7)) )

	#define IsAcceptedBit(a,n) 		( ((char*) (a))[(n)>>3]  &   (1<<((n)&7)) )
#endif


/*******************************************************************************
* 								ENTRY POINTS									
*------------------------------------------------------------------------------
* All the MidiShare entry point are implemented as below :
*			moveq	#nn, d0	;move entry point ID number into reg d0													
*			move.l	$B8, a0	;read address of MS dispatch routine from vector $B8													
*			jmp		(a0)	;jump to dispatch,													
*																				
* Vector $B8 is initialy set by MidiShare Init at boot time.		
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define RESULT_SIZE_MSH(sizeCode) 	\
	((long)(sizeCode) << kResultSizePhase)


enum {
	uppProcInfoMidiShareSpecialInit = kPascalStackBased
	
,

	uppProcInfoMidiGetSyncInfo = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(SyncInfoPtr)))
,
	
	uppProcInfoMidiGetIndAppl = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,
	uppProcInfoMidiTime2Smpte = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(SmpteLocPtr)))
,
	uppProcInfoMidiSmpte2Time = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(SmpteLocPtr)))
,						
	uppProcInfoMidiGetTimeAddr = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(long*)))
,						
	uppProcInfoMidiGetName = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(MidiName)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,						
	uppProcInfoMidiSetName = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(MidiName)))
,						
	uppProcInfoMidiGetInfo = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(void*)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,						
	uppProcInfoMidiSetInfo = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(void*)))
,						
	uppProcInfoMidiGetFilter = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(FilterPtr)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,
	uppProcInfoMidiSetFilter = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(FilterPtr)))
,						
	uppProcInfoMidiGetRcvAlarm = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(UPPRcvAlarmPtr)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,
	uppProcInfoMidiSetRcvAlarm = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(UPPRcvAlarmPtr)))
,
	uppProcInfoMidiGetApplAlarm = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(UPPApplAlarmPtr)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,
	uppProcInfoMidiSetApplAlarm = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(UPPApplAlarmPtr)))
,	
	uppProcInfoMidiConnect = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(Boolean)))
,						
	uppProcInfoMidiIsConnected = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(Boolean)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(short)))
,	
	uppProcInfoMidiGetPortState = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(Boolean)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						
,	
	uppProcInfoMidiSetPortState = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(Boolean)))
,						
	uppProcInfoMidiNewCell = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(MidiEvPtr)))
,
	uppProcInfoMidiNewEv = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
,
	uppProcInfoMidiCopyEv = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr)))
,
	uppProcInfoMidiSetField = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(long)))
,
	uppProcInfoMidiGetField = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(long)))
,	
	uppProcInfoMidiAddField = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(long)))
,				
	uppProcInfoMidiCountFields = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr)))
,
	uppProcInfoMidiNewSeq = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(MidiSeqPtr)))
,						
	uppProcInfoMidiAddSeq = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiSeqPtr)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(MidiEvPtr)))
,
	uppProcInfoMidiApplySeq = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiSeqPtr)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(UPPApplyProcPtr)))
,
	uppProcInfoMidiSendAt = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(long)))						
,
	uppProcInfoMidiReadSync = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(void*)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(void*)))
,						
	uppProcInfoMidiWriteSync = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(void*)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(void*)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(void*)))
,						
	uppProcInfoMidiCall = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(UPPTaskPtr)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(5, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(6, SIZE_CODE(sizeof(long)))
,						
	uppProcInfoMidiForgetTask = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr*)))
						
	
				
};

/* descripteurs utilis�s par plusieurs fonctions */

enum {

	/* MidiGetVersion , MidiCountAppls */
	
	uppProcInfoType1 = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(short)))
	,					
	/* MidiSetSyncMode , MidiFlushEvs,MidiClose,MidiFlushDTasks,MidiExec1DTask */
	
	uppProcInfoType2 = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
	,					
	/* MidiGetExtTime, MidiFreeSpace,MidiTotalSpace ,MidiGetTime */
	
	uppProcInfoType3 = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(long)))
	,					
	/* MidiInt2ExtTime, MidiExtInt2Time,MidiGrowSpace  */
	
	uppProcInfoType4 = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(long)))
	,
	/* MidiGetNamedAppl, MidiOpen  */	
				
	uppProcInfoType5 = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiName)))
						
	,
	/* MidiFreeCell, MidiFreeEv  */					
	uppProcInfoType6 = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiEvPtr)))

	,
	/* MidiFreeSeq, MidiClearSeq  */					
	uppProcInfoType7 = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(MidiSeqPtr)))

	,
	/* MidiSendIm, MidiSend  */					
	uppProcInfoType8 = kPascalStackBased
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(MidiEvPtr)))

	,
	/* MidiGetEv, MidiAvailEv  */					
	uppProcInfoType9 = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
					
	,				
	/* MidiTask, MidiDTask */	
	uppProcInfoType10 = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(MidiEvPtr)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(UPPTaskPtr)))
						| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(short)))
						| STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(5, SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(6, SIZE_CODE(sizeof(long)))
	,					
	/* MidiCountEvs, MidiCountDTasks  */					
	uppProcInfoType11 = kPascalStackBased
						| RESULT_SIZE (SIZE_CODE(sizeof(long)))
						| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short)))
	

};


/*--------------------------- Global MidiShare environment --------------------*/

static short CodeMidiShareSpecialInit[]	={0x7037, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetVersion[]			={0x7000, 0x2078, 0x00B8, 0x4ED0};

static short CodeMidiCountAppls[]			={0x7001, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetIndAppl[] 			={0x7002, 0x2078, 0x00B8, 0x4ED0};		
static short CodeMidiGetNamedAppl[]		={0x7003, 0x2078, 0x00B8, 0x4ED0};
 
/*----------------------------- SMPTE synchronization -------------------------*/

static short CodeMidiGetSyncInfo[]			={0x7038, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiSetSyncMode[]			={0x7039, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetExtTime[]			={0x703D, 0x2078, 0x00B8, 0x4ED0};						
static short CodeMidiInt2ExtTime[]			={0x703E, 0x2078, 0x00B8, 0x4ED0};						
static short CodeMidiExt2IntTime[]			={0x703F, 0x2078, 0x00B8, 0x4ED0};						
static short CodeMidiTime2Smpte[] 			={0x7040, 0x2078, 0x00B8, 0x4ED0};						
static short CodeMidiSmpte2Time[]			={0x7041, 0x2078, 0x00B8, 0x4ED0};						
static short CodeMidiGetTimeAddr[]			={0x7042, 0x2078, 0x00B8, 0x4ED0};						


/*----------------------------- Open / close application ----------------------*/

static short CodeMidiOpen[] 				={0x7004, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiClose[] 				={0x7005, 0x2078, 0x00B8, 0x4ED0};	


/*--------------------------- Application configuration -----------------------*/

static short CodeMidiGetName[]				={0x7006, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiSetName[] 			={0x7007, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetInfo[] 			={0x7008, 0x2078, 0x00B8, 0x4ED0};	
static short CodeMidiSetInfo[]				={0x7009, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetFilter[] 			={0x700A, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiSetFilter[]			={0x700B, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetRcvAlarm[]			={0x700C, 0x2078, 0x00B8, 0x4ED0};		
static short CodeMidiSetRcvAlarm[] 		={0x700D, 0x2078, 0x00B8, 0x4ED0};	
static short CodeMidiGetApplAlarm[]		={0x700E, 0x2078, 0x00B8, 0x4ED0};		
static short CodeMidiSetApplAlarm[]		={0x700F, 0x2078, 0x00B8, 0x4ED0};


/*------------------------- Inter-Application Connections ---------------------*/

static short CodeMidiConnect[] 			={0x7010, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiIsConnected[]			={0x7011, 0x2078, 0x00B8, 0x4ED0};


/*-------------------------------- Serial ports -------------------------------*/

static short CodeMidiGetPortState[]		={0x7012, 0x2078, 0x00B8, 0x4ED0};	
static short CodeMidiSetPortState[]		={0x7013, 0x2078, 0x00B8, 0x4ED0};


/*-------------------------- Events and memory managing -----------------------*/

static short CodeMidiFreeSpace[]			={0x7014, 0x2078, 0x00B8, 0x4ED0};						

static short CodeMidiNewCell[]				={0x7033, 0x2078, 0x00B8, 0x4ED0};			
static short CodeMidiFreeCell[] 			={0x7034, 0x2078, 0x00B8, 0x4ED0};					
static short CodeMidiTotalSpace[]			={0x7035, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGrowSpace[]			={0x7036, 0x2078, 0x00B8, 0x4ED0};

static short CodeMidiNewEv[]				={0x7015, 0x2078, 0x00B8, 0x4ED0};			
static short CodeMidiCopyEv[]				={0x7016, 0x2078, 0x00B8, 0x4ED0};			
static short CodeMidiFreeEv[]				={0x7017, 0x2078, 0x00B8, 0x4ED0};					


static short CodeMidiSetField[] 			={0x703A, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetField[]			={0x703B, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiAddField[] 			={0x701A, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiCountFields[]			={0x703C, 0x2078, 0x00B8, 0x4ED0};


/*------------------------------- Sequence managing ---------------------------*/

static short CodeMidiNewSeq[]				={0x701D, 0x2078, 0x00B8, 0x4ED0};				 			
static short CodeMidiAddSeq[] 				={0x701E, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiFreeSeq[] 			={0x701F, 0x2078, 0x00B8, 0x4ED0};		
static short CodeMidiClearSeq[]			={0x7020, 0x2078, 0x00B8, 0x4ED0};			
static short CodeMidiApplySeq[]			={0x7021, 0x2078, 0x00B8, 0x4ED0}; 


/*------------------------------------- Time ----------------------------------*/

static short CodeMidiGetTime[]				={0x7022, 0x2078, 0x00B8, 0x4ED0};		


/*------------------------------------ Sending --------------------------------*/

static short CodeMidiSendIm[]				={0x7023, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiSend[] 				={0x7024, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiSendAt[]				={0x7025, 0x2078, 0x00B8, 0x4ED0};	


/*------------------------------------ Receving -------------------------------*/

static short CodeMidiCountEvs[]			={0x7026, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiGetEv[]				={0x7027, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiAvailEv[]				={0x7028, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiFlushEvs[]			={0x7029, 0x2078, 0x00B8, 0x4ED0};	


/*----------------------------------- Mail boxes ------------------------------*/

static short CodeMidiReadSync[]			={0x702A, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiWriteSync[]		 	={0x702B, 0x2078, 0x00B8, 0x4ED0};


/*---------------------------------- Task Managing ----------------------------*/

static short CodeMidiCall[]				={0x702C, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiTask[]				={0x702D, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiDTask[] 				={0x702E, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiForgetTask[]			={0x702F, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiCountDTasks[]			={0x7030, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiFlushDTasks[]			={0x7031, 0x2078, 0x00B8, 0x4ED0};
static short CodeMidiExec1DTask[]			={0x7032, 0x2078, 0x00B8, 0x4ED0};


/*-----------------MidiShare -------------------------------*/

#define MidiShare() 	( **((long**)0xB8) == 0xD080D080 )


/*--------------------------- Global MidiShare environment --------------------*/

#define MidiShareSpecialInit()		\
	CallUniversalProc((UniversalProcPtr)CodeMidiShareSpecialInit, uppProcInfoMidiShareSpecialInit)

#define MidiGetVersion()		\
	(short)CallUniversalProc((UniversalProcPtr)CodeMidiGetVersion, uppProcInfoType1)

#define MidiCountAppls()		\
	(short)CallUniversalProc((UniversalProcPtr)CodeMidiCountAppls, uppProcInfoType1)

#define MidiGetIndAppl(ind)		\
	(short)CallUniversalProc((UniversalProcPtr)CodeMidiGetIndAppl, uppProcInfoMidiGetIndAppl,(ind))

#define MidiGetNamedAppl(na)		\
	(short)CallUniversalProc((UniversalProcPtr)CodeMidiGetNamedAppl, uppProcInfoType5,(na))

/*----------------------------- SMPTE synchronization -------------------------*/

#define MidiGetSyncInfo(p)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiGetSyncInfo, uppProcInfoMidiGetSyncInfo,(p))

#define MidiSetSyncMode(mode)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetSyncMode, uppProcInfoType2,(mode))

#define MidiGetExtTime()		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiGetExtTime, uppProcInfoType3)

#define MidiInt2ExtTime(v)		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiInt2ExtTime, uppProcInfoType4,(v))

#define MidiExt2IntTime(v)		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiExt2IntTime, uppProcInfoType4,(v))
		
#define MidiTime2Smpte(time,format,loc)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiTime2Smpte, uppProcInfoMidiTime2Smpte,(time),(format),(loc))

	
#define MidiSmpte2Time(loc)		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiSmpte2Time, uppProcInfoMidiSmpte2Time,(loc))

/*----------------------------- Open / close application ----------------------*/


#define MidiOpen(na)		\
	(short)CallUniversalProc((UniversalProcPtr)CodeMidiOpen, uppProcInfoType5,(na))


#define MidiClose(r)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiClose, uppProcInfoType2,(r))

	

/*--------------------------- Application configuration -----------------------*/

#define MidiGetName(r)		\
	(MidiName)CallUniversalProc((UniversalProcPtr)CodeMidiGetName, uppProcInfoMidiGetName,(r))

#define MidiSetName(r,na)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetName, uppProcInfoMidiSetName,(r),(na))


#define MidiGetInfo(r)		\
	(void*)CallUniversalProc((UniversalProcPtr)CodeMidiGetInfo, uppProcInfoMidiGetInfo,(r))


#define MidiSetInfo(r,in)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetInfo, uppProcInfoMidiSetInfo,(r),(in))

		
#define MidiGetFilter(r)		\
	(FilterPtr)CallUniversalProc((UniversalProcPtr)CodeMidiGetFilter, uppProcInfoMidiGetFilter,(r))
	
	
#define MidiSetFilter(r,f)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetFilter, uppProcInfoMidiSetFilter,(r),(f))

#define MidiGetRcvAlarm(r)		\
	(UPPRcvAlarmPtr)CallUniversalProc((UniversalProcPtr)CodeMidiGetRcvAlarm, uppProcInfoMidiGetRcvAlarm,(r))
	
		
#define MidiSetRcvAlarm(r,al)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetRcvAlarm, uppProcInfoMidiSetRcvAlarm,(r),(al))

	
#define MidiGetApplAlarm(r)		\
	(UPPApplAlarmPtr)CallUniversalProc((UniversalProcPtr)CodeMidiGetApplAlarm, uppProcInfoMidiGetApplAlarm,(r))
	

#define MidiSetApplAlarm(r,al)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetApplAlarm, uppProcInfoMidiSetApplAlarm,(r),(al))

	


/*------------------------- Inter-Application Connections ---------------------*/

#define MidiConnect(s,d,st)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiConnect, uppProcInfoMidiConnect,(s),(d),(st))

	
#define MidiIsConnected(s,d)		\
	(Boolean)CallUniversalProc((UniversalProcPtr)CodeMidiIsConnected, uppProcInfoMidiIsConnected,(s),(d))
	
 
/*-------------------------------- Serial ports -------------------------------*/


#define MidiGetPortState(p)		\
	(Boolean)CallUniversalProc((UniversalProcPtr)CodeMidiGetPortState, uppProcInfoMidiGetPortState,(p))


#define MidiSetPortState(p,s)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetPortState, uppProcInfoMidiSetPortState,(p),(s))
	


/*-------------------------- Events and memory managing -----------------------*/

#define MidiFreeSpace()		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiFreeSpace, uppProcInfoType3)


#define MidiNewCell()		\
	(MidiEvPtr)CallUniversalProc((UniversalProcPtr)CodeMidiNewCell, uppProcInfoMidiNewCell)

#define  MidiFreeCell(e)	\
	CallUniversalProc((UniversalProcPtr)CodeMidiFreeCell,uppProcInfoType6,(e))
	
#define  MidiTotalSpace()	\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiTotalSpace,uppProcInfoType3)
	
	
#define  MidiGrowSpace(n)	\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiGrowSpace,uppProcInfoType4,(n))
	
	
#define MidiNewEv(ty)		\
	(MidiEvPtr)CallUniversalProc((UniversalProcPtr)CodeMidiNewEv, uppProcInfoMidiNewEv,(ty))

#define MidiCopyEv(e)		\
	(MidiEvPtr)CallUniversalProc((UniversalProcPtr)CodeMidiCopyEv, uppProcInfoMidiCopyEv,(e))

#define MidiFreeEv(e)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiFreeEv, uppProcInfoType6,(e))


#define MidiSetField(e,f,v)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSetField, uppProcInfoMidiSetField,(e),(f),(v))


#define MidiGetField(e,f)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiGetField, uppProcInfoMidiGetField,(e),(f))


#define MidiAddField(e,v)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiAddField, uppProcInfoMidiAddField,(e),(v))


#define MidiCountFields(e)		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiCountFields, uppProcInfoMidiCountFields,(e))

	

/*------------------------------- Sequence managing ---------------------------*/

#define MidiNewSeq()		\
	(MidiSeqPtr)CallUniversalProc((UniversalProcPtr)CodeMidiNewSeq, uppProcInfoMidiNewSeq)

#define MidiAddSeq(s,e)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiAddSeq, uppProcInfoMidiAddSeq,(s),(e))


#define MidiFreeSeq(s)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiFreeSeq, uppProcInfoType7,(s))


#define MidiClearSeq(s)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiClearSeq, uppProcInfoType7,(s))


#define MidiApplySeq(s,p)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiApplySeq, uppProcInfoMidiApplySeq,(s),(p))


/*------------------------------------- Time ----------------------------------*/

#define MidiGetTime()		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiGetTime, uppProcInfoType3)



/*------------------------------------ Sending --------------------------------*/

#define MidiSendIm(r,e)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSendIm, uppProcInfoType8,(r),(e))

#define MidiSend(r,e)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSend, uppProcInfoType8,(r),(e))

#define MidiSendAt(r,e,d)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiSendAt, uppProcInfoMidiSendAt,(r),(e),(d))

/*------------------------------------ Receving -------------------------------*/

#define MidiCountEvs(r)		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiCountEvs, uppProcInfoType11,(r))


#define MidiGetEv(r)		\
	(MidiEvPtr)CallUniversalProc((UniversalProcPtr)CodeMidiGetEv, uppProcInfoType9,(r))


#define MidiAvailEv(r)		\
	(MidiEvPtr)CallUniversalProc((UniversalProcPtr)CodeMidiAvailEv, uppProcInfoType9,(r))


#define MidiFlushEvs(r)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiFlushEvs, uppProcInfoType2,(r))


/*----------------------------------- Mail boxes ------------------------------*/


#define MidiReadSync(adrMem)		\
	(void*)CallUniversalProc((UniversalProcPtr)CodeMidiReadSync, uppProcInfoMidiReadSync,(adrMem))


#define MidiWriteSync(adrMem,val)		\
	(void*)CallUniversalProc((UniversalProcPtr)CodeMidiWriteSync, uppProcInfoMidiWriteSync,(adrMem),(val))


/*---------------------------------- Task Managing ----------------------------*/


#define MidiCall(ro,d,re,a1,a2,a3)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiCall, uppProcInfoMidiCall,(ro),(d),(re),(a1),(a2),(a3))


#define MidiTask(ro,d,re,a1,a2,a3)		\
	(MidiEvPtr)CallUniversalProc((UniversalProcPtr)CodeMidiTask, uppProcInfoType10,(ro),(d),(re),(a1),(a2),(a3))


#define MidiDTask(ro,d,re,a1,a2,a3)		\
	(MidiEvPtr)CallUniversalProc((UniversalProcPtr)CodeMidiDTask, uppProcInfoType10,(ro),(d),(re),(a1),(a2),(a3))


#define MidiForgetTask(e)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiForgetTask, uppProcInfoMidiForgetTask,(e))


#define MidiCountDTasks(r)		\
	(long)CallUniversalProc((UniversalProcPtr)CodeMidiCountDTasks, uppProcInfoType11,(r))


#define MidiFlushDTasks(r)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiFlushDTasks, uppProcInfoType2,(r))


#define MidiExec1DTask(r)		\
	CallUniversalProc((UniversalProcPtr)CodeMidiExec1DTask, uppProcInfoType2,(r))





#ifdef __cplusplus
}
#endif

#endif

#endif