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

#ifndef OCCORE_H
#define OCCORE_H

/**		\mainpage

  \section Introduction

  The following is documentation for compiling, installing and using OpenCAN.

  \section Compiling

  OpenCAN is distributed with four projects, each with their own QMake \a .pro file.
  <table>
  <tr><td>OpenCAN.pro</td><td>OpenCAN library</tr>
  <tr><td>ocplugins/LinCAN.pro</td><td>LinCAN device plugin <em>(Linux only)</em></tr>
  <tr><td>ocplugins/PCAN.pro</td><td>PCAN device plugin <em>(Windows and Linux)</em></tr>
  <tr><td>Testbench/Testbench.pro</td><td>Testbench application</tr>
  </table>
  Only the OpenCAN library must be compiled using the OpenCAN.pro project file,
  and it must be compiled first.
  The other projects are optional.

  OpenCAN has been tested on Windows, Linux and Mac OS X. You can use Qt Creator to compile
  and debug each project by opening the project's .pro file, or you can follow the
  platform-specific compilation instructions.
  - \subpage compilewin
  - \subpage compilelin
  - \subpage compilemac

  \section Installing

  Currently, there is no installation method. Simply copy the compiled files to
  the desired location or leave them where they are.

  \section Using

  To use the OpenCAN API you must add the directory to your include and library
  paths. The Testbench QMake .pro file can be a useful example.

  To use OpenCAN Testbench simply run the executable. Testbench does very little
  without a supported CAN device installed and connected.

  \section Troubleshooting

  \subsection Loading Plugins

  If you are having trouble loading the PCAN plugin in Windows, you may need to
  copy the PCAN_USB.dll from the PEAK software into the OpenCAN folder with
  testbench.exe.

  Other reasons for a plugin not loading is if the plugin is built with a different
  version of Qt than the Qt used to build OpenCAN, or if the plugin is not built with the
  installed version of OpenCAN loaded at runtime.
**/

/** \page compilewin Compile for Windows
  \section vs Compile using Visual Studio
  You must have the Qt library built for Visual Studio installed before compiling
  and QTDIR\bin must be in your PATH. This is done for you if you use the Qt
  installer.

  Nokia currently does not distribute a 64-bit build of Qt for Windows. So if you
  want to develop 64-bit software on Windows using OpenCAN, you must build Qt
  yourself.
  - Open the Visual Studio Command Prompt <em>(x64 if 64-bit is desired)</em>
  - Change to the directory containing the QMake file for the project to compile.
  - Execute <em>qmake -tp vc</em> to create the Visual Studio project file
  - Open the created VS project file to compile and debug

  You may also be able to use the Qt Visual Studio Add-In, but I have not.

  \section MinGW Compile using mingw
  You must have the Qt library built for MinGW installed before compiling.
  - Open a Command Prompt
  - Change to the directory containing the QMake file for the project to compile.
  - Execute \a qmake to create the gmake Makefile
  - Execute \a mingw32-make
**/

/** \page compilelin Compile for Linux
  - Change to the directory containing the QMake file for the project to compile.
  - Execute \a qmake, or \a qmake-qt4 on Fedora, to create the gmake Makefile.
  - Execute \a make to build the project
**/

/** \page compilemac Compile for Mac OS X
  - Change to the directory containing the QMake file for the project to compile.
  - Execute \a qmake to create the XCode project.
  - Open the created XCode project to compile and debug
**/

#include <QtCore/QtGlobal>

#if defined(Q_WS_WIN) && defined(Q_CC_MINGW)
	#if defined(OPENCAN_LIBRARY)
		#define OPENCAN_EXPORT __attribute__((visibility("default")))
	#else
		#define OPENCAN_EXPORT
	#endif
#else
	#if defined(OPENCAN_LIBRARY)
		#define OPENCAN_EXPORT Q_DECL_EXPORT
	#else
        #if defined(USE_OPENCAN_DIRECTLY)
            #define OPENCAN_EXPORT
        #else
            #define OPENCAN_EXPORT  Q_DECL_IMPORT
        #endif
	#endif
#endif

typedef enum {
	OcFail,
	OcSuccess,
	OcNA
} OPENCAN_EXPORT OcStatus;

typedef enum {
	OcBaud_1M =    1000000,  //   1 MBit/s
	OcBaud_500K =  500000,  // 500 kBit/s
	OcBaud_250K =  250000,  // 250 kBit/s
	OcBaud_125K =  125000,  // 125 kBit/s
	OcBaud_100K =  100000,  // 100 kBit/s
	OcBaud_50K  =  50000,  //  50 kBit/s
	OcBaud_20K  =  20000,  //  20 kBit/s
	OcBaud_10K  =  10000,  //  10 kBit/s
	OcBaud_5K   =  5000,  //   5 kBit/s
} OPENCAN_EXPORT OcBaud;

extern OPENCAN_EXPORT QString OpenCAN_Version();
extern OPENCAN_EXPORT QString OpenCAN_About();

#endif // OCCORE_H
