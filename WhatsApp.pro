#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T10:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsApp
TEMPLATE = app


SOURCES += main.cpp \
    entry.cpp \
    Entry/system/kernel/alarm.c \
    Entry/system/kernel/event.c \
    Entry/system/kernel/task.c \
    Application/Configuration/os_cfg.c \
    Entry/system/EcuM.c \
    Entry/system/SchM.c \
    Entry/system/kernel/resource.c \
    Entry/system/kernel/bitop.c \
    VirtualDevice/virtualdevice.cpp \
    VirtualDevice/virtualcan.cpp

HEADERS  += \
    entry.h \
    Entry/include/Os.h \
    Entry/include/Std_Types.h \
    Entry/include/Compiler.h \
    Entry/system/kernel/os_i.h \
    Application/Configuration/os_cfg.h \
    Entry/include/EcuM.h \
    Entry/include/SchM.h \
    VirtualDevice/virtualdevice.h \
    VirtualDevice/virtualcan.h

FORMS    +=

INCLUDEPATH += VirtualDevice
INCLUDEPATH += Entry
INCLUDEPATH += Entry/include
INCLUDEPATH += Entry/system/kernel
INCLUDEPATH += Application/Configuration

RESOURCES += \
    WhatsApp.qrc

