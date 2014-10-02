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

#ifndef OCDEVICEMANAGER_H
#define OCDEVICEMANAGER_H

#include <QList>
#include <QHash>

#include "ocdeviceinterface.h"

typedef QList<OcPluginInfo *> OcPluginInfoList;

/// Manages all CAN devices and plugins.
class OPENCAN_EXPORT OcDeviceManager
{
public:
	OcDeviceManager();
	virtual ~OcDeviceManager();

	static QString version();

	void loadPlugins();
	OcPluginInfoList getPluginInfos() const;
	OcDeviceList getDevices() const;

	OcDevice* getDevice(const QString &type, const QString &device);

private:
	void loadDeviceInterface(OcDeviceInterface *interface, const QString &fileName = "");

	QHash<QString, OcDeviceInterface *> plugins;
	OcPluginInfoList pluginInfos;
	OcDeviceList devices;
};

/// Get the OcPluginInfo for each plugin file installed
inline OcPluginInfoList OcDeviceManager::getPluginInfos() const
{
	return pluginInfos;
}

/// Get the OcDeviceInfo for each plugin file installed
inline OcDeviceList OcDeviceManager::getDevices() const
{
	return devices;
}

#endif // OCDEVICEMANAGER_H
