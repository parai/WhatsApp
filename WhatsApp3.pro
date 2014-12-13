#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T10:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsApp
TEMPLATE = app

DEFINES = USE_KERNEL3 USE_OPENCAN_DIRECTLY


SOURCES +=              \
    Entry/system/EcuM.c \
    Entry/system/SchM.c \
    Entry/platform/qt/kernel3/config/os_cfg.c \
    Entry/platform/qt/kernel3/alarm.cpp \
    Entry/platform/qt/kernel3/event.cpp \
    Entry/platform/qt/kernel3/resource.cpp \
    Entry/platform/qt/kernel3/task.cpp \
    Entry/communication/CanIf.c \
    Entry/communication/config/CanIf_Cfg.c \
    Entry/diagnostic/Det.c \
    Entry/platform/qt/simul/MCAL/Can/Can.cpp \
    Entry/platform/qt/simul/arcan.cpp \
    Entry/platform/qt/entry.cpp \
    Entry/platform/qt/main.cpp \
    Entry/platform/qt/simul/MCAL/Can/config/Can_Cfg.c \
    Entry/platform/qt/common/OpenCAN/ocdevice.cpp \
    Entry/platform/qt/common/OpenCAN/ocdevicemanager.cpp \
    Entry/platform/qt/common/OpenCAN/ocmessage.cpp \
    Entry/platform/qt/common/ardevice.cpp \
    Entry/rte/Rte.c

HEADERS  +=             \
    Entry/include/Os.h \
    Entry/include/Std_Types.h \
    Entry/include/Compiler.h \
    Entry/include/EcuM.h \
    Entry/include/SchM.h \
    Entry/platform/qt/kernel3/config/os_cfg.h \
    Entry/platform/qt/kernel3/os_i.h \
    Entry/include/Can.h \
    Entry/include/CanIf.h \
    Entry/include/ComStack_Types.h \
    Entry/include/Modules.h \
    Entry/communication/config/CanIf_Cfg.h \
    Entry/platform/qt/simul/MCAL/Can/config/Can_Cfg.h \
    Entry/platform/qt/simul/arcan.h \
    Entry/platform/qt/entry.h \
    Entry/platform/qt/common/OpenCAN/occore.h \
    Entry/platform/qt/common/OpenCAN/ocdevice.h \
    Entry/platform/qt/common/OpenCAN/ocdeviceinterface.h \
    Entry/platform/qt/common/OpenCAN/ocdevicemanager.h \
    Entry/platform/qt/common/OpenCAN/ocmessage.h \
    Entry/platform/qt/common/OpenCAN/ocplugininfo.h \
    Entry/platform/qt/common/ardevice.h \
    Entry/include/CanTp.h \
    Entry/include/Det.h \
    Entry/platform/qt/kernel3/task.h \
    Entry/include/Rte.h

FORMS    +=

INCLUDEPATH += Application/Configuration
INCLUDEPATH += Entry
INCLUDEPATH += Entry/include Entry/include/types
INCLUDEPATH += Entry/platform/qt/kernel3
INCLUDEPATH += Entry/platform/qt/kernel3/config
INCLUDEPATH += Entry/communication/config   \
               Entry/platform/qt/simul/MCAL/Can \
               Entry/platform/qt/simul/MCAL/Can/config  \
               Entry/platform/qt/simul  \
               Entry/platform/qt        \
               Entry/platform/qt/common/OpenCAN \
               Entry/platform/qt/common

RESOURCES += \
    WhatsApp.qrc

