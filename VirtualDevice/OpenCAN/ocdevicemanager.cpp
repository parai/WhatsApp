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

#include "ocdevicemanager.h"

#include <QtCore>

static const QString OPENCAN_VERSION = "0.7";

static const QString MAC_DIR_NAME = "MacOS";
static const QString PLUGINS_DIR = "ocplugins";

#if defined(Q_OS_WIN)
	static const QString PLUGIN_EXT = "*.dll";
#else
	static const QString PLUGIN_EXT = "*.so";
#endif

QString OpenCAN_Version()
{
	return OPENCAN_VERSION;
}

QString OpenCAN_About()
{
	return QObject::tr("<p><h3>About OpenCAN</h3>") +
		QObject::tr("Testbench is using OpenCAN version ") + OpenCAN_Version() + ".</p>" +
		QObject::tr("<p>OpenCAN is a software platform for interacting with various Controller Area Network (CAN) devices.</p>") +
		QObject::tr("<p>OpenCAN provides an abstract C++ interface that can be used to control any CAN device, and each component is cross-platform, enabling the efficient development of CAN software on Windows, Linux and Mac OS X.</p>") +
		QObject::tr("<p>You are free to use and extend OpenCAN according to the GNU Lesser General Public License (LGPL) version 2.1.</p>") +
		QObject::tr("OpenCAN is a Code of Intelligence product. For more information visit <a href=\"http://www.codeofintelligence.com/opensource/opencan\">www.codeofintelligence.com/opensource/opencan</a>.") +
		QString::fromUtf8("<center><p style=\"font-size: small\">Copyright © 2005-2011 Code of Intelligence, LLC.") +
		QObject::tr(" All rights reserved.</p></center>");
}

OcDeviceManager::OcDeviceManager()
{
    //printf(QString("OpenCAN version " + OPENCAN_VERSION + "\n").toAscii().constData());
    printf((const char*)QString("OpenCAN version " + OPENCAN_VERSION + "\n").constData());
}

OcDeviceManager::~OcDeviceManager()
{
	foreach(OcPluginInfo *info, pluginInfos)
	{
		if (info->status() == OcFail)	// no plugin loaded
			delete info;
	}
}

/// Get the current linked version of OpenCAN
/// @returns the version as a QString
QString OcDeviceManager::version()
{
	return OPENCAN_VERSION;
}

/// Load static and dynamically-loaded CAN device plugins
/// Looks in the ocplugins directory in the application's working directory
void OcDeviceManager::loadPlugins()
{
	printf("Loading OpenCAN device plugins\n");

	// static plugins
	foreach (QObject *plugin, QPluginLoader::staticInstances())
		loadDeviceInterface(qobject_cast<OcDeviceInterface *>(plugin));

	// dynamically-loaded plugins
	QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
	//if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
	//	pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
	if (pluginsDir.dirName() == MAC_DIR_NAME)
	{
		pluginsDir.cdUp();
		pluginsDir.cdUp();
		pluginsDir.cdUp();
	}
#endif
	pluginsDir.cd(PLUGINS_DIR);
	foreach (QString fileName, pluginsDir.entryList(QStringList() << PLUGIN_EXT))
	{
		QString fp = pluginsDir.absoluteFilePath(fileName) + "\n";
        printf((const char*)fp/*.toAscii()*/.constData());
		QString filePath = pluginsDir.absoluteFilePath(fileName);
		QPluginLoader loader(filePath);
		QObject *plugin = loader.instance();
		if (plugin)
		{
			loadDeviceInterface(qobject_cast<OcDeviceInterface *>(plugin), filePath);
		}
		else
		{
			fp = loader.errorString() + "\n";
            fprintf(stderr, (const char*)fp/*.toAscii()*/.constData());
			OcPluginInfo *info = new OcPluginInfo();
			info->setFileName(filePath);
			pluginInfos.append(info);
		}
	}
}

/// Get a CAN device
/// @param type the type of CAN device<br/>
/// @param device the name of the device
/// Examples are <em>lincan</em>, etc.
/// An empty string uses the first available type
/// @returns NULL if no device interfaces have been loaded, a device does not
/// exist, or an interface matching type is not loaded.
OcDevice* OcDeviceManager::getDevice(const QString &type, const QString &device)
{
	if (!plugins.empty() && plugins.value(type))
		return plugins[type]->getCanDevice(device);

	return NULL;
}

void OcDeviceManager::loadDeviceInterface(OcDeviceInterface *interface, const QString &fileName)
{
	if (interface)
	{
		plugins[interface->type()] = interface;

		OcPluginInfo *info = interface->info();
		info->setFileName(fileName);
		pluginInfos.append(info);

		interface->discoverDevices();
		devices.append(interface->getDevices());
	}
	else
	{
		fprintf(stderr, "OcDeviceManager::loadDeviceInterface: NULL interface\r\n");
        fprintf(stderr, "Unable to load plugin %s\r\n", (char*)fileName/*.toAscii()*/.constData());
		OcPluginInfo *info = new OcPluginInfo();
		info->setFileName(fileName);
		pluginInfos.append(info);
	}
}
