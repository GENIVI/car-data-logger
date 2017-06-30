/*
* Copyright (C) 2017, IVIS
*
* This file is part of GENIVI Project CDL - Car Data Logger.
*
* This Source Code Form is subject to the terms of the
* Mozilla Public License (MPL), v. 2.0.
* If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* For further information see http://www.genivi.org/.
*/

/*!
* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
*
* \copyright Copyright (c) 2017, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#include "datagenerator.h"
#include "onboardprovider.h"
#include "../../../common/log.h"

#include <QCoreApplication>
#include <QDir>
#include <csignal>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ Q_UNUSED(sig); qApp->quit(); });
    signal(SIGINT, [](int sig){ Q_UNUSED(sig); qApp->quit(); });

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    setenv("COMMONAPI_CONFIG", "config/commonapi.ini", 1);
    setenv("VSOMEIP_APPLICATION_NAME", "onboard-provider", 1);
    setenv("VSOMEIP_CONFIGURATION", "config/vsomeip-onboard-provider.json", 1);

    init_log(boost::log::trivial::severity_level::debug);

    int result = 0;
    OnBoardProvider * onBoardProvider_instance = new OnBoardProvider();

    if( !onBoardProvider_instance->start() )
    {
        return result;
    }

    DataGenerator * dataGenerator_instance = new DataGenerator(onBoardProvider_instance);
    dataGenerator_instance->init();

    result = a.exec();

    delete dataGenerator_instance;

    onBoardProvider_instance->stop();
    delete onBoardProvider_instance;

    return result;
}
