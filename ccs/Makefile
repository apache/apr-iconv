.include "../Makefile.inc"

CHARSETS_ISO8859 = iso-8859-1.so iso-8859-2.so iso-8859-4.so iso-8859-5.so \
                   iso-8859-15.so
CHARSETS_PC =      cp775.so cp850.so cp852.so cp855.so cp866.so
CHARSETS_KOI =     koi8-r.so koi8-u.so
CHARSETS_SB =      $(CHARSETS_ISO8859) $(CHARSETS_PC) $(CHARSETS_CJK) \
                   $(CHARSETS_KOI) us-ascii.so
CHARSETS_CJK =     big5.so cns11643-plane1.so cns11643-plane2.so \
                   cns11643-plane14.so gb_2312-80.so jis_x0201.so \
                   jis_x0208-1983.so jis_x0212-1990.so ksx1001.so shift_jis.so
CHARSETS_ALL =     ${CHARSETS_SB} ${CHARSETS_CJK}
EXTRA_ISO8859 =    iso-8859-3.so iso-8859-6.so iso-8859-7.so iso-8859-8.so \
                   iso-8859-9.so iso-8859-10.so iso-8859-13.so iso-8859-14.so
EXTRA_KOI =        koi8-ru.so 
EXTRA_MISC =       gb12345.so johab.so adobe-stdenc.so adobe-symbol.so \
                   adobe-zdingbats.so mac-ce.so mac-croatian.so mac-cyrillic.so \
                   mac-dingbats.so mac-greek.so mac-iceland.so mac-japan.so \
                   mac-roman.so mac-romania.so mac-thai.so mac-turkish.so \
                   mac-ukraine.so
EXTRA_PC =         cp424.so cp500.so cp856.so cp1006.so cp437.so cp737.so cp857.so \
                   cp860.so cp861.so cp862.so cp863.so cp864.so cp865.so cp869.so \
                   cp874.so cp932.so cp936.so cp949.so cp950.so \
                   windows-1250.so windows-1251.so windows-1252.so windows-1253.so \
                   windows-1254.so windows-1255.so windows-1256.so windows-1257.so \
                   windows-1258.so cp037.so cp875.so cp1026.so \
                   cp10000.so cp10006.so cp10007.so cp10029.so cp10079.so cp10081.so
EXTRA_ALL =        ${EXTRA_ISO8859} ${EXTRA_KOI} ${EXTRA_MISC} ${EXTRA_PC}
RFC1345_PC =       cp851.so cp868.so cp038.so cp273.so cp274.so cp275.so cp277.so \
                   cp278.so cp280.so cp281.so cp284.so cp285.so cp290.so cp297.so \
                   cp420.so cp423.so cp870.so cp871.so cp880.so cp891.so \
                   cp903.so cp904.so cp905.so cp918.so
RFC1345_EBCDIC =   ebcdic-at-de.so ebcdic-at-de-a.so ebcdic-ca-fr.so \
                   ebcdic-dk-no.so ebcdic-dk-no-a.so ebcdic-es.so ebcdic-es-a.so \
                   ebcdic-es-s.so ebcdic-fi-se.so ebcdic-fi-se-a.so ebcdic-fr.so \
                   ebcdic-it.so ebcdic-pt.so ebcdic-uk.so ebcdic-us.so
RFC1345_IR =       iso-ir-2.so iso-ir-4.so iso-ir-8-1.so iso-ir-8-2.so \
                   iso-ir-9-1.so iso-ir-9-2.so iso-ir-10.so iso-ir-11.so \
                   iso-ir-13.so iso-ir-14.so iso-ir-15.so iso-ir-16.so \
                   iso-ir-17.so iso-ir-18.so iso-ir-19.so iso-ir-21.so \
                   iso-ir-25.so iso-ir-27.so iso-ir-37.so iso-ir-47.so \
                   iso-ir-49.so iso-ir-50.so iso-ir-51.so iso-ir-54.so \
                   iso-ir-55.so iso-ir-57.so iso-ir-60.so iso-ir-61.so \
                   iso-ir-69.so iso-ir-70.so iso-ir-84.so iso-ir-85.so \
                   iso-ir-86.so iso-ir-88.so iso-ir-89.so iso-ir-90.so \
                   iso-ir-91.so iso-ir-92.so iso-ir-93.so iso-ir-94.so \
                   iso-ir-95.so iso-ir-96.so iso-ir-98.so iso-ir-99.so \
                   iso-ir-102.so iso-ir-103.so iso-ir-111.so iso-ir-121.so \
                   iso-ir-122.so iso-ir-123.so iso-ir-128.so iso-ir-139.so \
                   iso-ir-141.so iso-ir-142.so iso-ir-143.so iso-ir-146.so \
                   iso-ir-147.so iso-ir-150.so iso-ir-151.so iso-ir-152.so \
                   iso-ir-153.so iso-ir-154.so iso-ir-155.so iso-ir-158.so
RFC1345_MISC =     dec-mcs.so hp-roman8.so iso646-dk.so iso646-kr.so macintosh.so
RFC1345_ALL =      ${RFC1345_PC} ${RFC1345_EBCDIC} ${RFC1345_IR} ${RFC1345_MISC}

MODULES =          ${CHARSETS_ALL} ${EXTRA_ALL} ${RFC1345_ALL}

all:            ${MODULES}

LDADD=          -L${.CURDIR}/../lib -liconv

INTERNALLIB=
SYMLINKS !=     ../cs-aliases -p ${MODULEDIR} charset.aliases

NOMAN=

beforeinstall:
                @mkdir -p ${MODULEDIR}
                ${INSTALL} ${COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
                ${INSTALLFLAGS} ${SHLINSTALLFLAGS} ${MODULES} \
                ${DESTDIR}${MODULEDIR}

CLEANFILES=     ${MODULES} *.So

.include <bsd.lib.mk>
.SUFFIXES:      .so .c
