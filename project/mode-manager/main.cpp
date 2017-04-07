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
#include <dlt.h>
#include <CommonAPI/CommonAPI.hpp>
#include "ModeManagerService.h"
#include "LogHelper.h"

#include <QDebug>

DLT_DECLARE_CONTEXT( ContextModeManager )

int main( int argc, char *argv[] )
{
    QCoreApplication a( argc, argv );

    signal( SIGTERM, []( int sig )
    {
        qApp->quit();
    } );
    signal( SIGINT, []( int sig )
    {
        qApp->quit();
    } );

    DLT_REGISTER_APP("mode", "Mode Manager");
    DLT_REGISTER_CONTEXT(ContextModeManager, "mms", "Mode Manager Service");

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    runtime->registerService( "local", "com.ivis.ModeManager.ModeManager", ModeManageService::getInstance() );

    int result = a.exec();

    runtime->unregisterService("local", ModeManager::getInterface(), "com.ivis.ModeManager.ModeManager");

    DLT_UNREGISTER_CONTEXT(ContextModeManager);
    DLT_UNREGISTER_APP();

    return result;
}
