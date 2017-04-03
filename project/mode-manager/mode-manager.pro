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

TARGET = mode-manager
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INTERFACE_DIR = ../interface

include(../../common-config.pri)

*-arm-*|*-oe-* {
    target.path = /opt/cdl/bin
} else {
    target.path = ../../deploy/$$BUILD_DIR/bin
}

INSTALLS += target

SOURCES += main.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusStubAdapter.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerStubDefault.cpp \
    src/ModeManagerDebug.cpp \
    src/ModeManagerService.cpp

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManager.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerStub.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerTypes.hpp \
    src/ModeManagerDebug.h \
    src/LogHelper.h \
    src/ModeDefine.h \
    src/ModeManagerService.h

