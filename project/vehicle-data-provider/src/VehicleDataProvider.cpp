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
 * \file VehicleDataProvider.cpp
*/

#include "Simulator.h"
#include "VehicleDataProvider.h"

#include <QDebug>
#include <CommonAPI/CommonAPI.hpp>

VehicleDataProvider * g_vehicle_data_provider_instance = NULL;

VehicleDataProvider *VehicleDataProvider::instance()
{
    if ( g_vehicle_data_provider_instance == NULL )
    {
        g_vehicle_data_provider_instance = new VehicleDataProvider;
    }

    return g_vehicle_data_provider_instance;
}

void VehicleDataProvider::finalize()
{
    if ( g_vehicle_data_provider_instance != NULL )
    {
        delete g_vehicle_data_provider_instance;
        g_vehicle_data_provider_instance = NULL;
    }
}

VehicleDataProvider::VehicleDataProvider()
{
    DLT_REGISTER_CONTEXT( mContext, "vedp", "Vehicle Data Provider");

    CDL::initClientAPI( CDL::CDLRuntimeType::RUNTIME_SOMEIP );

    connect( HardWareSimulator::VehicleDataSimulator::instance(), SIGNAL(notifyFuelLevelData(quint16)), this, SLOT(responseNotifyFuelLevelDataParsed(quint16)));
    connect( HardWareSimulator::VehicleDataSimulator::instance(), SIGNAL(notifyVehicleSpeedData(quint16)), this, SLOT(responseNotifyVehicleSpeedDataParsed(quint16)));
    connect( HardWareSimulator::VehicleDataSimulator::instance(), SIGNAL(notifyEngineSpeedData(quint16)), this, SLOT(responseNotifyEngineSpeedDataParsed(quint16)));

    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(airConditionUpdated(bool)), this, SLOT(airConditionUpdated(bool)));
    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(syncModeUpdated(bool)), this, SLOT(syncModeUpdated(bool)));
    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(defrostWindshiledUpdated(bool)), this, SLOT(defrostWindshiledUpdated(bool)));
    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(airIntakeUpdated(bool)), this, SLOT(airIntakeUpdated(bool)));
    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(fanSpeedUpdated(quint8)), this, SLOT(fanSpeedUpdated(quint8)));
    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(fanDirectionUpdated(quint8)), this, SLOT(fanDirectionUpdated(quint8)));
    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(driverTargetTemperatureUpdated(quint16)), this, SLOT(driverTargetTemperatureUpdated(quint16)));
    connect( HardWareSimulator::HVACDataSimulator::instance(), SIGNAL(passengerTargetTemperatureUpdated(quint16)), this, SLOT(passengerTargetTemperatureUpdated(quint16)));
}

VehicleDataProvider::~VehicleDataProvider()
{
    DLT_UNREGISTER_CONTEXT( mContext );
}


/* Vehicle Data */
void VehicleDataProvider::responseNotifyFuelLevelDataParsed(quint16 fuelLevel)
{
    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::RunningStatus::ID_FUEL.data()),
             DLT_STRING("value ="), DLT_UINT16(fuelLevel));

    CDL::storeData( DOMAIN_VEHICLE_DATA,
                    VehicleData::SUB_DOMAIN_RUNNING_STATUS,
                    VehicleData::RunningStatus::ID_FUEL,
                    static_cast<uint16_t>(fuelLevel)
                    );
}

void VehicleDataProvider::responseNotifyVehicleSpeedDataParsed(quint16 vehicleSpeed)
{
    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::RunningStatus::ID_SPEEDOMETER.data()),
             DLT_STRING("value ="), DLT_UINT16(vehicleSpeed));

    CDL::storeData( DOMAIN_VEHICLE_DATA,
                    VehicleData::SUB_DOMAIN_RUNNING_STATUS,
                    VehicleData::RunningStatus::ID_SPEEDOMETER,
                    static_cast<uint16_t>(vehicleSpeed)
                    );
}

void VehicleDataProvider::responseNotifyEngineSpeedDataParsed(quint16 engineSpeed)
{
    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::RunningStatus::ID_ENGINE_SPEED.data()),
             DLT_STRING("value ="), DLT_UINT16(engineSpeed));

    CDL::storeData( DOMAIN_VEHICLE_DATA,
                    VehicleData::SUB_DOMAIN_RUNNING_STATUS,
                    VehicleData::RunningStatus::ID_ENGINE_SPEED,
                    static_cast<uint16_t>(engineSpeed)
                    );
}





/* HVAC Data */
void VehicleDataProvider::syncModeUpdated(bool on)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_SYNC.data()),
             DLT_STRING("value ="), DLT_BOOL(!on));

    // Dual, dual != sync
    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_SYNC, !on);
}

void VehicleDataProvider::airConditionUpdated(bool on)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_AIR_CONDITIONING.data()),
             DLT_STRING("value ="), DLT_BOOL(on));

    // Air Condition
    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_AIR_CONDITIONING, on );
}

void VehicleDataProvider::defrostWindshiledUpdated(bool on)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_DEFROST_WINDSHIELD.data()),
             DLT_STRING("value ="), DLT_BOOL(on));

    // Defost
    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_DEFROST_WINDSHIELD, on );
}

void VehicleDataProvider::airIntakeUpdated(bool on)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_AIR_RECIRCULATION.data()),
             DLT_STRING("value ="), DLT_BOOL(on));

    // Intake
    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_AIR_RECIRCULATION, on );
}

void VehicleDataProvider::fanSpeedUpdated(quint8 speed)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_HVAC_FAN_SPEED.data()),
             DLT_STRING("value ="), DLT_INT(speed));

    // MainBlower
    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_HVAC_FAN_SPEED, static_cast<uint16_t>(speed) );
}

void VehicleDataProvider::fanDirectionUpdated(quint8 direction)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_HVAC_FAN_DIRECTION.data()),
             DLT_STRING("value ="), DLT_INT(direction));

    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_HVAC_FAN_DIRECTION, static_cast<uint16_t>(direction) );
}

void VehicleDataProvider::driverTargetTemperatureUpdated(quint16 temperature)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_HVAC_FAN_TARGET_TEMPERATURE_DRIVER.data()),
             DLT_STRING("value ="), DLT_INT(temperature));

    // Driver
    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_HVAC_FAN_TARGET_TEMPERATURE_DRIVER, static_cast<int16_t>(temperature) );
}

void VehicleDataProvider::passengerTargetTemperatureUpdated(quint16 temperature)
{
    const std::string domain = DOMAIN_VEHICLE_DATA;
    const std::string sub_domain = VehicleData::SUB_DOMAIN_CLIMATE;

    DLT_LOG( mContext, DLT_LOG_DEBUG,
             DLT_STRING("store data to CDL Daemon id ="),
             DLT_STRING(VehicleData::Climates::ID_HVAC_FAN_TARGET_TEMPERATURE_PASSENGER.data()),
             DLT_STRING("value ="), DLT_INT(temperature));

    // Passenger
    CDL::storeData( domain, sub_domain, VehicleData::Climates::ID_HVAC_FAN_TARGET_TEMPERATURE_PASSENGER, static_cast<int16_t>(temperature) );
}
















































