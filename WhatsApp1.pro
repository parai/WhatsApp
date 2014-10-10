#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T10:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsApp
TEMPLATE = app

DEFINES = USE_KERNEL1 USE_OPENCAN_DIRECTLY


SOURCES += main.cpp \
    entry.cpp \
    Entry/system/EcuM.c \
    Entry/system/SchM.c \
    VirtualDevice/virtualdevice.cpp \
    VirtualDevice/virtualcan.cpp \
    Entry/system/kernel1/config/os_cfg.c \
    Entry/system/kernel1/alarm.c \
    Entry/system/kernel1/bitop.c \
    Entry/system/kernel1/event.c \
    Entry/system/kernel1/resource.c \
    Entry/system/kernel1/task.c \
    VirtualDevice/OpenCAN/ocdevice.cpp \
    VirtualDevice/OpenCAN/ocdevicemanager.cpp \
    VirtualDevice/OpenCAN/ocmessage.cpp \
    VirtualDevice/MCAL/config/Can_Cfg.c \
    VirtualDevice/MCAL/Can.cpp \
    Entry/communication/CanIf.c \
    Entry/communication/config/CanIf_Cfg.c \
    Entry/diagnostic/Det.c

HEADERS  += \
    entry.h \
    Entry/include/Os.h \
    Entry/include/Std_Types.h \
    Entry/include/Compiler.h \
    Entry/include/EcuM.h \
    Entry/include/SchM.h \
    VirtualDevice/virtualdevice.h \
    VirtualDevice/virtualcan.h \
    Entry/system/kernel1/config/os_cfg.h \
    Entry/system/kernel1/os_i.h \
    VirtualDevice/MCAL/config/Can_Cfg.h \
    VirtualDevice/OpenCAN/occore.h \
    VirtualDevice/OpenCAN/ocdevice.h \
    VirtualDevice/OpenCAN/ocdeviceinterface.h \
    VirtualDevice/OpenCAN/ocdevicemanager.h \
    VirtualDevice/OpenCAN/ocmessage.h \
    VirtualDevice/OpenCAN/ocplugininfo.h \
    Entry/include/Can.h \
    Entry/include/CanIf.h \
    Entry/include/ComStack_Types.h \
    Entry/include/Modules.h \
    Entry/communication/config/CanIf_Cfg.h

FORMS    +=

INCLUDEPATH += VirtualDevice
INCLUDEPATH += Entry
INCLUDEPATH += Entry/include
INCLUDEPATH += Entry/system/kernel1
INCLUDEPATH += Entry/system/kernel1
INCLUDEPATH += Entry/system/kernel1/config
INCLUDEPATH += Application/Configuration
INCLUDEPATH += VirtualDevice/OpenCAN
INCLUDEPATH += VirtualDevice/MCAL/config    \
               Entry/communication/config

RESOURCES += \
    WhatsApp.qrc

