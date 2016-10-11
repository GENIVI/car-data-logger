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
# Project created by QtCreator 2016-03-08T16:48:19
#
#-------------------------------------------------

QT       -= gui

TARGET = AVInformationSomeIp
TEMPLATE = lib

DEFINES += LIBAVINFORMATION_LIBRARY

INTERFACE_DIR = ../../interface

include(../../../common-config.pri)

target.path = ../../../deploy/$$BUILD_DIR/lib

INSTALLS += target

SOURCES += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationSomeIPDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationSomeIPProxy.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationSomeIPStubAdapter.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationTypesSomeIPDeployment.cpp

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformation.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationProxyBase.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationSomeIPDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationSomeIPProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationSomeIPStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationStub.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationTypesSomeIPDeployment.hpp



