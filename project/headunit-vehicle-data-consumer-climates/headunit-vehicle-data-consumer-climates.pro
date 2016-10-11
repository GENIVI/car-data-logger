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
QT -= gui

TARGET = headunit-vehicle-data-consumer-climates
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INTERFACE_DIR = ../interface

include(../../common-config.pri)

INCLUDEPATH += ../cdl-client-api/include

LIBS += -L$$_PRO_FILE_PWD_/../cdl-client-api/lib/$$CPU_ARCH -lCDLClientAPI -ldl

target.path = ../../deploy/$$BUILD_DIR/bin

INSTALLS += target


SOURCES += main.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/DATCManager/DATCManagerStubDefault.cpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/DATCManager/DATCManagerDBusStubAdapter.cpp \
    src/DATCDataHandler.cpp \
    src/DATCManagerService.cpp \
    src/DATCCDLDataHandler.cpp \
    src/DataHandlerFactory.cpp \
    src/DATCManagerDebug.cpp


HEADERS += \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/DATCManager/DATCManagerStub.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/DATCManager/DATCManagerStubDefault.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/DATCManager/DATCManagerTypes.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/DATCManager/DATCManager.hpp \
    $$INTERFACE_DIR/src-gen/v1/com/ivis/DATCManager/DATCManagerDBusStubAdapter.hpp \
    src/DATCDataHandler.h \
    src/DATCManagerService.h \
    src/DATCCDLDataHandler.h \
    src/DataHandlerFactory.h \
    src/DATCManagerDebug.h
