.include <src.opts.mk>

.PATH: ${SRCTOP}/contrib/libevent

PACKAGE= ntp
LIB= ntpevent
INTERNALLIB=

SRCS=	buffer.c bufferevent.c bufferevent_filter.c \
	bufferevent_pair.c epoll.c evdns.c event.c event_tagging.c \
	evmap.c evport.c evrpc.c evthread.c evthread_pthread.c evutil.c \
	evutil_rand.c evutil_time.c http.c kqueue.c listener.c log.c poll.c \
	select.c signal.c strlcpy.c

.if ${MK_OPENSSL} != "no"
SRCS+=	bufferevent_openssl.c
.endif

.if ${MACHINE_ARCH} == "i386"
NTP_ATOMIC=x86_32
.elif ${MACHINE_ARCH} == "amd64"
NTP_ATOMIC=x86_64
.elif ${MACHINE_ARCH} == "powerpc64"
NTP_ATOMIC=powerpc
.else
NTP_ATOMIC=noatomic
.endif

CFLAGS+= -I${SRCTOP}/contrib/ntp/include \
	-I${SRCTOP}/contrib/libevent/include \
	-I${.CURDIR}/

CFLAGS+= -DHAVE_BSD_NICE -DHAVE_STDINT_H

.include <bsd.lib.mk>
