/*******************************************************************************
 * C H A M E L E O N    S. D. K.                                               *
 *******************************************************************************
 *  $Archive:: /Chameleon.sdk/SYSTEM/midishare/common/Clients/msAlarms.c       $
 *     $Date: 2005/12/08 13:38:28 $
 * $Revision: 1.1.1.1.6.1 $
 *-----------------------------------------------------------------------------*
 * This file is part of the Chameleon Software Development Kit                 *
 *                                                                             *
 * Copyright (C) 2001 soundart                                                 *
 * www.soundart-hot.com                                                        *
 * codemaster@soundart-hot.com                                                 *
 ******************************************************************************/

/*

  Copyright � Grame 1999

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
  research@grame.fr

*/

#include "msAlarms.h"
#include "msExtern.h"


/*_____________________________________________________________________________________*/
void CallAlarm (short ref, int alarmCode, TClientsPtr g)
{
	TApplPtr *applPtr, appl;
	long code; short i;

	code   = ref;
	code <<= 16;
	code  |= alarmCode & 0xffff;                      /* alarm arguments                 */
	applPtr = g->appls;                               /* points the applications table   */
	for( i=0; i<MaxAppls; i++) {                      /* for each application            */
		appl = *applPtr++;
		if( appl && appl->applAlarm) {                /* if the alarm exists             */
			CallApplAlarm (appl->context, appl->applAlarm, appl->refNum, code);
		}
	}
}
