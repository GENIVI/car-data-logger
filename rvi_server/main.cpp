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

#include "vehicle_data_viewer_window.hpp"
#include "vehicle_data_manager_window.hpp"
#include "rvi_server.hpp"

#include <QDebug>
#include <QApplication>
#include <csignal>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    signal(SIGTERM, [](int sig){ Q_UNUSED(sig); qApp->quit(); });
    signal(SIGINT, [](int sig){ Q_UNUSED(sig); qApp->quit(); });

    VehicleDataViewerWindow * vehicle_data_viewer_window_instance = VehicleDataViewerWindow::getInstance();
    VehicleDataManagerWindow * vehicle_data_manager_window_istance = VehicleDataManagerWindow::getInstance();

    RVIServer * rviServer = RVIServer::getInstance();

    if( vehicle_data_viewer_window_instance != NULL )
    {
        vehicle_data_viewer_window_instance->show();
    }

    if( vehicle_data_manager_window_istance != NULL )
    {
        vehicle_data_manager_window_istance->show();
    }

    int result = app.exec();

    delete rviServer;

    return result;
}
