#
# SPDX-License-Idendifier: BSD-2-Clause
#
# Copyright (c) 2025 FreeBSD Foundation
#
# This sofware was developed by Cy Schubert <cy@FreeBSD.org>
# under sponsorship from the FreeBSD Foundation.
#

PACKAGE=	kerberos-lib

.include "../Makefile.inc"

SCRIPTS=	krb5-config.sh
BINDIR?=	/usr/bin

MAN=	krb5-config.1

CLEANFILES=	krb5-config.1

krb5-config.1: krb5-config.man

.include <bsd.prog.mk>

.SUFFIXES: .sh .man .1

.man.1:
	@cp ${.ALLSRC} ${.TARGET}

.PATH:	${KRB5_DIR}/build-tools \
	${KRB5_DIR}/man \
	${KRB5_OBJTOP}/build-tools
