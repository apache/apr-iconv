/*-
 * Copyright (c) 1999,2000
 *	Konstantin Chuguev.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Konstantin Chuguev
 *	and its contributors.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	iconv (Charset Conversion Library) v1.0
 */

#ifndef HAVE_ICONV

#include <errno.h>	/* errno */
#include <stdlib.h>	/* free, malloc */
#include <string.h>

#define ICONV_INTERNAL
#include <iconv.h>

static struct iconv_converter_desc *converters[] = {
	&iconv_uc_desc,		/* CS1-UNICODE-CS2 converter */
/*	&iconv_tc_desc,	*/	/* XLAT (table based converter) */
	NULL
};

size_t
apr_iconv(iconv_t cd, const char **inbuf, size_t *inbytesleft,
	char **outbuf, size_t *outbytesleft)
{
	struct iconv_converter *icp = (struct iconv_converter *)cd;
	ssize_t res = -1;

	if (icp == NULL) {
		errno = EBADF;
		return (size_t)(-1);
	}
	if (outbytesleft == NULL || *outbytesleft == 0 ||
	    outbuf == NULL || *outbuf == 0) {
		errno = E2BIG;
		return (size_t)(-1);
	}
	res = icp->ic_desc->icd_conv(icp->ic_data,
	    (const unsigned char**)inbuf, inbytesleft,
	    (unsigned char**)outbuf, outbytesleft);
	return (size_t)res;
}

iconv_t
apr_iconv_open(const char *to, const char *from)
{
	struct iconv_converter_desc **idesc;
	struct iconv_converter *icp;
	void *data;
	int error;

	icp = malloc(sizeof(*icp));
	if (icp == NULL)
		return (iconv_t)(-1);
	error = EINVAL;
	for (idesc = converters; *idesc; idesc++) {
		error = (*idesc)->icd_open(to, from, &data);
		if (error == 0)
			break;
	}
	if (error) {
		free(icp);
		errno = error;
		return (iconv_t)(-1);
	}
	icp->ic_desc = *idesc;
	icp->ic_data = data;
	return (iconv_t)icp;
}

int
apr_iconv_close(iconv_t cd)
{
	struct iconv_converter *icp = (struct iconv_converter *)cd;
	int error = 0;

	if (icp == NULL) {
		errno = EBADF;
		return -1;
	}
	if (icp->ic_desc)
		error = icp->ic_desc->icd_close(icp->ic_data);
		
	free(icp);
	return error;
}

#else

#include <iconv.h>

iconv_t apr_iconv_open(const char *to_charset,
            const char *from_charset)
{
	return (iconv_open(to_charset, from_charset));
}

size_t apr_iconv(iconv_t cd, const char **inbuf,
            size_t *inbytesleft, char **outbuf,
            size_t *outbytesleft)
{
	return (iconv(cd , inbuf, inbytesleft, outbuf, outbytesleft));
}
int apr_iconv_close(iconv_t cd)
{
	return (iconv_close(cd));
}

#endif /* !defined(HAVE_ICONV) */
