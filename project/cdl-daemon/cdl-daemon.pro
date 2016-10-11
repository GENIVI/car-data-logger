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

guimode{
    QT += qml quick widgets
    DEFINES += __CDL_GUI_MODE__
}

QT += sql

TARGET = cdl-daemon
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

INTERFACE_DIR = ../interface

include(../../common-config.pri)

target.path = ../../deploy/$$BUILD_DIR/bin

INSTALLS += target

SOURCES += main.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusStubAdapter.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalTypesDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypesSomeIPDeployment.cpp \
    src/CDLDaemon.cpp \
    src/CDLDataModel.cpp \
    src/DBHandler.cpp

guimode{
SOURCES +=
}

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocal.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemote.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPILocalTypesDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypesSomeIPDeployment.hpp \
    src/CDLDaemon.h \
    src/CDLDataModel.h \
    src/DBHandler.h

guimode{
HEADERS +=
}

guimode{
RESOURCES += \
    qml.qrc
}

