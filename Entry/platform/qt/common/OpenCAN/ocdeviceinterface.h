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

#ifndef OCDEVICEINTERFACE_H
#define OCDEVICEINTERFACE_H

#include <QObject>

#include "ocdevice.h"
#include "ocplugininfo.h"

/// OpenCAN device plugin interface class.
class OPENCAN_EXPORT OcDeviceInterface
{
public:
	virtual ~OcDeviceInterface() {}

	/// Virtual method for retrieving a plugin's device type string
	virtual QString type() const = 0;

	/// Get the OcPluginInfo for this plugin
	virtual OcPluginInfo *info() const = 0;

	/// Discover devices
	virtual void discoverDevices() = 0;

	/// Get the list of discovered devices
	virtual OcDeviceList getDevices() = 0;

	/// Virtual method for retrieving a plugin's CAN device
	/// @param device the device name
	virtual OcDevice* getCanDevice(const QString &device) const = 0;
};

Q_DECLARE_INTERFACE(OcDeviceInterface,
					 "com.codeofintelligence.OpenCAN.OcDeviceInterface/0.7")

#endif // OCDEVICEINTERFACE_H
