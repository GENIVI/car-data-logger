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
#include <QQmlContext>
#include <QDebug>
#include <QQuickView>

#include "src/Simulator.h"
#include "src/VehicleDataProvider.h"

#include <dlt.h>

#include <csignal>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    view.setResizeMode(QQuickView::SizeViewToRootObject);
    view.setWidth(800);
    view.setHeight(480);
    view.setMinimumSize(QSize(800,480));
    view.setGeometry(900, 500, 800, 480);

    view.setProperty("IVI-Surface-ID", 220);

    DLT_REGISTER_APP("vdp", "Vehicle Data Provider");

    VehicleDataProvider::instance();

    view.rootContext()->setContextProperty("Vehicle_Data_Simulator", HardWareSimulator::VehicleDataSimulator::instance() );
    view.rootContext()->setContextProperty("HVAC_Data_Simulator", HardWareSimulator::HVACDataSimulator::instance() );

    view.setSource(QUrl("qrc:/qml/simulator.qml"));
    view.show();

    int result = app.exec();

    VehicleDataProvider::finalize();
    HardWareSimulator::VehicleDataSimulator::finalize();
    HardWareSimulator::HVACDataSimulator::finalize();

    DLT_UNREGISTER_APP();

    return result;
}

