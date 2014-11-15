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

#include "ocdevice.h"

static const int TIMER_MSECS = 1;

/// Create a CAN device
/// @param deviceName the device name
/// For Linux, this is the device number: e.g. "0" for /dev/can0
OcDevice::OcDevice(const QString id)
{
	devId = id;
	auton = false;
	started = false;
	rxIndx = 0;
	timerId = 0;
	prevTimestamp = 0;
	extendedCAN = true;

	bauds.append(OcBaud_1M);	//   1 MBit/s
	bauds.append(OcBaud_500K);	// 500 kBit/s
	bauds.append(OcBaud_250K);	// 250 kBit/s
	bauds.append(OcBaud_125K);	// 125 kBit/s
	bauds.append(OcBaud_100K);	// 100 kBit/s
	bauds.append(OcBaud_50K);	//  50 kBit/s
	bauds.append(OcBaud_20K);	//  20 kBit/s
	bauds.append(OcBaud_10K);	//  10 kBit/s
	bauds.append(OcBaud_5K);	//   5 kBit/s
}

/// OcDevice destructor
OcDevice::~OcDevice()
{
	while (!rxBuffer.isEmpty())
	{
		delete rxBuffer.at(rxBuffer.size() - 1);
		rxBuffer.removeLast();
	}
}

/// Set the device to run autonomously.
/// @param autonomous true to run autonomously
/// @param bufferSize the size of the receive buffer in messages
/// Set this before starting the device.
/// @returns nothing
void OcDevice::setAutonomous(bool autonomous, int bufferSize)
{
	while (rxBuffer.size() > bufferSize)
	{
		delete rxBuffer.at(rxBuffer.size() - 1);
		rxBuffer.removeLast();
	}
	while (rxBuffer.size() < bufferSize)
		rxBuffer.append(new OcMessage());
	auton = autonomous;
}

/// Initialize the device.
/// Implement this method in device-specific subclasses and then call this
/// method, returning its value. This method starts the autonomous process.
/// @returns OcSuccess if the device wasn't already initialized and was then properly
/// initialized
OcStatus OcDevice::startup()
{
	if (started && auton)
	{
		rxIndx = 0;
		timerId = startTimer(TIMER_MSECS);
	}
	return OcSuccess;
}

/// Uninitialize the device.
/// Implement this method in device-specific subclasses and then call this
/// method, returning its value. This method stops the autonomous process.
/// @returns OcSuccess if was initialized and then properly uninitialized
OcStatus OcDevice::shutdown()
{
	if (auton)
	{
		killTimer(timerId);
	}
	return OcSuccess;
}

/// Get a received message.
/// The caller must delete the returned OcMessage if it is not NULL.
/// @returns the received message or NULL if none was received
OcMessage* OcDevice::getMessage()
{
	if (!isStarted())
		return NULL;

	OcMessage *msg = new OcMessage();
	if (internalGetMessage(msg))
		return msg;
	else
		delete msg;
	return NULL;
}

void OcDevice::timerEvent(QTimerEvent *)
{
    if (started)
	{
		while (receivedMessage())
		{
			OcMessage *msg = rxBuffer.at(rxIndx);
			if (internalGetMessage(msg))
			{
				if (prevTime.isNull())
					prevTime = prevTime.currentTime();
				else
				{
					if (msg->timestamp() < prevTimestamp)
						// timestamp rolled over
						prevTime = prevTime.addMSecs((sizeof(prevTimestamp) * 255) - prevTimestamp + msg->timestamp());
					else
						prevTime = prevTime.addMSecs(msg->timestamp() - prevTimestamp);
				}
				prevTimestamp = msg->timestamp();

				emit messageReceived(msg, prevTime);

				rxIndx = (rxIndx + 1) % rxBuffer.size();
			}

		}
	}
}
