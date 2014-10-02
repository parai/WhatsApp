#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T10:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsApp
TEMPLATE = app

DEFINES = USE_KERNEL1


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
    Entry/system/kernel1/task.c

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
    Entry/system/kernel1/os_i.h

FORMS    +=

INCLUDEPATH += VirtualDevice
INCLUDEPATH += Entry
INCLUDEPATH += Entry/include
INCLUDEPATH += Entry/system/kernel1
INCLUDEPATH += Entry/system/kernel1
INCLUDEPATH += Entry/system/kernel1/config
INCLUDEPATH += Application/Configuration

RESOURCES += \
    WhatsApp.qrc

