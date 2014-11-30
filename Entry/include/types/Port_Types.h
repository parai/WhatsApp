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
 * Version: AUTOSAR 4.2.0
 * Generated by arxml.py
 */
#ifndef PORT_TYPES_H
#define PORT_TYPES_H

#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* The initial direction of the pin (IN or OUT). If the direction is not changeable, the value
 *  configured here is fixed.
 */
typedef enum
{
	PORT_PIN_IN,
	PORT_PIN_OUT,
} Port_PinDirectionType ;

/* Port pin mode from mode list for use with Port_Init() function. */
typedef enum
{
	PORT_PIN_MODE_ADC,
	PORT_PIN_MODE_CAN,
	PORT_PIN_MODE_DIO,
	PORT_PIN_MODE_DIO_GPT,
	PORT_PIN_MODE_DIO_WDG,
	PORT_PIN_MODE_FLEXRAY,
	PORT_PIN_MODE_ICU,
	PORT_PIN_MODE_LIN,
	PORT_PIN_MODE_MEM,
	PORT_PIN_MODE_PWM,
	PORT_PIN_MODE_SPI,
} Port_PinInitialModeType ;

/* Port Pin Level value from Port pin list. */
typedef enum
{
	PORT_PIN_LEVEL_HIGH,
	PORT_PIN_LEVEL_LOW,
} Port_PinLevelValueType ;

/* Port pin mode from mode list. */
typedef enum
{
	PORT_PIN_MODE_ADC,
	PORT_PIN_MODE_CAN,
	PORT_PIN_MODE_DIO,
	PORT_PIN_MODE_DIO_GPT,
	PORT_PIN_MODE_DIO_WDG,
	PORT_PIN_MODE_FLEXRAY,
	PORT_PIN_MODE_ICU,
	PORT_PIN_MODE_LIN,
	PORT_PIN_MODE_MEM,
	PORT_PIN_MODE_PWM,
	PORT_PIN_MODE_SPI,
} Port_PinModeType ;

/* Configuration of the individual port pins. */
typedef struct
{
/* The direction must match the pin mode. E.g. a pin used for an ADC must be configured to be an
 *  in port.
 * 
 *                                                         Implementation Type: Port_PinDirectionType
 */
	Port_PinDirectionType PortPinDirection ;
/* true: Port Pin direction changeable enabled.
 *                                                         false: Port Pin direction changeable
 *  disabled.
 */
/* Parameter to indicate if the direction is changeable on a port pin during runtime. */
	boolean PortPinDirectionChangeable ;
/* Pin Id of the port pin. This value will be assigned to the symbolic name derived from the port
 *  pin container short name.
 */
	uint16 PortPinId ;
	Port_PinInitialModeType PortPinInitialMode ;
	Port_PinLevelValueType PortPinLevelValue ;
/* Note that more than one mode is allowed by default. That way it is e.g. possible to combine
 *  DIO with another mode such as ICU.
 */
	Port_PinModeType PortPinMode ;
/* Parameter to indicate if the mode is changeable on a port pin during runtime. True: Port Pin
 *  mode changeable allowed. False: Port Pin mode changeable not permitted.
 */
	boolean PortPinModeChangeable ;
} Port_PinType ;

/* Container collecting the PortPins. */
typedef struct
{
	Port_PinType* PortPin ;
/* The number of specified PortPins in this PortContainer. */
	uint16 PortNumberOfPortPins ;
} Port_ContainerType ;

/* This container is the base of a multiple configuration set */
typedef struct
{
	Port_ContainerType* PortContainer ;
} Port_ConfigSetType ;

/* Module wide configuration parameters of the PORT driver. */
typedef struct
{
/* true: Enabled.
                                        false: Disabled. */
/* Switches the Development Error Detection and Notification on or off. */
	boolean PortDevErrorDetect ;
/* TRUE: Enabled - Function Port_SetPinDirection() is available.
 *                                         FALSE: Disabled - Function Port_SetPinDirection() is
 *  not available.
 */
/* Pre-processor switch to enable / disable the use of the function Port_SetPinDirection(). */
	boolean PortSetPinDirectionApi ;
/* true: Enabled - Function Port_SetPinMode() is available.
 *                                         false: Disabled - Function Port_SetPinMode() is not
 *  available.
 */
/* Pre-processor switch to enable / disable the use of the function Port_SetPinMode(). */
	boolean PortSetPinModeApi ;
/* true: Version info API enabled.
 *                                         false: Version info API disabled.
 */
/* Pre-processor switch to enable / disable the API to read out the modules version information. */
	boolean PortVersionInfoApi ;
} Port_GeneralType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif /* PORT_TYPES_H */

