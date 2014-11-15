# Qt QMake Project file for OpenCAN library
QT += core
TARGET = OpenCAN
TEMPLATE = lib
CONFIG += shared
DEFINES += OPENCAN_LIBRARY QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS
win32:DEFINES += _BIND_TO_CURRENT_CRT_VERSION
HEADERS += ocdevicemanager.h \
    ocdevice.h \
    ocmessage.h \
    ocdeviceinterface.h \
    occore.h \
    ocplugininfo.h
SOURCES += ocdevicemanager.cpp \
    ocdevice.cpp \
    ocmessage.cpp
OTHER_FILES += README
DESTDIR = ../OpenCAN
