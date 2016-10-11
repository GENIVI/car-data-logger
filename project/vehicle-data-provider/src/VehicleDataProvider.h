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
 * \file VehicleDataProvider.h
*/

#ifndef VEHICLEDATAPROVIDER
#define VEHICLEDATAPROVIDER

#include <QObject>

#include <dlt.h>

#include "com/ivis/ClusterData/ClusterDataStubDefault.hpp"
#include "com/ivis/CDL/ClientAPIRemoteProxy.hpp"

#include "cdl/CDLClientAPI.h"

#include "cdl/interfaces/CDLData.h"
#include "cdl/interfaces/vehicledata/VehicleData.h"
#include "cdl/interfaces/vehicledata/VehicleDataRunningStatus.h"
#include "cdl/interfaces/vehicledata/VehicleDataClimates.h"

using namespace v1::com::ivis::ClusterData;
using namespace v1::com::ivis::CDL;

class VehicleDataProvider : public QObject
{
    Q_OBJECT

public:
    static VehicleDataProvider * instance();
    static void finalize();

private:
    VehicleDataProvider();

public:
    ~VehicleDataProvider();

public slots:
    void responseNotifyFuelLevelDataParsed(quint16 fuelLevel);
    void responseNotifyVehicleSpeedDataParsed(quint16 vehicleSpeed);
    void responseNotifyEngineSpeedDataParsed(quint16 engineSpeed);

public slots:
    void syncModeUpdated(bool on);
    void airConditionUpdated(bool on);
    void defrostWindshiledUpdated(bool on);
    void airIntakeUpdated(bool on);

    void fanSpeedUpdated(quint8 speed);
    void fanDirectionUpdated(quint8 direction);
    void driverTargetTemperatureUpdated(quint16 temperature);
    void passengerTargetTemperatureUpdated(quint16 temperature);

private:
    DLT_DECLARE_CONTEXT(mContext)
};


#endif // VEHICLEDATAPROVIDER

