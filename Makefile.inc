MODULEDIR=	${PREFIX}/lib/iconv

.if !defined(ICONVDIR)
CFLAGS+=	-I/usr/local/include
LDADD+=		-L/usr/local/lib
.endif

all:		${MODULES}

LDADD+=		-liconv

INTERNALLIB=
SYMLINKS !=	../cs-aliases -p ${MODULEDIR} charset.aliases

NOMAN=

NOOBJ=
CLEANFILES=	${MODULES} *.So

.SUFFIXES:	.so .So

.So.so:
	@${LDDESTDIRENV} ${CC} -shared -Wl,-x -o ${.TARGET} \
		-Wl,-soname,${.TARGET} `lorder ${.ALLSRC} | tsort -q` \
		${LDDESTDIR} ${LDADD}

beforeinstall:
		@mkdir -p ${MODULEDIR}
		${INSTALL} ${COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
		${INSTALLFLAGS} ${SHLINSTALLFLAGS} ${MODULES} \
		${DESTDIR}${MODULEDIR}

.include <bsd.lib.mk>
.SUFFIXES:	.so .c
