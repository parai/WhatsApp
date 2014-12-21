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
    Entry/rte/Rte.c \
    Entry/platform/qt/lua-5.2.3/arLua.cpp \
    Entry/platform/qt/lua-5.2.3/src/lapi.c \
    Entry/platform/qt/lua-5.2.3/src/lauxlib.c \
    Entry/platform/qt/lua-5.2.3/src/lbaselib.c \
    Entry/platform/qt/lua-5.2.3/src/lbitlib.c \
    Entry/platform/qt/lua-5.2.3/src/lcode.c \
    Entry/platform/qt/lua-5.2.3/src/lcorolib.c \
    Entry/platform/qt/lua-5.2.3/src/lctype.c \
    Entry/platform/qt/lua-5.2.3/src/ldblib.c \
    Entry/platform/qt/lua-5.2.3/src/ldebug.c \
    Entry/platform/qt/lua-5.2.3/src/ldo.c \
    Entry/platform/qt/lua-5.2.3/src/ldump.c \
    Entry/platform/qt/lua-5.2.3/src/lfunc.c \
    Entry/platform/qt/lua-5.2.3/src/lgc.c \
    Entry/platform/qt/lua-5.2.3/src/linit.c \
    Entry/platform/qt/lua-5.2.3/src/liolib.c \
    Entry/platform/qt/lua-5.2.3/src/llex.c \
    Entry/platform/qt/lua-5.2.3/src/lmathlib.c \
    Entry/platform/qt/lua-5.2.3/src/lmem.c \
    Entry/platform/qt/lua-5.2.3/src/loadlib.c \
    Entry/platform/qt/lua-5.2.3/src/lobject.c \
    Entry/platform/qt/lua-5.2.3/src/lopcodes.c \
    Entry/platform/qt/lua-5.2.3/src/loslib.c \
    Entry/platform/qt/lua-5.2.3/src/lparser.c \
    Entry/platform/qt/lua-5.2.3/src/lstate.c \
    Entry/platform/qt/lua-5.2.3/src/lstring.c \
    Entry/platform/qt/lua-5.2.3/src/lstrlib.c \
    Entry/platform/qt/lua-5.2.3/src/ltable.c \
    Entry/platform/qt/lua-5.2.3/src/ltablib.c \
    Entry/platform/qt/lua-5.2.3/src/ltm.c \
    Entry/platform/qt/lua-5.2.3/src/lundump.c \
    Entry/platform/qt/lua-5.2.3/src/lvm.c \
    Entry/platform/qt/lua-5.2.3/src/lzio.c \
    Entry/platform/qt/lua-5.2.3/src/lua.c

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
    Entry/include/Rte.h \
    Entry/include/types/Adc_Types.h \
    Entry/include/types/BswM_Types.h \
    Entry/include/types/Cal_Types.h \
    Entry/include/types/Can_Types.h \
    Entry/include/types/CanIf_Types.h \
    Entry/include/types/CanNm_Types.h \
    Entry/include/types/CanSM_Types.h \
    Entry/include/types/CanTp_Types.h \
    Entry/include/types/CanTrcv_Types.h \
    Entry/include/types/Cdd_Types.h \
    Entry/include/types/Com_Types.h \
    Entry/include/types/ComM_Types.h \
    Entry/include/types/CorTst_Types.h \
    Entry/include/types/Crc_Types.h \
    Entry/include/types/Csm_Types.h \
    Entry/include/types/Dbg_Types.h \
    Entry/include/types/Dcm_Types.h \
    Entry/include/types/Dem_Types.h \
    Entry/include/types/Det_Types.h \
    Entry/include/types/Dio_Types.h \
    Entry/include/types/Dlt_Types.h \
    Entry/include/types/Ea_Types.h \
    Entry/include/types/EcuC_Types.h \
    Entry/include/types/EcuM_Types.h \
    Entry/include/types/Eep_Types.h \
    Entry/include/types/Eth_Types.h \
    Entry/include/types/EthIf_Types.h \
    Entry/include/types/EthSm_Types.h \
    Entry/include/types/EthTrcv_Types.h \
    Entry/include/types/Fee_Types.h \
    Entry/include/types/FiM_Types.h \
    Entry/include/types/Fls_Types.h \
    Entry/include/types/FlsTst_Types.h \
    Entry/include/types/Fr_Types.h \
    Entry/include/types/FrArTp_Types.h \
    Entry/include/types/FrIf_Types.h \
    Entry/include/types/FrNm_Types.h \
    Entry/include/types/FrSM_Types.h \
    Entry/include/types/FrTp_Types.h \
    Entry/include/types/FrTrcv_Types.h \
    Entry/include/types/Gpt_Types.h \
    Entry/include/types/Icu_Types.h \
    Entry/include/types/IpduM_Types.h \
    Entry/include/types/J1939Tp_Types.h \
    Entry/include/types/Lin_Types.h \
    Entry/include/types/LinIf_Types.h \
    Entry/include/types/LinNm_Types.h \
    Entry/include/types/LinSM_Types.h \
    Entry/include/types/LinTp_Types.h \
    Entry/include/types/LinTrcv_Types.h \
    Entry/include/types/Mcu_Types.h \
    Entry/include/types/MemIf_Types.h \
    Entry/include/types/MemMap_Types.h \
    Entry/include/types/Nm_Types.h \
    Entry/include/types/NvM_Types.h \
    Entry/include/types/Os_Types.h \
    Entry/include/types/PduR_Types.h \
    Entry/include/types/Port_Types.h \
    Entry/include/types/Pwm_Types.h \
    Entry/include/types/RamTst_Types.h \
    Entry/include/types/Rte_Types.h \
    Entry/include/types/SoAd_Types.h \
    Entry/include/types/Spi_Types.h \
    Entry/include/types/StbM_Types.h \
    Entry/include/types/UdpNm_Types.h \
    Entry/include/types/Wdg_Types.h \
    Entry/include/types/WdgIf_Types.h \
    Entry/include/types/WdgM_Types.h \
    Entry/include/types/Xcp_Types.h \
    Entry/platform/qt/lua-5.2.3/src/lua.hpp \
    Entry/platform/qt/lua-5.2.3/arLua.h \
    Entry/platform/qt/lua-5.2.3/src/lapi.h \
    Entry/platform/qt/lua-5.2.3/src/lauxlib.h \
    Entry/platform/qt/lua-5.2.3/src/lcode.h \
    Entry/platform/qt/lua-5.2.3/src/lctype.h \
    Entry/platform/qt/lua-5.2.3/src/ldebug.h \
    Entry/platform/qt/lua-5.2.3/src/ldo.h \
    Entry/platform/qt/lua-5.2.3/src/lfunc.h \
    Entry/platform/qt/lua-5.2.3/src/lgc.h \
    Entry/platform/qt/lua-5.2.3/src/llex.h \
    Entry/platform/qt/lua-5.2.3/src/llimits.h \
    Entry/platform/qt/lua-5.2.3/src/lmem.h \
    Entry/platform/qt/lua-5.2.3/src/lobject.h \
    Entry/platform/qt/lua-5.2.3/src/lopcodes.h \
    Entry/platform/qt/lua-5.2.3/src/lparser.h \
    Entry/platform/qt/lua-5.2.3/src/lstate.h \
    Entry/platform/qt/lua-5.2.3/src/lstring.h \
    Entry/platform/qt/lua-5.2.3/src/ltable.h \
    Entry/platform/qt/lua-5.2.3/src/ltm.h \
    Entry/platform/qt/lua-5.2.3/src/lua.h \
    Entry/platform/qt/lua-5.2.3/src/luaconf.h \
    Entry/platform/qt/lua-5.2.3/src/lualib.h \
    Entry/platform/qt/lua-5.2.3/src/lundump.h \
    Entry/platform/qt/lua-5.2.3/src/lvm.h \
    Entry/platform/qt/lua-5.2.3/src/lzio.h

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
               Entry/platform/qt/common \
               Entry/platform/qt/lua-5.2.3/src  \
               Entry/platform/qt/lua-5.2.3

RESOURCES += \
    WhatsApp.qrc

LIBS +=

OTHER_FILES += \
    Entry/platform/qt/lua-5.2.3/src/liblua.a

