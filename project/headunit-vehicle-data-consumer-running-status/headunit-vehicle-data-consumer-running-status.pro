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

QT += core
QT -= gui

TARGET = headunit-vehicle-data-consumer-running-status
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INTERFACE_DIR = ../interface

include(../../common-config.pri)

INCLUDEPATH += ../cdl-client-api/include

LIBS += -L$$_PRO_FILE_PWD_/../cdl-client-api/lib/$$CPU_ARCH -lCDLClientAPI -ldl

target.path = ../../deploy/$$BUILD_DIR/bin

INSTALLS += target



SOURCES += main.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerDBusStubAdapter.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerStubDefault.cpp \
    src/VehicleDataHandler.cpp \
    src/VehicleCDLDataHandler.cpp \
    src/DataHandlerFactory.cpp \
    src/VehicleDataManagerDebug.cpp \
    src/VehicleDataManagerService.cpp

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManager.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerDBusStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerStub.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerTypes.hpp \
    src/VehicleDataHandler.h \
    src/VehicleCDLDataHandler.h \
    src/DataHandlerFactory.h \
    src/VehicleDataManagerDebug.h \
    src/VehicleDataManagerService.h












