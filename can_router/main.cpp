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

#include "src/can_router.hpp"
#include "src/can_router_server.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <dlt.h>
#include <csignal>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ Q_UNUSED(sig); qApp->quit(); });
    signal(SIGINT, [](int sig){ Q_UNUSED(sig); qApp->quit(); });

    DLT_REGISTER_APP("vdp", "Vehicle Data Provider");
    DLT_ENABLE_LOCAL_PRINT();

    CANRouterServer::instance();

    CANRouter::instance();

    int result = a.exec();

    DLT_UNREGISTER_APP();

    return result;
}
