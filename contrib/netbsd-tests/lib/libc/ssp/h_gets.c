/* $NetBSD: h_gets.c,v 1.1 2010/12/27 02:04:19 pgoyette Exp $ */

/*
 * Copyright (c) 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__COPYRIGHT("@(#) Copyright (c) 2008\
 The NetBSD Foundation, inc. All rights reserved.");
__RCSID("$NetBSD: h_gets.c,v 1.1 2010/12/27 02:04:19 pgoyette Exp $");

#include <stdio.h>

#ifdef __FreeBSD__
/* _FORTIFY_SOURCE, at the very least, may #define a gets() macro. */
#undef gets

/*
 * We want to test the gets() implementation, but cannot simply link against
 * the gets symbol because it is not in the default version. (We've made it
 * unavailable by default on FreeBSD because it should not be used.)
 *
 * The next two lines create an unsafe_gets() function that resolves to
 * gets@FBSD_1.0, which we call from our local gets() implementation.
 */
__sym_compat(gets, unsafe_gets, FBSD_1.0);
char *unsafe_gets(char *);

char *gets(char *buf)
{
	return unsafe_gets(buf);
}
#endif

int
main(int argc, char *argv[])
{
	char b[10];
	(void)gets(b);
	(void)printf("%s\n", b);
	return 0;
}
