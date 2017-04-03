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

QT += core gui widgets
TARGET = av-information-provider
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
    src/AVInformationProvider.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/MediaManagerTypesDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusProxy.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusProxy.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerTypesDBusDeployment.cpp

HEADERS += \
    src/AVInformationProvider.h \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/AVInformationProvider/AVInformationTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/MediaManagerTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/MediaManagerTypesDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControl.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlProxyBase.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManager.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerProxyBase.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerTypesDBusDeployment.hpp
