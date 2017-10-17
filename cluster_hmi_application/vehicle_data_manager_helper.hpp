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
#include <QTimer>

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
    enum GEAR_STATE
	{
        PARKING = 0,
        REVERSE,
        NEUTRAL,
        DRIVE,

        MAX_GEAR_STATE,
    };
public:
#ifdef ENABLE_COMMONAPI
    static std::shared_ptr<VehicleDataManagerHelper> &getInstance();

    void init();
    void onVehicleSpeedChanged(int16_t vehicleSpeed);
    void onEngineSpeedChanged(uint16_t engineSpeed);

    void onFuelLevelChanged(uint8_t fuelLevel);
    void onGearStateChanged(int8_t gearState);
    void onAirBagDeployedChanged(bool airBagDeployed);
    void onLowWasherFluidChanged(bool lowWasherFluid);
    void onParkingBrakeEnagedChanged(bool parkingBrakeEngaged);
    void onSeatBeltChanged(bool seatBelted);
    void onFogLightChanged(bool fogLightActive);
    void onHeadLightChanged(bool headLightActive);
    void onHighBeamChanged(bool highBeamActive);
    void onLeftIndicatorChanged(bool leftIndicatorActive);
    void onRightIndicatorChanged(bool rightIndicatorActive);
    void onEngineCoolantTemperatureChanged(int16_t coolantTemperature);

#endif

private:
    explicit VehicleDataManagerHelper(QObject *parent = Q_NULLPTR);

#ifdef ENABLE_COMMONAPI
private:
    std::shared_ptr< ClusterDataProxy<> > mClusterDataProxy;
#endif
};

#endif // VEHICLEDATAMANAGERHELPER_H
