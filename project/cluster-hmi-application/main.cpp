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

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QSharedPointer>
#include "Cluster.h"
#include "GaugeArea.h"
#include "AVInformationTypesEnum.h"
#include "AVDataManager.h"
#include "AlbumArtProvider.h"

#include "VehicleDataManagerHelper.h"
#include "AVInformationProviderHelper.h"

#include <csignal>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    QQuickView view;
    view.setResizeMode(QQuickView::SizeViewToRootObject);
    view.setWidth(800);
    view.setHeight(480);
    view.setMinimumSize(QSize(800,480));

    view.rootContext()->setContextProperty("Cluster", Cluster::instance());
    view.rootContext()->setContextProperty("AVDataManager", AVDataManager::instance());
    view.engine()->addImageProvider("AlbumArtProvider",AlbumArtProvider::instance());
    qmlRegisterType<GaugeArea>("GaugeArea", 1, 0, "GaugeArea");
    qmlRegisterType<AVInformationTypesEnum::Source>("AVInformationTypes", 1, 0, "Source");
    qmlRegisterType<AVInformationTypesEnum::PlayStatus>("AVInformationTypes", 1, 0, "PlayStatus");

    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.show();
    view.setGeometry(900, 0, 800, 480);

    AVInformationProviderHelper::getInstance();
    VehicleDataManagerHelper::getInstance();

    int result = app.exec();

    view.engine()->removeImageProvider("AlbumArtProvider");

    Cluster::finalize();
    AVDataManager::finalize();
    AVInformationProviderHelper::finalize();
    VehicleDataManagerHelper::finalize();

    return result;
}
