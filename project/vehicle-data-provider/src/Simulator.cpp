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
 * \file Simulator.cpp
*/

#include <QDebug>
#include <QtQml>

#include "CommonEnum.h"
#include "Simulator.h"

namespace HardWareSimulator
{

    VehicleDataSimulator * g_vehicle_data_simulator_instance = NULL;

    /* Vehicle Data Simulator */
    VehicleDataSimulator::VehicleDataSimulator() : mFuelLevel(0), mVehicleSpeed(0), mEngineSpeed(0)
    {
        qmlRegisterType<CommonEnum>("define.CommonEnum", 1, 0, "CommonEnum");
    }

    VehicleDataSimulator::~VehicleDataSimulator()
    {

    }

    VehicleDataSimulator *VehicleDataSimulator::instance()
    {
        if( g_vehicle_data_simulator_instance == NULL )
            g_vehicle_data_simulator_instance = new VehicleDataSimulator;

        return g_vehicle_data_simulator_instance;
    }

    void VehicleDataSimulator::finalize()
    {
        if ( g_vehicle_data_simulator_instance != NULL )
        {
            delete g_vehicle_data_simulator_instance;
            g_vehicle_data_simulator_instance = NULL;
        }
    }

    void VehicleDataSimulator::setFuelLevel(quint16 fuelLevel)
    {
        mFuelLevel = fuelLevel;

        emit notifyFuelLevelData(mFuelLevel);
    }

    void VehicleDataSimulator::setVehicleSpeedLevel(quint16 vehicleSpeed)
    {
        mVehicleSpeed = vehicleSpeed;

        emit notifyVehicleSpeedData(mVehicleSpeed);

    }

    void VehicleDataSimulator::setEngineSpeedLevel(quint16 engineSpeed)
    {
        mEngineSpeed = engineSpeed;

        emit notifyEngineSpeedData(mEngineSpeed);
    }








    /* HVAC Data Simulator */
    HVACDataSimulator * g_hvac_data_simulator_instance = NULL;

    HVACDataSimulator::HVACDataSimulator() : mSyncValue(false), mAirCondition(false), mFrontValue(false), mAirIntake(false),
        mFanSpeed(0), mFanDirection(0), mDriverTempC(0), mPassengerTempC(0)
    {

    }

    HVACDataSimulator::~HVACDataSimulator()
    {

    }

    HVACDataSimulator *HVACDataSimulator::instance()
    {
        if( g_hvac_data_simulator_instance == NULL )
            g_hvac_data_simulator_instance = new HVACDataSimulator;

        return g_hvac_data_simulator_instance;
    }

    void HVACDataSimulator::finalize()
    {
        if ( g_hvac_data_simulator_instance != NULL )
        {
            delete g_hvac_data_simulator_instance;
            g_hvac_data_simulator_instance = NULL;
        }
    }

    void HVACDataSimulator::setSyncMode(bool sync)
    {
        mSyncValue = sync;

        emit syncModeUpdated(mSyncValue);
    }

    void HVACDataSimulator::setAirConditionMode(bool airCondition)
    {
        mAirCondition = airCondition;

        emit airConditionUpdated(mAirCondition);
    }


    void HVACDataSimulator::setDefrostWindshiledMode(bool front)
    {
        mFrontValue = front;

        emit defrostWindshiledUpdated(mFrontValue);
    }

    void HVACDataSimulator::setAirIntakeMode(bool airIntake)
    {
        mAirIntake = airIntake;

        emit airIntakeUpdated(mAirIntake);
    }

    void HVACDataSimulator::setFanSpeedLevel(qint8 fanSpeed)
    {
        mFanSpeed = fanSpeed;

        emit fanSpeedUpdated(mFanSpeed);
    }

    void HVACDataSimulator::setFanDirectionMode(qint8 fanDirection)
    {
        mFanDirection = fanDirection;

        emit fanDirectionUpdated(mFanDirection);
    }

    void HVACDataSimulator::setDriverTempC(quint16 drTempC)
    {
        mDriverTempC = drTempC;

        emit driverTargetTemperatureUpdated(mDriverTempC);
    }

    void HVACDataSimulator::setPassengerTempC(quint16 psTempC)
    {
        mPassengerTempC = psTempC;

        emit passengerTargetTemperatureUpdated(mPassengerTempC);
    }
}
