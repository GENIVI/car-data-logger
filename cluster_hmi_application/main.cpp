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

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QSharedPointer>
#include "cluster.hpp"
#include "gauge_area.hpp"
#include "av_information_types_enum.hpp"
#include "av_data_manager.hpp"
#include "album_art_provider.hpp"

#include "vehicle_data_manager_helper.hpp"
#include "av_information_provider_helper.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeViewToRootObject);
    view.setWidth(800);
    view.setHeight(480);
    view.setMinimumSize(QSize(800,480));
#ifdef __TCC8935__
    view.setFlags(Qt::FramelessWindowHint);
#endif

    Cluster *cluster = Cluster::instance(&view).data();
    view.rootContext()->setContextProperty("Cluster", cluster);
    view.rootContext()->setContextProperty("AVDataManager", AVDataManager::instance().data());    
    view.engine()->addImageProvider("AlbumArtProvider",AlbumArtProvider::instance().data());
    qmlRegisterType<GaugeArea>("GaugeArea", 1, 0, "GaugeArea");
    qmlRegisterType<AVInformationTypesEnum::Source>("AVInformationTypes", 1, 0, "Source");
    qmlRegisterType<AVInformationTypesEnum::PlayStatus>("AVInformationTypes", 1, 0, "PlayStatus");

    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.show();

    AVInformationProviderHelper::getInstance();
    VehicleDataManagerHelper::getInstance();

    return app.exec();
}
