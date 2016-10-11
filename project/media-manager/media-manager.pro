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

TARGET = media-manager
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INTERFACE_DIR = ../interface

include(../../common-config.pri)

INCLUDEPATH += src/playback

target.path = ../../deploy/$$BUILD_DIR/bin
cover_art.path = ../../deploy/$$BUILD_DIR
cover_art.files = cover-art

INSTALLS += target
INSTALLS += cover_art


SOURCES += main.cpp \
    src/MediaManagerDebug.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusStubAdapter.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusProxy.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerTypesDBusDeployment.cpp \
    src/playback/AbstractPlayer.cpp \
    src/playback/PlaybackLogHelper.cpp \
    src/playback/PlaybackManager.cpp \
    src/playback/PlaybackService.cpp \
    src/playback/USBMusicPlayer.cpp \
    src/playback/USBVideoPlayer.cpp

HEADERS += \
    src/MediaManagerDebug.h \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/MediaManagerTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControl.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusStubAdapter.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlStub.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/MediaManager/PlaybackControlStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManager.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerProxyBase.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ModeManager/ModeManagerTypesDBusDeployment.hpp \
    src/playback/AbstractPlayer.h \
    src/playback/PlaybackLogHelper.h \
    src/playback/PlaybackManager.h \
    src/playback/PlaybackService.h \
    src/playback/USBMusicPlayer.h \
    src/playback/USBVideoPlayer.h
