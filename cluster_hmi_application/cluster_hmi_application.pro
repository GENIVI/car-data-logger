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

TEMPLATE = app

QT += qml quick
CONFIG += c++11

TARGET = cluster_hmi_application

linux {
DEFINES += ENABLE_COMMONAPI
INCLUDEPATH += $$_PRO_FILE_PWD_/interface/src-gen
INCLUDEPATH += $$_PRO_FILE_PWD_/interface/src-gen src
INCLUDEPATH += $$_PRO_FILE_PWD_/interface/src-gen/v1

INVITE_LIBS = CommonAPI \
              CommonAPI-DBus \
              CommonAPI-SomeIP \
              dbus-1 \
              automotive-dlt \

CONFIG += link_pkgconfig
PKGCONFIG += $$INVITE_LIBS
}

CONFIG(release, debug|release) {
    message( "release" )
    DESTDIR = release
    DEFINES += __RELEASE__
}
CONFIG(debug, debug|release) {
    message( "debug" )
    DESTDIR = debug
    DEFINES += __DEBUG__
    QMAKE_CXXFLAGS += -g
}

*-arm-*|*-oe-*  {
    message("arm!!")
    DESTDIR     = $$DESTDIR/arm
    OBJECTS_DIR = $$DESTDIR/.obj
    MOC_DIR     = $$DESTDIR/.moc
    RCC_DIR     = $$DESTDIR/.qrc
    UI_DIR      = $$DESTDIR/.ui
    DEFINES     += __TCC8935__
}else{
    message("x86!!")
    DESTDIR     = $$DESTDIR/x86
    OBJECTS_DIR = $$DESTDIR/.obj
    MOC_DIR     = $$DESTDIR/.moc
    RCC_DIR     = $$DESTDIR/.qrc
    UI_DIR      = $$DESTDIR/.ui
}


# install path
*-arm-*|*-oe-*  {
   target.path = deploy/arm
}else{
   target.path = deploy/x86
}
INSTALLS += target

SOURCES += main.cpp \
    cluster.cpp \
    interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.cpp \
    interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusProxy.cpp \
    album_art_provider.cpp \
    av_data_manager.cpp \
    av_information_provider_helper.cpp \
    vehicle_data_manager_helper.cpp \
    gauge_area.cpp

RESOURCES += \
    qml/qml.qrc \
    image/image.qrc

HEADERS += \
    interface/src-gen/v1/com/ivis/ClusterData/ClusterData.hpp \
    interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.hpp \
    interface/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusProxy.hpp \
    interface/src-gen/v1/com/ivis/ClusterData/ClusterDataProxy.hpp \
    interface/src-gen/v1/com/ivis/ClusterData/ClusterDataProxyBase.hpp \
    album_art_provider.hpp \
    av_data_manager.hpp \
    av_information_provider_helper.hpp \
    av_information_types_enum.hpp \
    cluster.hpp \
    gauge_area.hpp \
    vehicle_data_manager_helper.hpp
