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

TEMPLATE = subdirs

SUBDIRS += \
            lib-av-information-provider-someip \
            lib-cdl-client-api \
            lib-cdl-client-api-someip \
            av-information-provider \
            headunit-vehicle-data-consumer-climates \
            headunit-vehicle-data-consumer-running-status \
            av-hmi-application \
            media-manager \
            mode-manager \
            cdl-daemon \
            cluster-hmi-application \
            cluster-vehicle-data-consumer \
            vehicle-data-provider \



lib-av-information-provider-someip.subdir               = project/av-information-provider/libAVInformation
lib-cdl-client-api.subdir                               = project/cdl-client-api
lib-cdl-client-api-someip.subdir                        = project/cdl-client-api/libCDLClientSomeIp

av-information-provider.subdir                          = project/av-information-provider
headunit-vehicle-data-consumer-climates.subdir          = project/headunit-vehicle-data-consumer-climates
headunit-vehicle-data-consumer-running-status.subdir    = project/headunit-vehicle-data-consumer-running-status
av-hmi-application.subdir                               = project/av-hmi-application
media-manager.subdir                                    = project/media-manager
mode-manager.subdir                                     = project/mode-manager

cdl-daemon.subdir                                       = project/cdl-daemon
cluster-hmi-application.subdir                          = project/cluster-hmi-application
cluster-vehicle-data-consumer.subdir                    = project/cluster-vehicle-data-consumer
vehicle-data-provider.subdir                            = project/vehicle-data-provider


cluster-vehicle-data-consumer.depends                   = lib-cdl-client-api
headunit-vehicle-data-consumer-climates.depends         = lib-cdl-client-api
headunit-vehicle-data-consumer-running-status.depends   = lib-cdl-client-api
vehicle-data-provider.depends                           = lib-cdl-client-api



include(common-config.pri)

json.path = deploy/$$BUILD_DIR
json.files = json

commonapi-ini.path = deploy/$$BUILD_DIR
commonapi-ini.files = env/commonapi.ini

script.path = deploy/$$BUILD_DIR
script.files = script/*

INSTALLS += json commonapi-ini script
