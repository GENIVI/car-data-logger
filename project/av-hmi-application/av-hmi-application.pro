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

TEMPLATE = app
TARGET = av-hmi-application

QT += core qml quick widgets

INTERFACE_DIR = ../interface

include(../../common-config.pri)

include(src/src.pri)

*-arm-*|*-oe-* {
    target.path = /opt/cdl/bin
} else {
    target.path = ../../deploy/$$BUILD_DIR/bin
}

INSTALLS += target

RESOURCES += \ 
	component_qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManager.hpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusDeployment.hpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusProxy.hpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerProxy.hpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerProxyBase.hpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerTypes.hpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerTypesDBusDeployment.hpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/MediaManagerTypes.hpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/MediaManagerTypesDBusDeployment.hpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/PlaybackControl.hpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusDeployment.hpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusProxy.hpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/PlaybackControlProxy.hpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/PlaybackControlProxyBase.hpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManager.hpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerDBusDeployment.hpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerDBusProxy.hpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerProxy.hpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerProxyBase.hpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerTypes.hpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerTypesDBusDeployment.hpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManager.hpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerDBusDeployment.hpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerDBusProxy.hpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerProxy.hpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerProxyBase.hpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerTypes.hpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerTypesDBusDeployment.hpp

SOURCES += \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusDeployment.cpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerDBusProxy.cpp \
    ../interface/src-gen/v1/com/ivis/ModeManager/ModeManagerTypesDBusDeployment.cpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/MediaManagerTypesDBusDeployment.cpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusDeployment.cpp \
    ../interface/src-gen/v1/com/ivis/MediaManager/PlaybackControlDBusProxy.cpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerDBusDeployment.cpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerDBusProxy.cpp \
    ../interface/src-gen/v1/com/ivis/DATCManager/DATCManagerTypesDBusDeployment.cpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerDBusDeployment.cpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerDBusProxy.cpp \
    ../interface/src-gen/v1/com/ivis/VehicleDataManager/VehicleDataManagerTypesDBusDeployment.cpp
