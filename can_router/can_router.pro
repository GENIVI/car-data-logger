#/*
#* Copyright (C) 2017, IVIS
#*
#* This file is part of GENIVI Project CDL - Car Data Logger.
#*
#* This Source Code Form is subject to the terms of the
#* Mozilla Public License (MPL), v. 2.0.
#* If a copy of the MPL was not distributed with this file,
#* You can obtain one at http://mozilla.org/MPL/2.0/.
#*
#* For further information see http://www.genivi.org/.
#*/
#
#/*!
#* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
#*
#* \copyright Copyright (c) 2017, IVIS \n
#* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
#*
#*/

QT += core serialport network
QT -= gui

TARGET = can_router
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=gnu++11 -D__GXX_EXPERIMENTAL_CXX0X__
QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-unused-parameter

INVITE_LIBS += \
    automotive-dlt \
    vsi \


CONFIG += link_pkgconfig
PKGCONFIG += $$INVITE_LIBS

CONFIG(release, debug|release) {
    message( "release" )
    *-arm-*|*-oe-*  {
        message("arm!!")
        DESTDIR = release/arm
    }else{
        message("x86!!")
        DESTDIR = release/x86
    }
    DEFINES += __RELEASE__
}

CONFIG(debug, debug|release) {
    message( "debug" )
    *-arm-*|*-oe-*  {
        message("arm!!")
        DESTDIR = debug/arm
    }else{
        message("x86!!")
        DESTDIR = debug/x86
    }
    DEFINES += __DEBUG__
    QMAKE_CXXFLAGS += -g
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR     = $$DESTDIR/.moc
RCC_DIR     = $$DESTDIR/.qrc
UI_DIR      = $$DESTDIR/.ui

# Install path
*-arm-*|*-oe-*  {
   target.path = deploy/arm
}else{
   target.path = deploy/x86
}

INSTALLS += target


SOURCES += \
    main.cpp \
    src/can_router.cpp \
    src/can_router_server.cpp

HEADERS += \
    src/can_router.hpp \
    src/can_router_server.hpp
