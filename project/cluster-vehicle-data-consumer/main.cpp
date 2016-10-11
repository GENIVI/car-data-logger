/*
 * Copyright (C) 2016, IVIS
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
 * \author Seung-Hyun Yun <shyun@ivisolution.com>
 *
 * \copyright Copyright (c) 2016, IVIS \n
 * License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
 *
 * \file main.cpp
*/

#include <QCoreApplication>
#include <csignal>

#include "VehicleDataConsumerCluster.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    DLT_REGISTER_APP("vdcc", "Vehcile Data Consumer for Cluster");
    DLT_ENABLE_LOCAL_PRINT();

    VehicleDataConsumerCluster::instance();

    int result = a.exec();

    VehicleDataConsumerCluster::finalize();

    // clean up DLT
    DLT_UNREGISTER_APP();

    return result;
}
