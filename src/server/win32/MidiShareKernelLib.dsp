# Microsoft Developer Studio Project File - Name="MidiShareKernelLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MidiShareKernelLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MidiShareKernelLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MidiShareKernelLib.mak" CFG="MidiShareKernelLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MidiShareKernelLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MidiShareKernelLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MidiShareKernelLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MIDISHAREKERNELLIB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../common/Headers" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MIDISHAREKERNELLIB_EXPORTS" /D "MSKernel" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /dll /machine:I386 /out:"MidiShareKernel.dll"

!ELSEIF  "$(CFG)" == "MidiShareKernelLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MIDISHAREKERNELLIB_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../common/Headers" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MIDISHAREKERNELLIB_EXPORTS" /D "MSKernel" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /dll /debug /machine:I386 /out:"MidiShareKernel.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MidiShareKernelLib - Win32 Release"
# Name "MidiShareKernelLib - Win32 Debug"
# Begin Source File

SOURCE=..\..\common\midishare.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msAlarms.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msAppls.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msConnx.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msDriver.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msEvents.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msFields.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msFilter.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msHandler.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msInit.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msMail.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msMemory.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msSeq.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msSmpte.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msSorter.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msTasks.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msTime.c
# End Source File
# Begin Source File

SOURCE=..\..\common\msXmtRcv.c
# End Source File
# End Target
# End Project
