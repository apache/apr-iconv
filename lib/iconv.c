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

#include <stdlib.h>	/* free, malloc */
#include <string.h>

#define ICONV_INTERNAL
#include "iconv.h"

static struct iconv_converter_desc *converters[] = {
	&iconv_uc_desc,		/* CS1-UNICODE-CS2 converter */
/*	&iconv_tc_desc,	*/	/* XLAT (table based converter) */
	NULL
};

/* 
 * size_t *result is what the iconv() returns but it is cleaner to return
 * a status.
 * APR_EBADF:   cd is not valid.
 * APR_BADARG: The ouput arguments are not valid.
 */

apr_status_t
apr_iconv(iconv_t cd, const char **inbuf, size_t *inbytesleft,
	char **outbuf, size_t *outbytesleft, size_t *result)
{
	struct iconv_converter *icp = (struct iconv_converter *)cd;

	if (icp == NULL) {
		*result = (size_t) -1;
		return(APR_EBADF);
	}
	if (outbytesleft == NULL || *outbytesleft == 0 ||
	    outbuf == NULL || *outbuf == 0) {
		*result = (size_t) -1;
		return(APR_BADARG);
	}
	return ( icp->ic_desc->icd_conv(icp->ic_data,
	    (const unsigned char**)inbuf, inbytesleft,
	    (unsigned char**)outbuf, outbytesleft, result));
}

apr_status_t
apr_iconv_open(const char *to, const char *from, apr_pool_t *ctx, iconv_t *res)
{
	struct iconv_converter_desc **idesc;
	struct iconv_converter *icp;
	void *data;
	apr_status_t error;

	*res = (iconv_t)-1;
	icp = malloc(sizeof(*icp));
	if (icp == NULL)
		return (APR_ENOMEM);
	error = APR_EINVAL;
	for (idesc = converters; *idesc; idesc++) {
		error = (*idesc)->icd_open(to, from, &data, ctx);
		if (error == APR_SUCCESS)
			break;
	}
	if (error) {
		free(icp);
		return (error);
	}
	icp->ic_desc = *idesc;
	icp->ic_data = data;
	*res = icp;
	return(APR_SUCCESS);
}

apr_status_t
apr_iconv_close(iconv_t cd, apr_pool_t *ctx)
{
	struct iconv_converter *icp = (struct iconv_converter *)cd;
	int error = 0;

	if (icp == NULL)
		return(APR_EBADF);

	if (icp->ic_desc)
		error = icp->ic_desc->icd_close(icp->ic_data, ctx);
		
	free(icp);
	return error;
}

#else

#include <iconv.h>

apr_status_t apr_iconv_open(const char *to_charset,
            const char *from_charset, apr_pool_t *ctx, iconv_t **res)
{
	*res = iconv_open(to_charset, from_charset);
	if (*res == (size_t) -1)
		return apr_get_os_error();
	return APR_SUCCESS;
}

apr_status_t apr_iconv(iconv_t cd, const char **inbuf,
            size_t *inbytesleft, char **outbuf,
            size_t *outbytesleft, size_t *result)
{
	*result = iconv(cd , inbuf, inbytesleft, outbuf, outbytesleft);
	if (*result == (size_t) -1)
		return apr_get_os_error();
	return APR_SUCCESS;
}
apr_status_t apr_iconv_close(iconv_t cd)
{
	int status;
	if (iconv_close(cd))
		return apr_get_os_error();
	return APR_SUCCESS;
}

#endif /* !defined(HAVE_ICONV) */
