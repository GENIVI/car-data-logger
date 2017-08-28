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

#ifndef VEHICLEDATAMANAGERHELPER_H
#define VEHICLEDATAMANAGERHELPER_H

#include <QObject>
#include <QLoggingCategory>

#ifdef ENABLE_COMMONAPI
    #include <CommonAPI/CommonAPI.hpp>
    #include <com/ivis/ClusterData/ClusterDataProxy.hpp>

    using namespace v1::com::ivis::ClusterData;
#endif

Q_DECLARE_LOGGING_CATEGORY(vehicleDataManagerHelper)

class VehicleDataManagerHelper : public QObject
{
    Q_OBJECT

public:
#ifdef ENABLE_COMMONAPI
    static std::shared_ptr<VehicleDataManagerHelper> &getInstance();

    void init();
    void onVehicleSpeedChanged(uint16_t vehicleSpeed);
    void onEngineSpeedChanged(uint16_t engineSpeed);
    void onFuelLevelChanged(uint8_t fuelLevel);
#endif

private:
    explicit VehicleDataManagerHelper(QObject *parent = Q_NULLPTR);

#ifdef ENABLE_COMMONAPI
private:
    std::shared_ptr< ClusterDataProxy<> > mClusterDataProxy;
#endif
};

#endif // VEHICLEDATAMANAGERHELPER_H
