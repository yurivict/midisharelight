/*
	*** THIS FILE GENERATED AUTOMATICALLY -- DO NOT MODIFY ***
	Copyright (c) 1994-98 Opcode Systems, Inc.
*/

#if OMS_MAC_CFM
enum {
	uppOMSWakeUpTaskInfo = kPascalStackBased
					| RESULT_SIZE(kFourByteCode)				/* pascal OMSTimerTask * */
					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSTimerTask *task   */
};
typedef UniversalProcPtr OMSWakeUpTaskUPP;
#define NewOMSWakeUpTask(userRoutine)	\
		(OMSWakeUpTaskUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSWakeUpTaskInfo, GetCurrentArchitecture())
#define CallOMSWakeUpTask(userRoutine, task)	\
		(OMSTimerTask *)CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSWakeUpTaskInfo, (task))
#else
typedef OMSWakeUpTask OMSWakeUpTaskUPP;
#define NewOMSWakeUpTask(userRoutine)	\
		(OMSWakeUpTaskUPP)(userRoutine)
#define CallOMSWakeUpTask(userRoutine, task)	\
		(*(userRoutine))((task))
#endif

#if OMS_MAC_CFM
enum {
	uppOMSTimerMessageProcInfo = kPascalStackBased
					| RESULT_SIZE(0)							/* pascal void          */
					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSTimerStruct *params */
};
typedef UniversalProcPtr OMSTimerMessageProcUPP;
#define NewOMSTimerMessageProc(userRoutine)	\
		(OMSTimerMessageProcUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSTimerMessageProcInfo, GetCurrentArchitecture())
#define CallOMSTimerMessageProc(userRoutine, params)	\
		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSTimerMessageProcInfo, (params))
#else
typedef OMSTimerMessageProc OMSTimerMessageProcUPP;
#define NewOMSTimerMessageProc(userRoutine)	\
		(OMSTimerMessageProcUPP)(userRoutine)
#define CallOMSTimerMessageProc(userRoutine, params)	\
		(*(userRoutine))((params))
#endif

