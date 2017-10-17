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

#include "vehicle_data_manager_helper.hpp"
#include "cluster.hpp"
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
    if (!mVehicleDataManagerHelper)
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
    mClusterDataProxy = runtime->buildProxy<ClusterDataProxy>("local", ClusterData::getInterface());

    mClusterDataProxy->getVehicleSpeedAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onVehicleSpeedChanged, this, std::placeholders::_1));

    mClusterDataProxy->getEngineSpeedAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onEngineSpeedChanged, this, std::placeholders::_1));

    mClusterDataProxy->getFuelLevelAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onFuelLevelChanged, this, std::placeholders::_1));

    mClusterDataProxy->getGearStateAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onGearStateChanged, this, std::placeholders::_1));

    mClusterDataProxy->getAirBagDeployedAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onAirBagDeployedChanged, this, std::placeholders::_1));

    mClusterDataProxy->getLowWasherFluidAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onLowWasherFluidChanged, this, std::placeholders::_1));

    mClusterDataProxy->getParkingBrakeAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onParkingBrakeEnagedChanged, this, std::placeholders::_1));

    mClusterDataProxy->getSeatBeltActiveAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onSeatBeltChanged, this, std::placeholders::_1));

    mClusterDataProxy->getFogLightAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onFogLightChanged, this, std::placeholders::_1));

    mClusterDataProxy->getHeadLightAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onHeadLightChanged, this, std::placeholders::_1));

    mClusterDataProxy->getHighBeamAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onHighBeamChanged, this, std::placeholders::_1));

    mClusterDataProxy->getLeftIndicatorAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onLeftIndicatorChanged, this, std::placeholders::_1));

    mClusterDataProxy->getRightIndicatorAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onRightIndicatorChanged, this, std::placeholders::_1));

    mClusterDataProxy->getEngineCoolantTemperatureAttribute().getChangedEvent().subscribe(
                std::bind(&VehicleDataManagerHelper::onEngineCoolantTemperatureChanged, this, std::placeholders::_1));
}

void VehicleDataManagerHelper::onVehicleSpeedChanged(int16_t vehicleSpeed)
{
    Cluster::instance().data()->setSpeed(QVariant(vehicleSpeed));
}

void VehicleDataManagerHelper::onEngineSpeedChanged(uint16_t engineSpeed)
{
    Cluster::instance().data()->setRpm(QVariant(engineSpeed));
}

void VehicleDataManagerHelper::onFuelLevelChanged(uint8_t fuelLevel)
{
    Cluster::instance().data()->setFuel(QVariant(fuelLevel));
}

void VehicleDataManagerHelper::onGearStateChanged(int8_t gearState)
{
    Cluster::instance().data()->setGearState(gearState);
}

void VehicleDataManagerHelper::onAirBagDeployedChanged(bool airBagDeployed)
{
    Cluster::instance().data()->setAirBagDeployed(QVariant(airBagDeployed));
}

void VehicleDataManagerHelper::onLowWasherFluidChanged(bool lowWasherFluid)
{
    Cluster::instance().data()->setLowWasherFluid(QVariant(lowWasherFluid));
}

void VehicleDataManagerHelper::onParkingBrakeEnagedChanged(bool parkingBrakeEngaged)
{
    Cluster::instance().data()->setParkingBrakeEnaged(QVariant(parkingBrakeEngaged));
}

void VehicleDataManagerHelper::onSeatBeltChanged(bool seatBelted)
{
    Cluster::instance().data()->setSeatBelt(QVariant(seatBelted));
}

void VehicleDataManagerHelper::onFogLightChanged(bool fogLightActive)
{
    Cluster::instance().data()->setFogLight(QVariant(fogLightActive));
}

void VehicleDataManagerHelper::onHeadLightChanged(bool headLightActive)
{
    Cluster::instance().data()->setHeadLight(QVariant(headLightActive));
}

void VehicleDataManagerHelper::onHighBeamChanged(bool highBeamActive)
{
    Cluster::instance().data()->setHighBeam(QVariant(highBeamActive));
}

void VehicleDataManagerHelper::onLeftIndicatorChanged(bool leftIndicatorActive)
{
    Cluster::instance().data()->setLeftIndicator(QVariant(leftIndicatorActive));
}

void VehicleDataManagerHelper::onRightIndicatorChanged(bool rightIndicatorActive)
{
    Cluster::instance().data()->setRightIndicator(QVariant(rightIndicatorActive));
}

void VehicleDataManagerHelper::onEngineCoolantTemperatureChanged(int16_t coolantTemperature)
{
    Cluster::instance().data()->setEngineCoolantTemperature(QVariant(coolantTemperature));
}

#endif
