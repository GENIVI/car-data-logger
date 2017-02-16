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

#/*!
#* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
#*
#* \copyright Copyright (c) 2017, IVIS \n
#* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
#*
#*/

QT -= gui

TARGET = DataStoreManager

TEMPLATE = lib

DEFINES += BOOST_ALL_DYN_LINK

LIBS += \
    -lsqlite3 \
    -lboost_log \
    -lboost_system \
    -lboost_thread \
    -lboost_filesystem \
    -lboost_date_time \


include(src/src.pri)
