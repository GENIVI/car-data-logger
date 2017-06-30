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

#include "dbusclienttestapp1.h"

#include <QCoreApplication>
#include <csignal>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); Q_UNUSED(sig); });
    signal(SIGINT, [](int sig){ qApp->quit(); Q_UNUSED(sig); });

    DBusClientTestApp1 * dbusClientTestApp = new DBusClientTestApp1();

    int result = a.exec();

    delete dbusClientTestApp;

    return result;
}
