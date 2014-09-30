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

/**
 * \file Compiler.h
 * System Compiler Abstraction according to AUTOSAR
 * This is an example, this file should be modified if the target
 * CPU changed.
 * This file is for WhatsApp Qt platform simulation running only.
 */
#ifndef COMPILER_H
#define COMPILER_H

/* ============================ [ INCLUDES ] ====================================================== */
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS   ] ====================================================== */
#define AUTOMATIC
#define STATIC 	static
#define NULL_PTR	((void *)0)

#define FUNC(rettype,memclass) rettype

#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#define CONSTP2VAR(ptrtype,memclass,ptrclass) ptrtype * const

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

#define P2FUNC(rettype,ptrclass,fctname) rettype (*fctname)

#define CONST(consttype,memclass) const consttype

#define Inline static __inline__

/* ============================ [ TYPES    ] ====================================================== */
/* ============================ [ DATAS    ] ====================================================== */
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  // name space
#endif
#endif /* COMPILER_H */
