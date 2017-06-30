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

QT += core
QT -= gui

CONFIG += c++11

TARGET = DBusClientTestApp2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INVITE_LIBS = CommonAPI \
              CommonAPI-DBus \
              CommonAPI-SomeIP \
              dbus-1 \

CONFIG += link_pkgconfig
PKGCONFIG += $$INVITE_LIBS

CONFIG(release, debug|release) {
    message( "release" )
    *-arm-* {
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
    *-arm-* {
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

INCLUDEPATH += \
    $$PWD/../../interface/src-gen \
    $$PWD/../../interface/src-gen/v1 \

SOURCES += \
    main.cpp \
    dbusclienttestapp2.cpp \
    ../../interface/src-gen/v1/org/genivi/CDL/ClientAPIDBusProxy.cpp \

HEADERS += \
    dbusclienttestapp2.h \
    ../../interface/src-gen/v1/org/genivi/CDL/ClientAPIProxy.hpp \
    ../../interface/src-gen/v1/org/genivi/CDL/ClientAPIProxyBase.hpp \
    ../../interface/src-gen/v1/org/genivi/CDL/ClientAPIDBusProxy.hpp \

target.path = ../deploy

INSTALLS += target

additional_files.path = ../deploy

INSTALLS += additional_files
