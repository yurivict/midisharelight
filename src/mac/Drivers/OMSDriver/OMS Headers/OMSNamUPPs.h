/*
	*** THIS FILE GENERATED AUTOMATICALLY -- DO NOT MODIFY ***
	Copyright (c) 1994-98 Opcode Systems, Inc.
*/

#if OMS_MAC_CFM
enum {
	uppOMSNModalProcInfo = kPascalStackBased
					| RESULT_SIZE(0)							/* pascal void          */
					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* EventRecord *evt     */
};
typedef UniversalProcPtr OMSNModalProcUPP;
#define NewOMSNModalProc(userRoutine)	\
		(OMSNModalProcUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSNModalProcInfo, GetCurrentArchitecture())
#define CallOMSNModalProc(userRoutine, evt)	\
		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSNModalProcInfo, (evt))
#else
typedef OMSNModalProc OMSNModalProcUPP;
#define NewOMSNModalProc(userRoutine)	\
		(OMSNModalProcUPP)(userRoutine)
#define CallOMSNModalProc(userRoutine, evt)	\
		(*(userRoutine))((evt))
#endif

#if OMS_MAC_CFM
enum {
	uppOMSNameMenuChangeProcInfo = kPascalStackBased
					| RESULT_SIZE(0)							/* pascal void          */
					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSNameMenu menu     */
					| STACK_ROUTINE_PARAMETER(2, kFourByteCode)	/* long refCon          */
					| STACK_ROUTINE_PARAMETER(3, kTwoByteCode)	/* short newChoice      */
};
typedef UniversalProcPtr OMSNameMenuChangeProcUPP;
#define NewOMSNameMenuChangeProc(userRoutine)	\
		(OMSNameMenuChangeProcUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSNameMenuChangeProcInfo, GetCurrentArchitecture())
#define CallOMSNameMenuChangeProc(userRoutine, menu, refCon, newChoice)	\
		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSNameMenuChangeProcInfo, (menu), (refCon), (newChoice))
#else
typedef OMSNameMenuChangeProc OMSNameMenuChangeProcUPP;
#define NewOMSNameMenuChangeProc(userRoutine)	\
		(OMSNameMenuChangeProcUPP)(userRoutine)
#define CallOMSNameMenuChangeProc(userRoutine, menu, refCon, newChoice)	\
		(*(userRoutine))((menu), (refCon), (newChoice))
#endif

