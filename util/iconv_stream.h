#ifndef _ICONV_STREAM_H_
#define _ICONV_STREAM_H_

#include <sys/types.h>	/* size_t, ssize_t */
#include <stdio.h>	/* FILE */
#include "iconv.h"	/* iconv_t */

typedef ssize_t (*iconv_stream_func)(void *d, void *buf, size_t nbytes);

typedef struct {
	iconv_t		cd;
	size_t		chars;
	size_t		in_bytes;
	size_t		out_bytes;
	char *		buffer;
	char *		buf_ptr;
	void *		handle;
	iconv_stream_func method;
} iconv_stream;

iconv_stream *iconv_stream_open(iconv_t cd, void *handle,
                                iconv_stream_func method);
void iconv_stream_close(iconv_stream *stream);

iconv_stream *iconv_ostream_fopen(iconv_t cd, FILE *handle);

ssize_t iconv_write(void *stream, const void *buf, size_t nbytes);
ssize_t iconv_bwrite(void *stream, const void *buf, size_t nbytes);

#endif /*_ICONV_STREAM_H_*/
