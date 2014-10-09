#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T10:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsApp
TEMPLATE = app

DEFINES = USE_KERNEL2 USE_OPENCAN_DIRECTLY

SOURCES += main.cpp \
    entry.cpp \
    Entry/system/EcuM.c \
    Entry/system/SchM.c \
    VirtualDevice/virtualdevice.cpp \
    VirtualDevice/virtualcan.cpp \
    Entry/system/kernel2/portable/qt/portable.cpp \
    Entry/system/kernel2/portable/qt/rtetask.cpp \
    Entry/system/kernel2/config/os_cfg.c \
    Entry/system/kernel2/alarm.c \
    Entry/system/kernel2/event.c \
    Entry/system/kernel2/interrupt.c \
    Entry/system/kernel2/osctl.c \
    Entry/system/kernel2/resource.c \
    Entry/system/kernel2/task.c \
    Entry/system/kernel2/task_manage.c \
    VirtualDevice/OpenCAN/ocdevice.cpp \
    VirtualDevice/OpenCAN/ocdevicemanager.cpp \
    VirtualDevice/OpenCAN/ocmessage.cpp \
    VirtualDevice/MCAL/config/Can_Cfg.c \
    Entry/communication/config/CanIf_Cfg.c \
    Entry/communication/CanIf.c \
    VirtualDevice/MCAL/Can.cpp

HEADERS  += \
    entry.h \
    Entry/include/Os.h \
    Entry/include/Std_Types.h \
    Entry/include/Compiler.h \
    Entry/include/EcuM.h \
    Entry/include/SchM.h \
    VirtualDevice/virtualdevice.h \
    VirtualDevice/virtualcan.h \
    Entry/system/kernel2/config/os_cfg.h \
    Entry/system/kernel2/portable/qt/portable.h \
    Entry/system/kernel2/portable/qt/rtetask.h \
    Entry/system/kernel2/alarm.h \
    Entry/system/kernel2/check.h \
    Entry/system/kernel2/interrupt.h \
    Entry/system/kernel2/os_i.h \
    Entry/system/kernel2/osek_kernel.h \
    Entry/system/kernel2/oslog.h \
    Entry/system/kernel2/resource.h \
    Entry/system/kernel2/task.h \
    VirtualDevice/OpenCAN/occore.h \
    VirtualDevice/OpenCAN/ocdevice.h \
    VirtualDevice/OpenCAN/ocdeviceinterface.h \
    VirtualDevice/OpenCAN/ocdevicemanager.h \
    VirtualDevice/OpenCAN/ocmessage.h \
    VirtualDevice/OpenCAN/ocplugininfo.h \
    Entry/include/Modules.h \
    Entry/include/Can.h \
    Entry/include/ComStack_Types.h \
    VirtualDevice/MCAL/config/Can_Cfg.h \
    Entry/communication/config/CanIf_Cfg.h \
    Entry/include/CanIf.h \
    Entry/include/CanTp.h

FORMS    +=

INCLUDEPATH += VirtualDevice
INCLUDEPATH += VirtualDevice/OpenCAN
INCLUDEPATH += Entry
INCLUDEPATH += Entry/include
INCLUDEPATH += Entry/system/kernel2/portable/qt
INCLUDEPATH += Entry/system/kernel2
INCLUDEPATH += Entry/system/kernel2/config
INCLUDEPATH += Application/Configuration
INCLUDEPATH += Entry/communication/config
INCLUDEPATH += VirtualDevice/MCAL/config/

RESOURCES += \
    WhatsApp.qrc

