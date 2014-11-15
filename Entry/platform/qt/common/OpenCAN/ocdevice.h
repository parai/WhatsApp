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

#ifndef OCDEVICE_H
#define OCDEVICE_H

#include <QObject>

#include <QList>
#include <QVarLengthArray>
#include <QTime>

#include "ocmessage.h"

static const int DEFAULT_RX_BUFFER_SIZE = 20;

/// The virtual base class for all CAN devices.

/// This is a virtual class which can only be used with a subclass that includes
/// the CAN device implementation.
class OPENCAN_EXPORT OcDevice : public QObject
{
	Q_OBJECT
public:
	OcDevice(const QString id);
	virtual ~OcDevice();

	/// Get the device's identifier
	/// For Linux, this is the device number: e.g. /dev/can0 would return "0"
	QString id() const { return devId; }

	/// Get the text description of the device
	/// An understandable description of the device
	QString text() const { return devTxt; }

	/// Check if the device is set to run autonomously.
	/// The device will poll the hardware for received messages itself and
	/// emit the messageReceived() signal when a message is received.
	/// @returns true if the device is set to run autonomously
	bool isAutonomous() const { return auton; }
	void setAutonomous(bool autonomous, int bufferSize = DEFAULT_RX_BUFFER_SIZE);

	/// Check if the device has been started
	/// @returns OcSuccess if the device has been started
	inline bool isStarted() const { return started; }

	virtual OcStatus startup();
	virtual OcStatus shutdown();

	/// Send a CAN message
	/// @param msg the message to send
	/// @returns OcSuccess if the message was successfully sent
	virtual OcStatus sendMessage(const OcMessage &msg) = 0;

	/// Check if the device has received a message
	/// @returns OcSuccess if the device has received a message
	virtual OcStatus receivedMessage() = 0;
	OcMessage* getMessage();

	/// Get a list of available baud rates
	/// @returns a list of available baud rates
	QList<int> baudRates() const { return bauds; }

	/// Get the device's current baud rate
	/// @returns the current baud rate
	virtual int getBaudRate() = 0;

	/// Set the device baud rate
	/// @param baud the baud rate in bits per second
	/// @returns OcSuccess if successful
	virtual OcStatus setBaudRate(int baud) = 0;

	/// Query CAN 2.0b extended frame configuration
	/// @returns true if device is configured for CAN 2.0b extended
	inline bool isExtended() { return extendedCAN; }

	/// Set CAN 2.0b extended (29-bit) or standard (11-bit) frame
	/// @param extended set true to configure device for CAN 2.0b extended frame
	/// @returns nothing
	inline void setExtended(bool extended) { extendedCAN = extended; }

signals:
	/// This signal is emitted when a message is received if
	/// isAutonomous() is true. The OcMessage should not be deleted.
	/// If isAutonomous() is false, this signal is never emitted.
	void messageReceived(OcMessage *, const QTime &);

protected:
	/// Fill the CAN message with the incoming message
	/// @param msg the message to fill
	/// @returns OcSuccess if the incoming message was successfully retreived
	virtual OcStatus internalGetMessage(OcMessage *msg) = 0;

	/// Set the device's text description
	/// @param deviceText the text to set as the device's description
	/// @returns nothing
	void setDeviceText(const QString &deviceText) { devTxt = deviceText; }

	bool started, auton;

private:
	void timerEvent(QTimerEvent *);

	QString devId, devTxt;
	bool extendedCAN;
	QList<int> bauds;
	QVarLengthArray<OcMessage *> rxBuffer;
	int rxIndx, timerId;
	quint32 prevTimestamp;
	QTime prevTime;
};

typedef QList<OcDevice *> OcDeviceList;

#endif // OCDEVICE_H
