// ===========================================================================
// The Player Library is Copyright (c) Grame, Computer Music Research Laboratory 
// 1996-2003, and is distributed as Open Source software under the Artistic License;
// see the file "Artistic" that is included in the distribution for details.
//
// Grame : Computer Music Research Laboratory
// Web : http://www.grame.fr/Research
// E-mail : MidiShare@rd.grame.fr
// ===========================================================================


// ===========================================================================
//	TScoreState.h			    
// ===========================================================================


#ifndef __TScoreState__
#define __TScoreState__

#include "TScoreFollower.h"
#include "CStruct.h"

//-------------------
// Class TScoreState 
//-------------------
/*!
	\brief For displaying purpose : get the current state.
*/ 


class TScoreState : public TScoreObjFollower {
	
	public:
 
 		TScoreState(TScorePtr score, ULONG tpq):TScoreObjFollower(score,tpq){}
 		virtual ~TScoreState (){}
 	
		void FillState(PlayerStatePtr state, ULONG date_ticks) 
		{
			SetPosTicks(date_ticks);
	
			TPos pos = GetVisitor().CurDateBBU();
			state->date = GetVisitor().CurDateMicro() / 100;
                        state->ticks = date_ticks;
			
			state->bar = (short)pos.GetBar() + 1; 
			state->beat = (short)pos.GetBeat() + 1;
			state->unit = (short)pos.GetUnit() + 1;
			
			state->tsnum = GetVisitor().GetNum ();
			state->tsdenom = GetVisitor().GetDenom ();
			state->tsclick= GetVisitor().GetNClocks();
			state->tsquarter = GetVisitor().GetN32nd();
		} 
};


typedef TScoreState FAR * TScoreStatePtr;

#endif
