PROG=		iconv
SRCS=		iconv.c iconv_stream.c

LDADD=		-L../lib -liconv
DPADD+=		../lib/libiconv.a

BINDIR=		${PREFIX}/bin

MAN1=		iconv.1

.include <bsd.prog.mk>
