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
#include <QDir>
#include <csignal>
#include <dlt.h>
#include "PlaybackService.h"
#include <CommonAPI/CommonAPI.hpp>

DLT_DECLARE_CONTEXT(ContextPlayback)
DLT_DECLARE_CONTEXT(ContextTime)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    DLT_REGISTER_APP("mm", "Media Manager");
    DLT_ENABLE_LOCAL_PRINT();

    DLT_REGISTER_CONTEXT(ContextPlayback, "pb", "Media Playback");

    auto runtime = CommonAPI::Runtime::get();
    runtime->registerService("local", "com.ivis.MediaManager.PlaybackControl", PlaybackService::getInstance());

    int result = a.exec();

    runtime->unregisterService("local", PlaybackControl::getInterface(), "com.ivis.MediaManager.PlaybackControl");

    // clean up DLT
    DLT_UNREGISTER_CONTEXT(ContextPlayback);
    DLT_UNREGISTER_APP();

    return result;
}
