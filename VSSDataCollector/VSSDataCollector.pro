#/*
#* Copyright (C) 2016, IVIS
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

#/*!
#* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
#*
#* \copyright Copyright (c) 2016, IVIS \n
#* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
#*
#*/

QT -= gui

TARGET = VSSDataCollector

TEMPLATE = lib

DEFINES += BOOST_ALL_DYN_LINK

INVITE_LIBS = vsi


CONFIG += link_pkgconfig
PKGCONFIG += $$INVITE_LIBS

LIBS += \
    -lboost_system \
    -lboost_thread \
    -lboost_log \

include(src/src.pri)

OTHER_FILES += README.md
