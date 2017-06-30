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
CONFIG += console
CONFIG -= app_bundle

TARGET = OffBoardProviderTestApp
TEMPLATE = app

DEFINES += BOOST_ALL_DYN_LINK

HEADERS += \
    offboardprovidertestapp.h \
    $$PWD/../../../common/log.h \

SOURCES += \
    main.cpp \
    offboardprovidertestapp.cpp \
    $$PWD/../../../common/log.cpp \

INVITE_LIBS = OffBoardProvider \
              python-2.7 \

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

target.path = ../deploy

INSTALLS += target

additional_files.files = $$PWD/SampleJSONFiles/vehicleData1.json $$PWD/SampleJSONFiles/vehicleData2.json $$PWD/SampleJSONFiles/vehicleData3.json \
                         $$PWD/SampleJSONFiles/vehicleData4.json $$PWD/SampleJSONFiles/vehicleData5.json
additional_files.path = ../deploy/SampleJSONFiles

additional_python_files.files = rvi_python_file/*
additional_python_files.path = /usr/lib/rvi_core

INSTALLS += additional_files
INSTALLS += additional_python_files
