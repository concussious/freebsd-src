.include <src.opts.mk>

LIB=		ssl
SHLIB_MAJOR=	30
VERSION_MAP=	${.CURDIR}/Version.map
PACKAGE=	openssl-lib

PCFILES=	libssl.pc openssl.pc

.include "../libcrypto/Makefile.inc"

SRCS=	bio_ssl.c d1_lib.c d1_msg.c d1_srtp.c methods.c pqueue.c
SRCS+=	s3_cbc.c s3_enc.c s3_lib.c s3_msg.c ssl_asn1.c ssl_cert.c ssl_ciph.c
SRCS+=	ssl_conf.c ssl_err.c ssl_err_legacy.c ssl_init.c ssl_lib.c ssl_mcnf.c
SRCS+=	ssl_rsa.c ssl_rsa_legacy.c ssl_sess.c ssl_stat.c ssl_txt.c ssl_utst.c
SRCS+=	t1_enc.c t1_lib.c t1_trce.c tls_depr.c tls_srp.c tls13_enc.c

# crypto
SRCS+=	packet.c sparse_array.c

# record
SRCS+=	dtls1_bitmap.c rec_layer_d1.c rec_layer_s3.c ssl3_buffer.c
SRCS+=	ssl3_record.c ssl3_record_tls13.c tls_pad.c

# statem
SRCS+=	extensions.c extensions_clnt.c extensions_cust.c extensions_srvr.c
SRCS+=	statem.c statem_clnt.c statem_dtls.c statem_lib.c statem_srvr.c

.if ${MK_OPENSSL_KTLS} != "no"
SRCS+=	ktls.c
.else
CFLAGS+=-DOPENSSL_NO_KTLS
.endif

LIBADD=	crypto

CFLAGS+=	-I${LCRYPTO_SRC}/ssl
CFLAGS+=	-I${.OBJDIR:H}/libcrypto

.include <bsd.lib.mk>

PICFLAG+=	-DOPENSSL_PIC

.PATH:	${LCRYPTO_SRC}/crypto \
	${LCRYPTO_SRC}/ssl \
	${LCRYPTO_SRC}/ssl/record \
	${LCRYPTO_SRC}/ssl/statem
