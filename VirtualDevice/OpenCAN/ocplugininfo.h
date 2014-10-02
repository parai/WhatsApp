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

#ifndef OCPLUGININFO_H
#define OCPLUGININFO_H

#include "occore.h"

#include <QStringList>

/// OpenCAN plugin information

/// Only name() and version() are guaranteed to be non-empty
class OPENCAN_EXPORT OcPluginInfo
{
public:
	OcPluginInfo() : devStatus(OcFail) {}
	OcPluginInfo(const QString &name, const QString &type,
				 const QString &version, OcStatus status)
		: devName(name), devType(type), pluginVersion(version), devStatus(status) {}

	/// The name of the OpenCAN driver
	inline QString name() const { return devName; }

	/// OpenCAN device type string
	/// The type string is used to get devices from the OcDeviceManager
	/// using OcDeviceManager::getDevice()
	inline QString type() const { return devType; }

	/// The version of the OpenCAN driver
	inline QString version() const { return pluginVersion; }

	/// The filename of the OpenCAN plugin
	/// @returns the filename otherwise an empty string if the plugin is statically linked
	inline QString fileName() const { return file; }

	/// Get the status of the plugin
	/// @returns OcSuccess if the plugin was loaded successfully, otherwise OcFail
	inline OcStatus status() const { return devStatus; }

	/// The person or organization who created the OpenCAN driver
	inline QString vendor() const { return pluginVendor; }

	/// The person or organization who created the device
	inline QString deviceVendor() const { return devVendor; }

	/// The version of the device hardware
	inline QString deviceVersion() const { return devVersion; }

	/// Device hardware description
	inline QString deviceDescription() const { return devDesc; }

	/// The hardware device driver version
	inline QString deviceDriverVersion() const { return devDrvVersion; }

	/// The person or organization who created the hardware device driver
	inline QString deviceDriverVendor() const { return devDrvVendor; }

	/// OpenCAN driver copyright
	inline QString copyright() const { return copy; }

	/// OpenCAN driver license
	inline QString license() const { return lic; }

	/// Any OpenCAN driver dependencies as a list
	inline QStringList dependencies() const { return deps; }

	/// Set the plugin's file name
	/// Note: The file name should be empty if statically linked
	inline void setFileName(const QString &fileName) { file = fileName; }

	/// Set the name of the person or organization who created the OpenCAN driver
	inline void setVendor(const QString &vendor) { pluginVendor = vendor; }

	/// Set the name of the person or organization who created the device
	inline void setDeviceVendor(const QString &vendor) { devVendor = vendor; }

	/// Set the version of the device hardware
	inline void setDeviceVersion(const QString &version) { devVersion = version; }

	/// Set the description of the device hardware
	inline void setDeviceDescription(const QString &description) { devDesc = description; }

	/// Set the version of the hardware device driver
	inline void setDeviceDriverVersion(const QString &version) { devDrvVersion = version; }

	/// Set the name of the person or organization who create the hardware device driver
	inline void setDeviceDriverVendor(const QString &vendor) { devDrvVendor = vendor; }

	/// Set the OpenCAN driver copyright
	inline void setCopyright(const QString &copyright) { copy = copyright; }

	/// Set the OpenCAN driver license
	inline void setLicense(const QString &license) { lic = license; }

	/// Add a dependency to the list of dependencies
	inline void addDependency(const QString &dependency) { deps.append(dependency); }

	/// Remove a dependency from the list of dependencies
	inline void removeDependency(int index) { deps.removeAt(index); }

	/// Set the list of dependencies
	inline void setDependencies(const QStringList &dependencies) { deps = dependencies; }
	// TODO: Should be able to set a range of compatible/dependent versions with optional end

private:
	QString devName, devType, pluginVersion, file, pluginVendor, devVendor,
			devVersion, devDesc, devDrvVersion, devDrvVendor, copy, lic;
	QStringList deps;
	OcStatus devStatus;
};

#endif // OCPLUGININFO_H
