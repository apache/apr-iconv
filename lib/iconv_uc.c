#define ICONV_INTERNAL
#include "iconv.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct iconv_uc {
	struct iconv_ces *	from;
	struct iconv_ces *	to;
	int			ignore_ilseq;
	ucs_t			missing;
};

static iconv_open_t iconv_uc_open;
static iconv_close_t iconv_uc_close;
static iconv_conv_t iconv_uc_conv;

struct iconv_converter_desc iconv_uc_desc = {
	iconv_uc_open,
	iconv_uc_close,
	iconv_uc_conv
};

int
iconv_uc_open(const char *to, const char *from, void **data, apr_pool_t *ctx)
{
	struct iconv_uc *ic;
	int error;

	ic = malloc(sizeof(*ic));
	if (ic == NULL)
		return ENOMEM;
	memset(ic, 0, sizeof(*ic));
	error = iconv_ces_open(from, &ic->from, ctx);
	if (error)
		goto bad;
	error = iconv_ces_open(to, &ic->to, ctx);
	if (error)
		goto bad;
	ic->ignore_ilseq = 0;
	ic->missing = '_';
	*data = (void*)ic;
	return 0;
bad:
	iconv_uc_close(ic,ctx);
	return error;
}

int
iconv_uc_close(void *data, apr_pool_t *ctx)
{
	struct iconv_uc *ic = (struct iconv_uc *)data;

	if (ic == NULL)
		return EBADF;
	if (ic->from)
		iconv_ces_close(ic->from, ctx);
	if (ic->to)
		iconv_ces_close(ic->to, ctx);
	free(ic);
	return 0;
}

size_t
iconv_uc_conv(void *data, const unsigned char **inbuf, size_t *inbytesleft,
	unsigned char **outbuf, size_t *outbytesleft)
{
	struct iconv_uc *ic = (struct iconv_uc *)data;
	const unsigned char *ptr;
	ucs_t ch;
        ssize_t size;
	size_t res = 0;

	if (data == NULL) {
		errno = EBADF;
		return (size_t)(-1);
	}
	if (inbuf == NULL || *inbuf == NULL) {
		if (ICONV_CES_CONVERT_FROM_UCS(ic->to, UCS_CHAR_NONE,
		    outbuf, outbytesleft) <= 0) {
			errno = E2BIG;
			return (size_t)(-1);
		}
		ICONV_CES_RESET(ic->from);
		ICONV_CES_RESET(ic->to);
		return res;
	}
	if (inbytesleft == NULL || *inbytesleft == 0)
		return 0;
	while (*inbytesleft > 0 && *outbytesleft > 0) {
		ptr = *inbuf;
		ch = ICONV_CES_CONVERT_TO_UCS(ic->from, inbuf, inbytesleft);
		if (ch == UCS_CHAR_NONE) {
			errno = EINVAL;
			return res;
		}
		if (ch == UCS_CHAR_INVALID) { /* Invalid character in source buffer */
			if (ic->ignore_ilseq)
				continue;
			*inbytesleft += *inbuf - ptr;
			*inbuf = ptr;
			errno = EILSEQ;
			return res;
		}
		size = ICONV_CES_CONVERT_FROM_UCS(ic->to, ch,
		    outbuf, outbytesleft);
		if (size < 0) {		 /* No equivalent in destination charset */
			size = ICONV_CES_CONVERT_FROM_UCS(ic->to, ic->missing,
			    outbuf, outbytesleft);
			if (size)
				res ++;
		}
		if (!size) {		 /* No space to write to */
			*inbytesleft += *inbuf - ptr;
			*inbuf = ptr; 
			errno = E2BIG;
			return res;
		}
	}
	return res;
}

#if 0
/* iconv_byteratio(cd) returns the byte ratio between OUTPUT and INPUT
 *                     stream lengths
 * -1: unknown
 *  0: 1/2
 *  1: 1/1
 *  2: 2/1
 */
int
iconv_byteratio(iconv_t cd)
{
	iconv_data *idata = (iconv_data *)cd;
	int from, to;

	to = (*idata->to->data->nbytes)(idata->to);
	if (to == 0)
		return -1;
	from = (*idata->from->data->nbytes)(idata->from);
	return (from) ? to / from : -1;
}
#endif
