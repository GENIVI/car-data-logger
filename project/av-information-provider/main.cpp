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

#include <QApplication>
#include "AVInformationProvider.h"
#include <dlt.h>
#include <csignal>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    DLT_REGISTER_APP("avip", "AV Information Provider");
    DLT_ENABLE_LOCAL_PRINT();

    AVInformationProvider * service = new AVInformationProvider(&a);

    int result = a.exec();

    delete service;

    // clean up DLT
    DLT_UNREGISTER_APP();

    return result;
}

