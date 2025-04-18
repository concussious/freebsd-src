#!/bin/ksh -p
# SPDX-License-Identifier: CDDL-1.0
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or https://opensource.org/licenses/CDDL-1.0.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

#
# Copyright (c) 2013, 2016 by Delphix. All rights reserved.
#

. $STF_SUITE/include/libtest.shlib
. $STF_SUITE/tests/functional/mv_files/mv_files_common.kshlib

verify_runnable "global"

[[ -f $TEST_BASE_DIR/exitsZero.ksh ]] &&
	log_must rm -f $TEST_BASE_DIR/exitsZero.ksh
[[ -f $TEST_BASE_DIR/testbackgprocs.ksh ]] &&
	log_must rm -f $TEST_BASE_DIR/testbackgprocs.ksh

ismounted $TESTPOOL/$TESTFS_TGT ||log_must zfs umount $TESTPOOL/$TESTFS_TGT
log_must zfs destroy $TESTPOOL/$TESTFS_TGT

[[ -d $TESTDIR_TGT ]] && log_must rm -rf $TESTDIR_TGT

default_cleanup
