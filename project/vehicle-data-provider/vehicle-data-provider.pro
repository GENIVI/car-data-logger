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

QT += core qml quick

TARGET = vehicle-data-provider
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
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusStubAdapter.cpp \
    src/VehicleDataProvider.cpp \
    src/Simulator.cpp

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypes.hpp \
    src/VehicleDataProvider.h \
    src/Simulator.h \
    src/CommonEnum.h

RESOURCES += \
    qml/qml.qrc \
    image/image.qrc \
