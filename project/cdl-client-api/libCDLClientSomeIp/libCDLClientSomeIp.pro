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
# Project created by QtCreator 2016-03-08T20:37:59
#
#-------------------------------------------------

QT       -= gui

TARGET = CDLClientSomeIp
TEMPLATE = lib

DEFINES += LIBCDLCLIENTSOMEIP_LIBRARY

INTERFACE_DIR = ../../interface

include(../../../common-config.pri)

target.path = ../../../deploy/$$BUILD_DIR/lib

INSTALLS += target

SOURCES += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPProxy.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPStubAdapter.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypesSomeIPDeployment.cpp

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemote.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteProxyBase.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteSomeIPStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteStub.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/CDL/ClientAPIRemoteTypesSomeIPDeployment.hpp
