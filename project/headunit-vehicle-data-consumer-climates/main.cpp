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
#include <dlt.h>
#include <csignal>
#include <CommonAPI/CommonAPI.hpp>
#include <DATCManagerService.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    DLT_REGISTER_APP("datc","DATC Manager");
    DLT_ENABLE_LOCAL_PRINT();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    runtime->registerService("local", "com.ivis.DATCManager.DATCManager", DATCManagerService::instance());

    DATCManagerService::instance()->initService();

    int result = a.exec();

    runtime->unregisterService("local", DATCManager::getInterface(), "com.ivis.DATCManager.DATCManager");

    // clean up DLT
    DATCManagerService::finalize();

    DLT_UNREGISTER_APP();

    return result;
}
