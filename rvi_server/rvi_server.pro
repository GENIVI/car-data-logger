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

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = rvi_server
TEMPLATE = app

SOURCES += \
    main.cpp \

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
    /usr/include/python2.7 \
    $$PWD/src/ \
    $$PWD/src/vehicle_data_manager \
    $$PWD/src/vehicle_data_viewer \

LIBS += \
    -lboost_system \
    -lboost_date_time \
    -lboost_thread \
    -lboost_iostreams \
    -L/usr/lib/python2.7/config-x86_64-linux-gnu/ -lpython2.7 \
    -L/usr/lib/python2.7/config-x86_64-linux-gnu \

FORMS    += \
    vehicledatamanagerwindow.ui \
    vehicledataviewerwindow.ui

target.path = ./deploy

INSTALLS += target

include(src/src.pri)

