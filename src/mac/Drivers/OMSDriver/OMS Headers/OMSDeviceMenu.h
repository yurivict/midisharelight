/*
	OMSDeviceMenu.h
	
	Application interface for Opcode MIDI System's pop-up device menus
	Doug Wyatt, Opcode Systems
	Copyright �1990-96 Opcode Systems, Inc., All Rights Reserved
*/
#ifndef __OMSDeviceMenu__
#define __OMSDeviceMenu__
#pragma once

#include "OMS.h"

/*
	Bits of flags in the device menu
*/
enum {
	odmFrameBox = 1,
	odmAllowMultSelections = 2,
	odmBold = 4
};

#if       OMS_WINDOWS
#define kOMSDevMenuID	0x4f44		// OD
#endif // OMS_WINDOWS

#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=mac68k
#endif
typedef struct OMSDeviceMenuItemInfo {
	unsigned char		spare;			/* must be 0 */
	unsigned char		itemType;		/* 0=oms node, 1-127 reserved, 128-255 user */
	OMSUniqueID			uniqueID;		/* 0 = nonexistant */
} OMSDeviceMenuItemInfo;


typedef struct OMSDeviceMenu {
	OMSMenuHandle			theMenu;			/* owned by prototype */
	OMSDeviceMenuItemInfo	**itemInfo;			/* owned by prototype */
	short					nItems;
	OMSBool					theMenuShared;		/* true if shared with other 
													OMSDeviceMenu's */
	unsigned char			flags;
	short					desiredNodeTypes;	/* unneeded if shared */
	OMSNodeFilterProcUPP	filterProc;			/* unneeded if shared */
	OMSWindowPtr			menuPort;
	OMSRect					menuBoxRect;
	OMSDeviceMenuItemInfo	**multiSelections;	/* NULL unless multiple selections allowed */
	
	/* none of the following are valid when multiple selections allowed */
	OMSDeviceMenuItemInfo	select;				/* itemInfo for selected item */
	OMSString				selectedName;
	short					selectedItemNum;
	short					selectedRefNum;		/* for app to read, -1 is non-existant */
	OMSDeviceH				selectedDeviceH;	/* for app to read - can be null! */
	
	struct OMSDeviceMenu	**prototype;		/* the prototype, if this one is shared */
#if       OMS_WINDOWS
	OMSFontHandle			fontHandle;			/* the font used in this device menu */
												/* NULL if default used */
#endif // OMS_WINDOWS
} OMSDeviceMenu, ** OMSDeviceMenuH;
#if OMS_MAC_PRAGMA_ALIGN
#pragma options align=reset
#endif

OMSAPI(OMSDeviceMenuH) OMSNewDeviceMenu(	OMSWindowPtr			theWindow,
											OMSDeviceMenuH			shareMenuWith, 
											unsigned char			flags,
											OMSRect 				*location,
											short 					desiredNodeTypes,
											OMSNodeFilterProcUPP	filterProc,
											OMSFontSpec				*font );
#if       OMS_MACINTOSH
OMSAPI(OMSDeviceMenuH) NewOMSDeviceMenu(OMSDeviceMenuH shareMenuWith, 
						unsigned char flags, OMSRect *location,
						short desiredNodeTypes, OMSNodeFilterProcUPP filterProc);
			
#endif // OMS_MACINTOSH

#if       OMS_WINDOWS
OMSAPI(OMSDeviceMenu *) OMSGetOMSDeviceMenuPtr( HWND theDeviceMenuHWND );
#endif // OMS_WINDOWS

OMSAPI(OMSBool) TestOMSDeviceMenu(OMSDeviceMenuH menu, OMSPoint pt);

OMSAPI(short)	ClickOMSDeviceMenu(OMSDeviceMenuH menu);

OMSAPI(short)	OMSCountDeviceMenuItems( OMSDeviceMenuH theDeviceMenu );

OMSAPI(void)	DisposeOMSDeviceMenu(OMSDeviceMenuH menu);

OMSAPI(void)	DrawOMSDeviceMenu(OMSDeviceMenuH menu);

OMSAPI(void)	SetOMSDeviceMenuSelection(OMSDeviceMenuH menu, unsigned char itemType, 
					OMSUniqueID uniqueID, OMSStringPtr name, OMSBool selected);
			
OMSAPI(void)	RebuildOMSDeviceMenu(OMSDeviceMenuH menu);

OMSAPI(void)	AppendOMSDeviceMenu(OMSDeviceMenuH menu, unsigned char itemType, 
					OMSUniqueID uniqueID, OMSStringPtr itemName);

#endif	/* __OMSDeviceMenu__ */
