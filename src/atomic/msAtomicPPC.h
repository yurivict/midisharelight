/*

  Copyright � Grame 1999-2002

  This library is free software; you can redistribute it and modify it under 
  the terms of the GNU Library General Public License as published by the 
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  grame@grame.fr

*/

#ifndef __msAtomicPPC__
#define __msAtomicPPC__

#define inline __inline__

//----------------------------------------------------------------
// Compare and swap
//----------------------------------------------------------------
static inline int CAS (register vtype void * addr, register void * value, register void * newvalue) 
{
	register int result;
	asm volatile (
       "# CAS					\n"
		"	lwarx	r0, 0, %1	\n"         /* creates a reservation on addr  */
		"	cmpw	r0, %2		\n"         /* test value at addr             */
		"	bne-	1f          \n"
        "	sync            	\n"         /* synchronize instructions       */
		"	stwcx.	%3, 0, %1	\n"         /* if the reservation is not altered */
                                            /* stores the new value at addr   */
		"	bne-	1f          \n"
        "   li      %0, 1       \n"
		"	b		2f          \n"
        "1:                     \n"
        "   li      %0, 0       \n"
        "2:                     \n"
       :"=r" (result)
	   : "r" (addr), "r" (value), "r" (newvalue)
       : "r0"
 	);
	return result;
}

//----------------------------------------------------------------
// Compare and swap link
//----------------------------------------------------------------
static inline int CASL (register vtype void * addr, register void * value) 
{
	register int result;
	register long tmp, next;
	asm volatile (
       "# CASL					\n"
		"	lwarx	%3, 0, %1	\n"         /* creates a reservation on addr  */
		"	cmpw	%3, %2		\n"         /* test value at addr             */
		"	bne-	1f          \n"
		"	lwzx	%4, 0, %3	\n"
        "	sync            	\n"         /* synchronize instructions       */
		"	stwcx.	%4, 0, %1	\n"         /* if the reservation is not altered */
                                            /* stores the new value at addr   */
		"	bne-	1f          \n"
        "   li      %0, 1       \n"
		"	b		2f          \n"
        "1:                     \n"
        "   li      %0, 0       \n"
        "2:                     \n"
       :"=r" (result)
	   : "r" (addr), "r" (value), "0" (tmp), "r" (next)
 	);
	return result;
}

#endif
