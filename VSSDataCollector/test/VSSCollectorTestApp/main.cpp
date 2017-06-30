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

#include <vssdatacollector.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <csignal>

#include "../../../common/log.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ Q_UNUSED(sig); qApp->quit(); });
    signal(SIGINT, [](int sig){ Q_UNUSED(sig); qApp->quit(); });

    init_log(boost::log::trivial::severity_level::debug);

    QString currentPath = QDir::currentPath();

    setenv("VSS_JSON_FILE", (QString("%1/vss_rel_1.json").arg(currentPath)).toStdString().data(), 1);
    setenv("VSS_COLLECTOR_CONFIGURATION_FILE", (QString("%1/DataConfig.json").arg(currentPath)).toStdString().data(), 1);
    setenv("VSS_VSI_FILE", (QString("%1/vss_rel_1.vsi").arg(currentPath)).toStdString().data(), 1);

    VSSDataCollector vssDataCollector_instance;

    if( !vssDataCollector_instance.start() )
    {
        qDebug() << "Vss Data Collector Daemon Error";
        return 0;
    }

    int result = a.exec();

    vssDataCollector_instance.stop();

    return result;
}
