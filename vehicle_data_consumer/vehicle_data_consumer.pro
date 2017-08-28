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

TARGET = vehicle_data_consumer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-unused-parameter

DEFINES += BOOST_ALL_DYN_LINK

LIBS += \
    -lboost_log -lboost_system -lboost_thread

INVITE_LIBS = CommonAPI \
              CommonAPI-DBus \
              CommonAPI-SomeIP \
              dbus-1 \

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

INCLUDEPATH += src
INCLUDEPATH += $$_PRO_FILE_PWD_/../cdl_daemon/on_board_provider/interface/src-gen
INCLUDEPATH += $$_PRO_FILE_PWD_/../cdl_daemon/on_board_provider/interface/src-gen/v1
INCLUDEPATH += $$_PRO_FILE_PWD_/../cluster_hmi_application/interface/src-gen
INCLUDEPATH += $$_PRO_FILE_PWD_/../cluster_hmi_application/interface/src-gen/v1

SOURCES += main.cpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPIDBusDeployment.cpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPIDBusProxy.cpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPITypesDBusDeployment.cpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.cpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusStubAdapter.cpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterDataStubDefault.cpp \
    src/vehicle_data_consumer_cluster.cpp

HEADERS += \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPI.hpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPIDBusDeployment.hpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPIDBusProxy.hpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPIProxy.hpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPIProxyBase.hpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPITypes.hpp \
    ../cdl_daemon/on_board_provider/interface/src-gen/v1/org/genivi/CDL/ClientAPITypesDBusDeployment.hpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterData.hpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.hpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusStubAdapter.hpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterDataStub.hpp \
    ../cluster_hmi_application/interface/src-gen/v1/com/ivis/ClusterData/ClusterDataStubDefault.hpp \
    src/common_log_header.hpp \
    src/vehicle_data_consumer_cluster.hpp

*-arm-*|*-oe-*  {
   target.path = deploy/arm
}else{
   target.path = deploy/x86
}

INSTALLS += target
