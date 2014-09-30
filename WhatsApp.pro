#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T10:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsApp
TEMPLATE = app

DEFINES =


SOURCES += main.cpp \
    entry.cpp \
    Entry/system/EcuM.c \
    Entry/system/SchM.c \
    VirtualDevice/virtualdevice.cpp \
    VirtualDevice/virtualcan.cpp \
    Entry/system/kernel2/config/os_cfg.c \
    Entry/system/kernel2/alarm.c \
    Entry/system/kernel2/event.c \
    Entry/system/kernel2/interrupt.c \
    Entry/system/kernel2/osctl.c \
    Entry/system/kernel2/resource.c \
    Entry/system/kernel2/task.c \
    Entry/system/kernel2/task_manage.c \
    Entry/system/kernel2/portable/qt/portable.c

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
    Entry/system/kernel2/alarm.h \
    Entry/system/kernel2/check.h \
    Entry/system/kernel2/interrupt.h \
    Entry/system/kernel2/os_i.h \
    Entry/system/kernel2/osek_kernel.h \
    Entry/system/kernel2/oslog.h \
    Entry/system/kernel2/resource.h \
    Entry/system/kernel2/task.h \
    Entry/system/kernel2/portable/qt/portable.h

FORMS    +=

INCLUDEPATH += VirtualDevice
INCLUDEPATH += Entry
INCLUDEPATH += Entry/include
INCLUDEPATH += Entry/system/kernel2
INCLUDEPATH += Entry/system/kernel2/portable/qt
INCLUDEPATH += Entry/system/kernel2/config
INCLUDEPATH += Application/Configuration

RESOURCES += \
    WhatsApp.qrc

