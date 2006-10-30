# Microsoft Developer Studio Project File - Name="libapriconv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libapriconv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libapriconv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libapriconv.mak" CFG="libapriconv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libapriconv - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libapriconv - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libapriconv - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# ADD CPP /nologo /MD /W3 /Zi /O2 /Oy- /I "./include" /I "./lib" /I "../apr/include" /D "NDEBUG" /D "API_DECLARE_EXPORT" /D "WIN32" /D "_WINDOWS" /D "API_MODULE_STATIC" /Fd"Release\libapriconv_src" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "./include" /i "../apr/include" /d "NDEBUG" /d "API_VERSION_ONLY"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib advapi32.lib /nologo /base:"0x6EE50000" /subsystem:windows /dll /debug /machine:IX86 /opt:ref
# ADD LINK32 kernel32.lib advapi32.lib /nologo /base:"0x6EE50000" /subsystem:windows /dll /debug /machine:IX86 /out:"Release/libapriconv-1.dll" /opt:ref
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Desc=Embed .manifest
PostBuild_Cmds=if exist $(OUTDIR)\libapriconv-1.dll.manifest mt.exe -manifest $(OUTDIR)\libapriconv-1.dll.manifest -outputresource:$(OUTDIR)\libapriconv-1.dll;2
# End Special Build Tool

!ELSEIF  "$(CFG)" == "libapriconv - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /EHsc /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /I "./include" /I "./lib" /I "../apr/include" /D "_DEBUG" /D "API_DECLARE_EXPORT" /D "WIN32" /D "_WINDOWS" /D "API_MODULE_STATIC" /Fd"Debug\libapriconv_src" /FD /EHsc /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "./include" /i "../apr/include" /d "_DEBUG" /d "API_VERSION_ONLY"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib advapi32.lib /nologo /base:"0x6EE50000" /subsystem:windows /dll /incremental:no /debug /machine:IX86
# ADD LINK32 kernel32.lib advapi32.lib /nologo /base:"0x6EE50000" /subsystem:windows /dll /incremental:no /debug /machine:IX86 /out:"Debug/libapriconv-1.dll"
# Begin Special Build Tool
OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Desc=Embed .manifest
PostBuild_Cmds=if exist $(OUTDIR)\libapriconv-1.dll.manifest mt.exe -manifest $(OUTDIR)\libapriconv-1.dll.manifest -outputresource:$(OUTDIR)\libapriconv-1.dll;2
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "libapriconv - Win32 Release"
# Name "libapriconv - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ".c"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\iconv.c
# End Source File
# Begin Source File

SOURCE=.\lib\iconv_ces.c
# End Source File
# Begin Source File

SOURCE=.\lib\iconv_ces_euc.c
# End Source File
# Begin Source File

SOURCE=.\lib\iconv_ces_iso2022.c
# End Source File
# Begin Source File

SOURCE=.\lib\iconv_int.c
# End Source File
# Begin Source File

SOURCE=.\lib\iconv_module.c
# End Source File
# Begin Source File

SOURCE=.\lib\iconv_uc.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\include\api_version.h
# End Source File
# Begin Source File

SOURCE=.\include\apr_iconv.h
# End Source File
# Begin Source File

SOURCE=.\lib\charset_alias.h
# End Source File
# Begin Source File

SOURCE=.\lib\iconv.h
# End Source File
# End Group
# Begin Group "CCS Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\ccs\adobe-stdenc.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\adobe-symbol.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\adobe-zdingbats.c"
# End Source File
# Begin Source File

SOURCE=.\ccs\big5.c
# End Source File
# Begin Source File

SOURCE=".\ccs\cns11643-plane1.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\cns11643-plane14.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\cns11643-plane2.c"
# End Source File
# Begin Source File

SOURCE=.\ccs\cp037.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp038.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp10000.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp10006.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp10007.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp10029.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp1006.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp10079.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp10081.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp1026.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp273.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp274.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp275.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp277.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp278.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp280.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp281.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp284.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp285.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp290.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp297.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp420.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp423.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp424.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp437.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp500.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp737.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp775.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp850.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp851.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp852.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp855.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp856.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp857.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp860.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp861.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp862.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp863.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp864.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp865.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp866.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp868.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp869.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp870.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp871.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp874.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp875.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp880.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp891.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp903.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp904.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp905.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp918.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp932.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp936.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp949.c
# End Source File
# Begin Source File

