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

#include "vehicledatagenerator.h"
#include "../../../common/log.h"

#include <QCoreApplication>
#include <QDir>
#include <csignal>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ Q_UNUSED(sig); qApp->quit(); });
    signal(SIGINT, [](int sig){ Q_UNUSED(sig); qApp->quit(); });

    init_log(boost::log::trivial::severity_level::debug);

    int result = 0;
    QString currentPath = QDir::currentPath();

    setenv("STORE_CONFIG_FILE", (QString("%1/store_config_file.json").arg(currentPath)).toStdString().data(), 1);

    vehicleDataGenerator *dataGenerator_instance = new vehicleDataGenerator();

    if( !dataGenerator_instance->init() )
    {
        return result;
    }

    result = a.exec();

    delete dataGenerator_instance;

    return result;
}
