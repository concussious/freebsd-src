/*-
 * Copyright (c) 2017 Kevin Lo <kevlo@FreeBSD.org>
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
 */

#include <sys/cdefs.h>
#include "opt_wlan.h"

#include <sys/param.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/mbuf.h>
#include <sys/kernel.h>
#include <sys/socket.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/queue.h>
#include <sys/taskqueue.h>
#include <sys/bus.h>
#include <sys/endian.h>
#include <sys/linker.h>

#include <net/if.h>
#include <net/ethernet.h>
#include <net/if_media.h>

#include <net80211/ieee80211_var.h>
#include <net80211/ieee80211_radiotap.h>

#include <dev/rtwn/if_rtwnreg.h>
#include <dev/rtwn/if_rtwnvar.h>

#include <dev/rtwn/rtl8192e/r92e.h>
#include <dev/rtwn/rtl8192e/r92e_reg.h>

uint32_t
r92e_rf_read(struct rtwn_softc *sc, int chain, uint8_t addr)
{
	uint32_t val;

	val = rtwn_bb_read(sc, R92C_HSSI_PARAM2(chain));
	rtwn_bb_write(sc, R92C_HSSI_PARAM2(chain),
	    RW(val, R92C_HSSI_PARAM2_READ_ADDR, addr) &
	    ~R92C_HSSI_PARAM2_READ_EDGE);

	rtwn_delay(sc, 10);
	rtwn_bb_setbits(sc, R92C_HSSI_PARAM2(0), R92C_HSSI_PARAM2_READ_EDGE, 0);
	rtwn_delay(sc, 100);
	rtwn_bb_setbits(sc, R92C_HSSI_PARAM2(0), 0, R92C_HSSI_PARAM2_READ_EDGE);
	rtwn_delay(sc, 20);

	if (rtwn_bb_read(sc, R92C_HSSI_PARAM1(chain)) & R92C_HSSI_PARAM1_PI)
		val = rtwn_bb_read(sc, R92C_HSPI_READBACK(chain));
	else
		val = rtwn_bb_read(sc, R92C_LSSI_READBACK(chain));
	return (MS(val, R92C_LSSI_READBACK_DATA));
}

void
r92e_rf_write(struct rtwn_softc *sc, int chain, uint8_t addr, uint32_t val)
{

	rtwn_bb_setbits(sc, 0x818, 0x20000, 0);
	rtwn_bb_write(sc, R92C_LSSI_PARAM(chain),
	    SM(R88E_LSSI_PARAM_ADDR, addr) | SM(R92C_LSSI_PARAM_DATA, val));
	rtwn_delay(sc, 1);
	rtwn_bb_setbits(sc, 0x818, 0, 0x20000);
}
