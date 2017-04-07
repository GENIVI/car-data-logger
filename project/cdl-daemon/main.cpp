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

#ifdef __CDL_GUI_MODE__
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#else
#include <QCoreApplication>
#endif

#include <QSqlTableModel>

#include <CommonAPI/CommonAPI.hpp>
#include <dlt.h>

#include "src/CDLDaemon.h"
#include "src/DBHandler.h"

#include <csignal>

using namespace v1::com::ivis::CDL;

int main(int argc, char *argv[])
{
#ifdef __CDL_GUI_MODE__
    QGuiApplication a(argc, argv);
#else
    QCoreApplication a(argc, argv);
#endif

    DLT_REGISTER_APP( "cdld", "CDL Daemon" );

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

#ifdef __CDL_GUI_MODE__
//    QQmlApplicationEngine engine;
    QQuickView view;

    QQmlContext * context = view.rootContext();
    DBHandler::instance()->setContext( context );

    view.setResizeMode(QQuickView::SizeViewToRootObject);
    view.setWidth(800);
    view.setHeight(480);
    view.setMinimumSize(QSize(800,480));
    view.create();
    view.setColor(QColor(Qt::transparent));

    view.setSource( QUrl(QStringLiteral("qrc:/main.qml")) );
    view.show();
#endif

    DLT_ENABLE_LOCAL_PRINT();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    runtime->registerService("local", "com.ivis.CDL.ClientAPIRemote.SomeIp", CDLRemoteAPIHandler::getInstance());
    runtime->registerService("local", "com.ivis.CDL.ClientAPILocal", CDLLocalAPIHandler::getInstance());

    int result = a.exec();

    CDLLocalAPIHandler::finalize();
    CDLRemoteAPIHandler::finalize();

    runtime->unregisterService("local", ClientAPIRemote::getInterface(), "com.ivis.CDL.ClientAPIRemote.SomeIp");
    runtime->unregisterService("local", ClientAPILocal::getInterface(), "com.ivis.CDL.ClientAPILocal");

    DLT_UNREGISTER_APP();

    return result;
}

