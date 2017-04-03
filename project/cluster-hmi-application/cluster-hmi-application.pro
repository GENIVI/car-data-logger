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
QT += qml quick
TARGET = cluster-hmi-application

INTERFACE_DIR = ../interface

include(../../common-config.pri)

DEFINES += ENABLE_COMMONAPI

*-arm-*|*-oe-* {
    target.path = /opt/cdl/bin
} else {
    target.path = ../../deploy/$$BUILD_DIR/bin
}

INSTALLS += target

SOURCES += main.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusProxy.cpp \
    src/AlbumArtProvider.cpp \
    src/AVDataManager.cpp \
    src/AVInformationProviderHelper.cpp \
    src/Cluster.cpp \
    src/GaugeArea.cpp \
    src/VehicleDataManagerHelper.cpp


RESOURCES += \
    qml/qml.qrc \
    image/image.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)

HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterData.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusDeployment.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataDBusProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataProxy.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/ClusterData/ClusterDataProxyBase.hpp\
    src/AlbumArtProvider.h \
    src/AVDataManager.h \
    src/AVInformationProviderHelper.h \
    src/AVInformationTypesEnum.h \
    src/Cluster.h \
    src/GaugeArea.h \
    src/VehicleDataManagerHelper.h

DISTFILES +=
