#ifndef __OMSNProvider__
#define __OMSNProvider__
#pragma once


#include "OMSNameMgr.h"


/* messages to provider modules */
enum {
	omsnProviderInit = 0,			/* no params, return provider ID */
	omsnProviderGetAttrs = 1,		/* par1 = provider name,
										return attributes */
	omsnProviderFileTypes = 2,		/* par1 = short *nTypes, return OSType *filetypes */
	omsnProviderSetUpPatchFile = 3,	/* par1 = FSSpec *, par2 = OMSNProviderCallbacks * */
	omsnProviderMatchDevice = 4,		/* par1 = OMSDeviceH, par2 = OMSNProvLoadDeviceRec *,
										return boolean match */
	omsnProviderLoadDevice = 5,		/* par1 = OMSNProvLoadDeviceRec *, 
										par2 = OMSNProviderCallbacks * */
	omsnProviderGetFileIcon = 6,
	omsnProviderDispose = 7,		/* no params */
	omsnProviderDOSFileExtensions = 8	/* par1 = short *nTypes, return OSType *filetypes */
};

/* provider attributes */
enum {
	kOMSNProvActive = 1,
	kOMSNProvHasSendConcept = 2,
	kOMSNProvCanSend = 4,
	kOMSNProvCanFind = 8,
	kOMSNProvCanOpenAndEdit = 0x10
};


#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=mac68k
#endif


typedef struct OMSNProvLoadDeviceRec {
	OMSFile				loadFile;
	OMSUniqueID			devUniqueID;
	long				provDevRefCon;
} OMSNProvLoadDeviceRec;

TYPEDEF_OMSPROC(long,	OMSNProviderDefProc)(short msg, long param1, long param2);
TYPEDEF_OMSPROC(OMSErr,	OMSNDefineDeviceProc)(short devIndex0, OMSUniqueID devUniqueID, 
											long provDevRefCon, OMSStringPtr deviceName);
TYPEDEF_OMSPROC(OMSErr,	OMSNDefineModeProc)(short devIndex0, short modeIndex0, 
											long provModeRefCon, OMSStringPtr modeName);
TYPEDEF_OMSPROC(short,	OMSNGetNumModesProc)(void);
TYPEDEF_OMSPROC(long,	OMSNGetModeRefConProc)(short modeIndex0);
TYPEDEF_OMSPROC(OMSErr,	OMSNSetModePatchNameListProc)(short modeIndex0, OMSNNameListH nlh);
TYPEDEF_OMSPROC(OMSErr,	OMSNSetNoteNameListProc)(short modeIndex0, short patchNum, OMSNNameListH nlh);
TYPEDEF_OMSPROC(OMSErr,	OMSNSetCtlNameListProc)(short modeIndex0, short patchNum, OMSNNameListH nlh);
TYPEDEF_OMSPROC(OMSErr,	OMSNAddModeClassificationProc)(short modeIndex0, 
						OMSStringPtr className, OMSNNameListH nlh, char *patchGroupBits,
						Boolean isGlobal);

#include "OMSNPrUPPs.h"

/* devIndex0 and modeIndex0 are 0-based */
typedef struct OMSNProviderCallbacks {
	/* for SetUpPatchFile */
	OMSNDefineDeviceProcUPP			DefineDevice;
	OMSNDefineModeProcUPP			DefineMode;
	
	/* for LoadDevice */
	OMSNGetNumModesProcUPP			GetNumModes;
	OMSNGetModeRefConProcUPP		GetModeRefCon;
	OMSNSetModePatchNameListProcUPP	SetModePatchNameList;
	OMSNSetNoteNameListProcUPP		SetNoteNameList;
	OMSNSetCtlNameListProcUPP		SetCtlNameList;
	OMSNAddModeClassificationProcUPP AddModeClassification;
} OMSNProviderCallbacks;

#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=reset
#endif

#endif // __OMSNProvider__
