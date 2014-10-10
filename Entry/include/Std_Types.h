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
 * \file Std_Types.h
 * System Standard Types according to AUTOSAR
 */
#ifndef STD_TYPES_H
#define STD_TYPES_H
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Compiler.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
#ifndef MIN
#define MIN(_x,_y) (((_x) < (_y)) ? (_x) : (_y))
#endif
#ifndef MAX
#define MAX(_x,_y) (((_x) > (_y)) ? (_x) : (_y))
#endif
#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1

#ifndef TRUE
#define TRUE                    (BOOL)1
#endif
#ifndef FALSE
#define FALSE                   (BOOL)0
#endif

#define STD_HIGH		0x01
#define STD_LOW			0x00

#define STD_ACTIVE		0x01
#define STD_IDLE		0x00

#define STD_ON			0x01
#define STD_OFF			0x00

#define UINT8_INVALID		((UINT8)(~0u))
#define UINT16_INVALID		((UINT16)(~0u))
#define UINT32_INVALID		((UINT32)(~0u))
/* ============================ [ TYPES     ] ====================================================== */
/*! \typedef Std_Types
 *  AUTOSAR Standard Basic Types.
 */
typedef unsigned char               boolean;
typedef signed char         		sint8;
typedef unsigned char       		uint8;
typedef signed short        		sint16;
typedef unsigned short      		uint16;
typedef signed long         	    sint32;
typedef unsigned long       		uint32;
typedef signed long long  			sint64;
typedef unsigned long long  		uint64;
typedef uint32                      uint8_least;
typedef uint32                      uint16_least;
typedef uint32                      uint32_least;
typedef uint32                      sint8_least;
typedef uint32                      sint16_least;
typedef uint32                      sint32_least;
typedef float                       float32;
typedef double                      float64;

typedef volatile sint8     vint8_t;
typedef volatile uint8     vuint8_t;
typedef volatile sint16    vint16_t;
typedef volatile uint16    vuint16_t;
typedef volatile sint32    vint32_t;
typedef volatile uint32    vuint32_t;
typedef volatile sint64    vint64_t;
typedef volatile uint64    vuint64_t;

typedef uint8               Std_ReturnType;

/* externed from toppers_osek */
typedef int					BOOL;		/* boolean */
typedef	signed char		    INT8;		/* 8 bit integer */
typedef	unsigned char		UINT8;		/* 8 bit unsigned integer */
typedef	signed short		INT16;		/* 16 bit integer */
typedef	unsigned short  	UINT16;	    /* 16 bit unsigned integer */
typedef	signed long	    	INT32;		/* 32 bit integer */
typedef	unsigned long	    UINT32;		/* 32 bit unsigned integer */
typedef	signed long long	INT64;		/* 64 bit unsigned intege */
typedef	unsigned long long  UINT64;		/* 64 bit unsigned intege */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  // name space
#endif
#endif /* STD_TYPES_H */
