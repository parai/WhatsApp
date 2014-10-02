/**
 * WhatsApp - the open source AUTOSAR platform https://github.com/parai
 *
 * Copyright (C) 2014  WhatsApp <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef OSLOG_H
#define OSLOG_H
#include <stdio.h>
#include <assert.h>

#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
#ifndef LOG_STAOS_ENTER
  #define LOG_STAOS_ENTER(mode)
#endif

#ifndef LOG_STAOS_LEAVE
  #define LOG_STAOS_LEAVE()
#endif

#ifndef LOG_TERTSK_ENTER
  #define LOG_TERTSK_ENTER()
#endif

#ifndef LOG_TERTSK_LEAVE
  #define LOG_TERTSK_LEAVE(ercd)
#endif

#ifndef LOG_STUTOS_ENTER
  #define LOG_STUTOS_ENTER(ercd)
#endif

#ifndef LOG_STUTOS_LEAVE
  #define LOG_STUTOS_LEAVE()
#endif

#ifndef LOG_ACTTSK_ENTER
  #define LOG_ACTTSK_ENTER(tskid)
#endif

#ifndef LOG_ACTTSK_LEAVE
  #define LOG_ACTTSK_LEAVE(ercd)
#endif

#ifndef LOG_SIGCNT_ENTER
  #define LOG_SIGCNT_ENTER(cntid)
#endif

#ifndef LOG_SIGCNT_LEAVE
  #define LOG_SIGCNT_LEAVE(ercd)
#endif

#ifndef LOG_SETREL_ENTER
  #define LOG_SETREL_ENTER(almid, incr, cycle)
#endif

#ifndef LOG_SETREL_LEAVE
  #define LOG_SETREL_LEAVE(ercd)
#endif

#ifndef LOG_SETABS_ENTER
  #define LOG_SETABS_ENTER(almid, incr, cycle)
#endif

#ifndef LOG_SETABS_LEAVE
  #define LOG_SETABS_LEAVE(ercd)
#endif

#ifndef LOG_SETEVT_ENTER
  #define LOG_SETEVT_ENTER(tskid, mask)
#endif

#ifndef LOG_SETEVT_LEAVE
  #define LOG_SETEVT_LEAVE(ercd)
#endif

#ifndef LOG_CLREVT_ENTER
  #define LOG_CLREVT_ENTER(mask)
#endif

#ifndef LOG_CLREVT_LEAVE
  #define LOG_CLREVT_LEAVE(ercd)
#endif

#ifndef LOG_GETEVT_ENTER
  #define LOG_GETEVT_ENTER(tskid, p_mask)
#endif

#ifndef LOG_GETEVT_LEAVE
  #define LOG_GETEVT_LEAVE(ercd, mask)
#endif

#ifndef LOG_WAIEVT_ENTER
  #define LOG_WAIEVT_ENTER(mask)
#endif

#ifndef LOG_WAIEVT_LEAVE
  #define LOG_WAIEVT_LEAVE(ercd)
#endif

#ifndef LOG_GETRES_ENTER
  #define LOG_GETRES_ENTER(resid)
#endif

#ifndef LOG_GETRES_LEAVE
  #define LOG_GETRES_LEAVE(ercd)
#endif

#ifndef LOG_RELRES_ENTER
  #define LOG_RELRES_ENTER(resid)
#endif

#ifndef LOG_RELRES_LEAVE
  #define LOG_RELRES_LEAVE(ercd)
#endif

#ifndef LOG_GETALB_ENTER
  #define LOG_GETALB_ENTER(almid, p_info)
#endif

#ifndef LOG_GETALB_LEAVE
  #define LOG_GETALB_LEAVE(ercd)
#endif

#ifndef LOG_GETALM_ENTER
  #define LOG_GETALM_ENTER(almid, p_tick)
#endif

#ifndef LOG_GETALM_LEAVE
  #define LOG_GETALM_LEAVE(ercd)
#endif

#ifndef LOG_CANALM_ENTER
  #define LOG_CANALM_ENTER(almid)
#endif

#ifndef LOG_CANALM_LEAVE
  #define LOG_CANALM_LEAVE(ercd)
#endif

#ifndef LOG_DISINT_ENTER
  #define LOG_DISINT_ENTER()
#endif

#ifndef LOG_DISINT_LEAVE
  #define LOG_DISINT_LEAVE()
#endif

#ifndef LOG_ENAINT_ENTER
  #define LOG_ENAINT_ENTER()
#endif

#ifndef LOG_ENAINT_LEAVE
  #define LOG_ENAINT_LEAVE()
#endif

#ifndef LOG_SUSALL_ENTER
  #define LOG_SUSALL_ENTER()
#endif

#ifndef LOG_SUSALL_LEAVE
  #define LOG_SUSALL_LEAVE()
#endif

#ifndef LOG_RSMALL_ENTER
  #define LOG_RSMALL_ENTER()
#endif

#ifndef LOG_RSMALL_LEAVE
  #define LOG_RSMALL_LEAVE()
#endif

#ifndef LOG_SUSOSI_ENTER
  #define LOG_SUSOSI_ENTER()
#endif

#ifndef LOG_SUSOSI_LEAVE
  #define LOG_SUSOSI_LEAVE()
#endif

#ifndef LOG_RSMOSI_ENTER
  #define LOG_RSMOSI_ENTER()
#endif

#ifndef LOG_RSMOSI_LEAVE
  #define LOG_RSMOSI_LEAVE()
#endif

#ifndef LOG_GETAAM_ENTER
  #define LOG_GETAAM_ENTER()
#endif

#ifndef LOG_GETAAM_LEAVE
  #define LOG_GETAAM_LEAVE(mode)
#endif

#ifndef LOG_CHNTSK_ENTER
  #define LOG_CHNTSK_ENTER(tskid)
#endif

#ifndef LOG_CHNTSK_LEAVE
  #define LOG_CHNTSK_LEAVE(ercd)
#endif

#ifndef LOG_SCHED_ENTER
  #define LOG_SCHED_ENTER()
#endif

#ifndef LOG_SCHED_LEAVE
  #define LOG_SCHED_LEAVE(ercd)
#endif

#ifndef LOG_GETTID_ENTER
  #define LOG_GETTID_ENTER(p_tskid)
#endif

#ifndef LOG_GETTID_LEAVE
  #define LOG_GETTID_LEAVE(ercd, p_tskid)
#endif

#ifndef LOG_GETTST_ENTER
  #define LOG_GETTST_ENTER(tskid,p_state)
#endif

#ifndef LOG_GETTST_LEAVE
  #define LOG_GETTST_LEAVE(ercd, p_state)
#endif
#ifdef __cplusplus
}} // namespace
#endif
#endif /* OSLOG_H */
