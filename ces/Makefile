.include "../Makefile.inc"

MODULES_CORE=   _tbl_simple.so euc-jp.so euc-kr.so euc-tw.so gb2312.so \
                iso-10646-ucs-2.so iso-10646-ucs-4.so \
                ucs2-internal.so ucs4-internal.so utf-8.so utf-16.so

MODULES_EXTRA = unicode-1-1-utf-7.so iso-2022-cn.so iso-2022-jp.so \
                iso-2022-jp-2.so iso-2022-kr.so

MODULES =       ${MODULES_CORE} ${MODULES_EXTRA}

all:    ${MODULES}

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
.SUFFIXES:      .so
