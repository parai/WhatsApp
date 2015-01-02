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

#ifndef OCMESSAGE_H
#define OCMESSAGE_H

#include "occore.h"

#define MAX_MESSAGE_LENGTH 8

/// Encapsulates a CAN message.
class OPENCAN_EXPORT OcMessage
{
public:
	OcMessage(bool extended = true);
	OcMessage(quint32 id, quint8 data[MAX_MESSAGE_LENGTH],
			  int length = MAX_MESSAGE_LENGTH, bool extended = true, quint32 timestamp = 0);
	OcMessage(quint32 id, quint8 byte0 = 0, quint8 byte1 = 0, quint8 byte2 = 0,
			  quint8 byte3 = 0, quint8 byte4 = 0, quint8 byte5 = 0,
			  quint8 byte6 = 0, quint8 byte7 = 0,
			  int length = MAX_MESSAGE_LENGTH, bool extended = true, quint32 timestamp = 0);
	/// Copy constructor
	OcMessage(const OcMessage &msg)
	{
		msgId = msg.msgId;
		canExt = msg.canExt;
		dataLen = msg.dataLen;
		for (int x = 0; x < MAX_MESSAGE_LENGTH; ++x)
			msgData[x] = msg.msgData[x];
	}

	quint32 id() const;
	bool extended() const;
	quint32 timestamp() const;
	int length() const;
	quint8 byte1() const;
	quint8 byte2() const;
	quint8 byte3() const;
	quint8 byte4() const;
	quint8 byte5() const;
	quint8 byte6() const;
	quint8 byte7() const;
	quint8 byte8() const;
	const quint8* data() const;
	quint8* data();

	void setExtended(bool extended);
	void setId(quint32 id);
	void setTimestamp(quint32 timestamp);
	void setData(quint8 data[MAX_MESSAGE_LENGTH], int length = MAX_MESSAGE_LENGTH);

	bool operator==(const OcMessage &m) const;
    void operator=(const OcMessage &m);

    void setBusId(quint32 busid);
    quint32 busid(void);

    void setSWHandle(quint32);
    quint32 SWHandle(void);

protected:
	/// CAN message identifier
	quint32 msgId;
	/// CAN message data
	quint8 msgData[MAX_MESSAGE_LENGTH];
	/// Length of CAN message data
	int dataLen;
	/// Boolean value for whether message follows CAN 2.0b extended
	bool canExt;
	/// Timestamp
	quint32 time;
    quint32 busId;    // externded by parai
    quint32 swHandle; // externded by parai
};

// Inline Methods

/// Get the message identifier
inline quint32 OcMessage::id() const { return msgId; }

/// Get whether the message follows CAN 2.0b extended
inline bool OcMessage::extended() const { return canExt; }

inline quint32 OcMessage::timestamp() const { return time; }

/// Get the length of the message's data in bytes
inline int OcMessage::length() const { return dataLen; }

/// Get the first data byte
inline quint8 OcMessage::byte1() const { return msgData[0]; }

/// Get the second data byte
inline quint8 OcMessage::byte2() const { return msgData[1]; }

/// Get the third data byte
inline quint8 OcMessage::byte3() const { return msgData[2]; }

/// Get the fourth data byte
inline quint8 OcMessage::byte4() const { return msgData[3]; }

/// Get the fifth data byte
inline quint8 OcMessage::byte5() const { return msgData[4]; }

/// Get the sixth data byte
inline quint8 OcMessage::byte6() const { return msgData[5]; }

/// Get the seventh data byte
inline quint8 OcMessage::byte7() const { return msgData[6]; }

/// Get the eighth data byte
inline quint8 OcMessage::byte8() const { return msgData[7]; }

/// Get a const pointer to the data array
inline const quint8* OcMessage::data() const { return msgData; }

/// Get a pointer to the data array
inline quint8* OcMessage::data() { return msgData; }

/// Set the message identifier
/// @param id the message identifier
inline void OcMessage::setId(quint32 id) { msgId = id; }

/// Set whether the message follows CAN 2.0b extended
/// @param extended true if the message follows CAN 2.0b extended
inline void OcMessage::setExtended(bool extended) { canExt = extended; }

/// Set the message's timestamp in milliseconds
/// @param timestamp the timestamp in milliseconds
inline void OcMessage::setTimestamp(quint32 timestamp) { time = timestamp; }

/// Set the message data
/// @param data the message data
/// @param length the length of the data in bytes
inline void OcMessage::setData(quint8 data[MAX_MESSAGE_LENGTH], int length)
{
	dataLen = length;
	for (int x = 0; x < length; ++x)
		msgData[x] = data[x];
}

/// Verify if two messages contain the same content.
/// Compares message identifier, data, data length, and extended status.
/// @param m the message to compare this message to
/// @returns true if the two messages match
inline bool OcMessage::operator==(const OcMessage &m) const
{
	return (canExt == m.canExt && msgId == m.msgId && dataLen == m.dataLen &&
		msgData[0] == m.msgData[0] && msgData[1] == msgData[1] && msgData[2] == m.msgData[2] &&
		msgData[3] == m.msgData[3] && msgData[4] == m.msgData[4] && msgData[5] == m.msgData[5] &&
		msgData[6] == m.msgData[6] && msgData[7] == m.msgData[7]);
}
inline void OcMessage::operator=(const OcMessage &m)
{
    canExt = m.canExt;
    msgId = m.msgId ;
    dataLen = m.dataLen ;
    time = m.time;
    busId = m.busId;
    for (int x = 0; x < MAX_MESSAGE_LENGTH; ++x)
    {
        msgData[x] = m.msgData[x];
    }
}

inline void OcMessage::setBusId(quint32 busid)
{
    busId = busid;
}

inline quint32 OcMessage::busid(void)
{
    return busId;
}

inline void OcMessage::setSWHandle(quint32 handle)
{
    swHandle = handle;
}

inline quint32 OcMessage::SWHandle(void)
{
    return swHandle;
}


#endif // OCMESSAGE_H
