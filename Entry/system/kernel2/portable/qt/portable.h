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
#ifndef CPU_CONTEX_H_H
#define CPU_CONTEX_H_H
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
extern void disable_int();
extern void enable_int();

extern void dispatch();

extern void set_ipl(IPL ipl);
extern IPL current_ipl(void);
extern void start_dispatch(void);
extern void exit_and_dispatch(void);
extern void activate_context(TaskType TaskID);

extern void EnterISR2(void);
extern void ExitISR2(void);
#ifdef __cplusplus
}} //namespace
#endif
#endif
