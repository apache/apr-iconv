# Microsoft Developer Studio Project File - Name="libapriconv_ces_modules" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=libapriconv_ces_modules - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libapriconv_ces_modules.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libapriconv_ces_modules.mak" CFG="libapriconv_ces_modules - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libapriconv_ces_modules - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "libapriconv_ces_modules - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE "libapriconv_ces_modules - Win32 ReleaseNT" (based on "Win32 (x86) External Target")
!MESSAGE "libapriconv_ces_modules - Win32 DebugNT" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "libapriconv_ces_modules - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "..\Release\iconv"
# PROP BASE Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=release BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "libapriconv_ces_modules.exe"
# PROP BASE Bsc_Name "libapriconv_ces_modules.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "..\Release\iconv"
# PROP Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=release BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Release"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "libapriconv_ces_modules - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "..\Debug\iconv"
# PROP BASE Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=debug BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "libapriconv_ces_modules.exe"
# PROP BASE Bsc_Name "libapriconv_ces_modules.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "..\Debug\iconv"
# PROP Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=debug BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Debug"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "libapriconv_ces_modules - Win32 ReleaseNT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "..\Release\iconv"
# PROP BASE Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=release BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)NT\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "libapriconv_ces_modules.exe"
# PROP BASE Bsc_Name "libapriconv_ces_modules.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "..\Release\iconv"
# PROP Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=release BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)NT\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Release"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "libapriconv_ces_modules - Win32 DebugNT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "..\Debug\iconv"
# PROP BASE Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=debug BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)NT\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "libapriconv_ces_modules.exe"
# PROP BASE Bsc_Name "libapriconv_ces_modules.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "..\Debug\iconv"
# PROP Cmd_Line "NMAKE /nologo /f Makefile.win BUILD_MODE=debug BIND_MODE=shared API_LIBS="..\..\apr\$(OutDir)NT\libapr-1.lib ..\$(OutDir)\libapriconv-1.lib" CFG_OUTPUT="$(IntDir)" OUTPUT_DIR="..\$(IntDir)""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Debug"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "libapriconv_ces_modules - Win32 Release"
# Name "libapriconv_ces_modules - Win32 Debug"
# Name "libapriconv_ces_modules - Win32 ReleaseNT"
# Name "libapriconv_ces_modules - Win32 DebugNT"

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_tbl_simple.c
# End Source File
# Begin Source File

SOURCE=".\euc-jp.c"
# End Source File
# Begin Source File

SOURCE=".\euc-kr.c"
# End Source File
# Begin Source File

SOURCE=".\euc-tw.c"
# End Source File
# Begin Source File

SOURCE=.\gb2312.c
# End Source File
# Begin Source File

SOURCE=".\iso-10646-ucs-2.c"
# End Source File
# Begin Source File

SOURCE=".\iso-10646-ucs-4.c"
# End Source File
# Begin Source File

SOURCE=".\iso-2022-cn.c"
# End Source File
# Begin Source File

SOURCE=".\iso-2022-jp-2.c"
# End Source File
# Begin Source File

SOURCE=".\iso-2022-jp.c"
# End Source File
# Begin Source File

SOURCE=".\iso-2022-kr.c"
# End Source File
# Begin Source File

SOURCE=".\ucs2-internal.c"
# End Source File
# Begin Source File

SOURCE=".\ucs4-internal.c"
# End Source File
# Begin Source File

SOURCE=".\unicode-1-1-utf-7.c"
# End Source File
# Begin Source File

SOURCE=".\utf-16.c"
# End Source File
# Begin Source File

SOURCE=".\utf-8.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\lib\iconv.h
# End Source File
# End Group
# End Target
# End Project
