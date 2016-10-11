#/*
# * Copyright (C) 2016, IVIS
# *
# * This file is part of GENIVI Project CDL - Car Data Logger.
# *
# * This Source Code Form is subject to the terms of the
# * Mozilla Public License (MPL), v. 2.0.
# * If a copy of the MPL was not distributed with this file,
# * You can obtain one at http://mozilla.org/MPL/2.0/.
# *
# * For further information see http://www.genivi.org/.
# */

#/*!
# * \author Seung-Hyun Yun <shyun@ivisolution.com>
# *
# * \copyright Copyright (c) 2016, IVIS \n
# * License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
#*/


#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T21:26:42
#
#-------------------------------------------------

QT       -= gui

TARGET = CDLClientAPI
TEMPLATE = lib

DEFINES += CDLCLIENTAPI_LIBRARY

INTERFACE_DIR = ../interface

include(../../common-config.pri)

INCLUDEPATH += include

DESTDIR     = $$_PRO_FILE_PWD_/lib/$$CPU_ARCH

target.path = ../../deploy/$$BUILD_DIR/lib

INSTALLS += target

SOURCES += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusProxy.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalTypesDBusDeployment.cpp \
    src/CDLClientAPI.cpp \
    src/CDLClientLocalAPI.cpp \
    src/CDLClientRemoteAPI.cpp

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocal.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalProxyBase.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalTypesDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypes.hpp \
    include/cdl/CDLClientAPI.h \
    include/cdl/CDLClientAPIDefine.h \
    include/cdl/interfaces/CDLData.h \
    include/cdl/interfaces/vehicledata/VehicleData.h \
    include/cdl/interfaces/vehicledata/VehicleDataClimates.h \
    include/cdl/interfaces/vehicledata/VehicleDataDrivingSafety.h \
    include/cdl/interfaces/vehicledata/VehicleDataMaintenance.h \
    include/cdl/interfaces/vehicledata/VehicleDataParking.h \
    include/cdl/interfaces/vehicledata/VehicleDataPersonalization.h \
    include/cdl/interfaces/vehicledata/VehicleDataRunningStatus.h \
    include/cdl/interfaces/vehicledata/VehicleDataVisionSystem.h \
    include/cdl/interfaces/vehicledata/VehicleInformation.h \
    src/CDLClientLocalAPI.h \
    src/CDLClientRemoteAPI.h \
    src/CDLClientProxyBase.h
