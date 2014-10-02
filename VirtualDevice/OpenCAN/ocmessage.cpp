/******************************************************************************
**
**  Copyright (C) 2005-2011 Code of Intelligence, LLC.
**  All rights reserved.
**  Contact: opensource@codeofintelligence.com
**
**  Author(s): Mark Lenz
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Lesser General Public
**  License as published by the Free Software Foundation; either
**  version 2.1 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License along with this library; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
******************************************************************************/

#include "ocmessage.h"

/// Create an empty CAN message.
/// The length of the message data is set to 0.
/// @param extended true if the message uses extended CAN
OcMessage::OcMessage(bool extended)
{
	msgId = 0;
	dataLen = 0;
	canExt = extended;
	time = 0;
	for (int x = 0; x < MAX_MESSAGE_LENGTH; ++x)
		msgData[x] = 0;
}

/// Create a CAN message with data given by an array of 8 bytes.
/// Test.
/// @param id the message identifier
/// @param data an array of 8 bytes containing the message data
/// @param length the length of the message's data
/// @param extended true if the message uses extended CAN
OcMessage::OcMessage(quint32 id, quint8 data[MAX_MESSAGE_LENGTH], int length, bool extended, quint32 timestamp)
{
	msgId = id;
	dataLen = length;
	canExt = extended;
	time = timestamp;
	for (int x = 0; x < length; ++x)
		msgData[x] = data[x];
}

/// Create a CAN message with data given 8 separate bytes.
/// @param id the message identifier
/// @param byte1 the first data byte
/// @param byte2 the second data byte
/// @param byte3 the third data byte
/// @param byte4 the fourth data byte
/// @param byte5 the fifth data byte
/// @param byte6 the sixth data byte
/// @param byte7 the seventh data byte
/// @param byte8 the eighth data byte
/// @param extended true if the message uses extended CAN
OcMessage::OcMessage(quint32 id, quint8 byte1, quint8 byte2, quint8 byte3,
					 quint8 byte4, quint8 byte5, quint8 byte6, quint8 byte7,
					 quint8 byte8, int length, bool extended, quint32 timestamp)
{
	msgId = id;
	canExt = extended;
	time = timestamp;
	dataLen = length;
	msgData[0] = byte1;
	msgData[1] = byte2;
	msgData[2] = byte3;
	msgData[3] = byte4;
	msgData[4] = byte5;
	msgData[5] = byte6;
	msgData[6] = byte7;
	msgData[7] = byte8;
}
