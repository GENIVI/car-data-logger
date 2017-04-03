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

CONFIG += c++11

QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-unused-parameter

INVITE_LIBS = CommonAPI \
              CommonAPI-DBus \
              CommonAPI-SomeIP \
              dbus-1 \
              automotive-dlt \

CONFIG += link_pkgconfig
PKGCONFIG += $$INVITE_LIBS

LIBRARYS = $$LIBS

for(library, LIBRARYS) {
    message("$${library}")
}


INCLUDEPATH += $$INTERFACE_DIR/src-gen
INCLUDEPATH += $$INTERFACE_DIR/src-gen/v1
INCLUDEPATH += $$INTERFACE_DIR/src-gen/v2
INCLUDEPATH += src

*-arm-*|*-oe-* {
    CPU_ARCH=arm
} else {
    CPU_ARCH=x86
}

CONFIG(release, debug|release) {
    BUILD_DIR=release
    DEFINES += __RELEASE__
} else {
    BUILD_DIR=debug
    DEFINES += __DEBUG__
    QMAKE_CXXFLAGS += -g
}

DESTDIR     = $$BUILD_DIR/$$CPU_ARCH
OBJECTS_DIR = $$BUILD_DIR/$$CPU_ARCH/.obj
MOC_DIR     = $$BUILD_DIR/$$CPU_ARCH/.moc
RCC_DIR     = $$BUILD_DIR/$$CPU_ARCH/.qrc
UI_DIR      = $$BUILD_DIR/$$CPU_ARCH/.ui
