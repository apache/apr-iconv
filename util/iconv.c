/*-
 * Copyright (c) 1999
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
 *	iconv (Charset Conversion Library) v0.3
 */

#include "apr.h"

#include <stdarg.h>	/* va_end, va_list, va_start */
#include <stdio.h>	/* FILE, fclose, ferror, fopen, fread, stdin,
                           vfprintf */
#include <stdlib.h>	/* exit */
#include <unistd.h>	/* getopt */

#include "iconv_stream.h"

static void
convert_stream(FILE *in, iconv_stream *out)
{
	static char buffer[4096];
	size_t size;

	while ((size = fread(buffer, 1, sizeof(buffer), in))) {
    		if (iconv_bwrite(out, buffer, size) <= 0) {
			fprintf(stderr, "convert_stream: conversion stream writing error\n");
			exit(2);
		}
	}
	if (ferror(in)) {
		fprintf(stderr, "convert_stream: input file reading error\n");
		exit(1);
	}
}

static void
convert_file(const char *name, iconv_stream *is)
{
	int std = (name[0] == '-' && name[1] == '\0');
	FILE *fp = std ? stdin : fopen(name, "r");

	if (fp == NULL) {
		fprintf(stderr, "cannot open file %s\n", name);
		return;
	}
	convert_stream(fp, is);
	if (!std)
    		fclose(fp);
}

static void closeapr(void)
{
    apr_terminate();
}

int
main(int argc, char * const *argv)
{
	iconv_t cd;
	iconv_stream *is;
	char *from = NULL, *to = NULL, *input = NULL;
	int opt;
	apr_pool_t *ctx; 
	apr_status_t status;

	while ((opt = getopt(argc, argv, "f:s:t:")) > 0) {
		switch (opt) {
		    case 'f':
			from = optarg;
			break;
		    case 't':
			to = optarg;
			break;
		    case 's':
			input = optarg;
		}
	}
	if (from == NULL) {
		fprintf(stderr, "missing source charset (-f <name>)\n");
		exit(4);
	}
	if (to == NULL) {
		fprintf(stderr, "missing destination charset (-t <name>)\n");
		exit(5);
	}

	/* Initialize APR */
	apr_initialize();
	atexit(closeapr);
	if (apr_pool_create(&ctx, NULL) != APR_SUCCESS) {
		fprintf(stderr, "Couldn't allocate context.\n");
		exit(-1);
	}

	/* Use it */
	status = apr_iconv_open(to, from,ctx, &cd);
	if (status) {
		fprintf(stderr, "unable to open specified convertor\n");
		exit(6);
		}
	if (!(is = iconv_ostream_fopen(cd, stdout))) {
		apr_iconv_close(cd,ctx);
		exit(7);
	}
	if (input) {
		if (iconv_bwrite(is, input, strlen(input)) <= 0)
			exit(8);
	} else if (optind < argc) {
		for (opt = optind; opt < argc; opt ++)
			convert_file(argv[opt], is);
	} else
		convert_file("-", is);
	if (iconv_write(is, NULL, 0) < 0)
		exit(9);
	iconv_stream_close(is);
	apr_iconv_close(cd,ctx);
	return 0;
}