SOURCE=.\ccs\cp950.c
# End Source File
# Begin Source File

SOURCE=".\ccs\dec-mcs.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-at-de-a.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-at-de.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-ca-fr.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-dk-no-a.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-dk-no.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-es-a.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-es-s.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-es.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-fi-se-a.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-fi-se.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-fr.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-it.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-pt.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-uk.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\ebcdic-us.c"
# End Source File
# Begin Source File

SOURCE=.\ccs\gb12345.c
# End Source File
# Begin Source File

SOURCE=".\ccs\gb_2312-80.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\hp-roman8.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-1.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-10.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-13.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-14.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-15.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-2.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-3.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-4.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-5.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-6.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-7.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-8.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-8859-9.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-10.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-102.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-103.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-11.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-111.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-121.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-122.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-123.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-128.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-13.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-139.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-14.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-141.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-142.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-143.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-146.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-147.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-15.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-150.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-151.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-152.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-153.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-154.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-155.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-158.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-16.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-17.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-18.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-19.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-2.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-21.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-25.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-27.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-37.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-4.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-47.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-49.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-50.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-51.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-54.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-55.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-57.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-60.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-61.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-69.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-70.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-8-1.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-8-2.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-84.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-85.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-86.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-88.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-89.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-9-1.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-9-2.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-90.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-91.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-92.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-93.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-94.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-95.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-96.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-98.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso-ir-99.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso646-dk.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\iso646-kr.c"
# End Source File
# Begin Source File

SOURCE=.\ccs\jis_x0201.c
# End Source File
# Begin Source File

SOURCE=".\ccs\jis_x0208-1983.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\jis_x0212-1990.c"
# End Source File
# Begin Source File

SOURCE=.\ccs\johab.c
# End Source File
# Begin Source File

SOURCE=".\ccs\koi8-r.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\koi8-ru.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\koi8-u.c"
# End Source File
# Begin Source File

SOURCE=.\ccs\ksx1001.c
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-ce.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-croatian.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-cyrillic.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-dingbats.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-greek.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-iceland.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-japan.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-roman.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-romania.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-thai.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-turkish.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\mac-ukraine.c"
# End Source File
# Begin Source File

SOURCE=.\ccs\macintosh.c
# End Source File
# Begin Source File

SOURCE=.\ccs\osd_ebcdic_df04_1.c
# End Source File
# Begin Source File

SOURCE=.\ccs\osd_ebcdic_df04_15.c
# End Source File
# Begin Source File

SOURCE=.\ccs\shift_jis.c
# End Source File
# Begin Source File

SOURCE=".\ccs\us-ascii.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1250.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1251.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1252.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1253.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1254.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1255.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1256.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1257.c"
# End Source File
# Begin Source File

SOURCE=".\ccs\windows-1258.c"
# End Source File
# End Group
# Begin Group "CES Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ces\_tbl_simple.c
# End Source File
# Begin Source File

SOURCE=".\ces\euc-jp.c"
# End Source File
# Begin Source File

SOURCE=".\ces\euc-kr.c"
# End Source File
# Begin Source File

SOURCE=".\ces\euc-tw.c"
# End Source File
# Begin Source File

SOURCE=.\ces\gb2312.c
# End Source File
# Begin Source File

SOURCE=".\ces\iso-10646-ucs-2.c"
# End Source File
# Begin Source File

SOURCE=".\ces\iso-10646-ucs-4.c"
# End Source File
# Begin Source File

SOURCE=".\ces\iso-2022-cn.c"
# End Source File
# Begin Source File

SOURCE=".\ces\iso-2022-jp-2.c"
# End Source File
# Begin Source File

SOURCE=".\ces\iso-2022-jp.c"
# End Source File
# Begin Source File

SOURCE=".\ces\iso-2022-kr.c"
# End Source File
# Begin Source File

SOURCE=".\ces\ucs2-internal.c"
# End Source File
# Begin Source File

SOURCE=".\ces\ucs4-internal.c"
# End Source File
# Begin Source File

SOURCE=".\ces\unicode-1-1-utf-7.c"
# End Source File
# Begin Source File

SOURCE=".\ces\utf-16.c"
# End Source File
# Begin Source File

SOURCE=".\ces\utf-8.c"
# End Source File
# End Group
# Begin Source File

SOURCE=.\libapriconv.rc
# End Source File
# End Target
# End Project
