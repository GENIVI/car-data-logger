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
 * \file vehicledatamanagerhelper.cpp
*/

#include "VehicleDataManagerHelper.h"
#include "Cluster.h"
#include <QSharedPointer>

#ifdef ENABLE_COMMONAPI
    std::shared_ptr<VehicleDataManagerHelper> mVehicleDataManagerHelper = Q_NULLPTR;
#endif

Q_LOGGING_CATEGORY(vehicleDataManagerHelper, "cluster.hmi.vehicleDataManagerHelper")

VehicleDataManagerHelper::VehicleDataManagerHelper(QObject *parent) : QObject(parent)
{

}

#ifdef ENABLE_COMMONAPI
std::shared_ptr<VehicleDataManagerHelper> &VehicleDataManagerHelper::getInstance()
{
    if ( mVehicleDataManagerHelper == Q_NULLPTR )
    {
        mVehicleDataManagerHelper = std::shared_ptr<VehicleDataManagerHelper> (new VehicleDataManagerHelper);
        mVehicleDataManagerHelper.get()->init();
    }

    return mVehicleDataManagerHelper;
}

void VehicleDataManagerHelper::init()
{
    qCDebug(vehicleDataManagerHelper) << "";

    auto runtime = CommonAPI::Runtime::get();
    mClusterDataProxy = runtime->buildProxy<ClusterDataProxy>("local", "com.ivis.ClusterData.ClusterData");

    mClusterDataProxy->getVehicleSpeedAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onVehicleSpeedChanged, this, std::placeholders::_1));

    mClusterDataProxy->getEngineSpeedAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onEngineSpeedChanged, this, std::placeholders::_1));

    mClusterDataProxy->getFuelLevelAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onFuelLevelChanged, this, std::placeholders::_1));
}

void VehicleDataManagerHelper::onVehicleSpeedChanged(uint16_t vehicleSpeed)
{
    qCDebug(vehicleDataManagerHelper) << "vehicle speed updated : " << vehicleSpeed << " km/h";

    Cluster::instance()->setSpeed(QVariant(vehicleSpeed));
}

void VehicleDataManagerHelper::onEngineSpeedChanged(uint16_t engineSpeed)
{
    qCDebug(vehicleDataManagerHelper) << "engine speed updated : " << engineSpeed << " RPM";

    Cluster::instance()->setRpm(QVariant(engineSpeed));
}

void VehicleDataManagerHelper::onFuelLevelChanged(uint8_t fuelLevel)
{
    qCDebug(vehicleDataManagerHelper) << "fuel level updated : " << fuelLevel << " %";

    Cluster::instance()->setFuel(QVariant(fuelLevel));
}

void VehicleDataManagerHelper::finalize()
{
    if ( mVehicleDataManagerHelper != Q_NULLPTR )
    {
        mVehicleDataManagerHelper = Q_NULLPTR;
    }
}

#endif
