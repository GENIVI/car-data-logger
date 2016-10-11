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
 * \file VehicleDataConsumerCluster.cpp
*/

#include "VehicleDataConsumerCluster.h"
#include <CommonAPI/CommonAPI.hpp>

#include <cdl/interfaces/CDLData.h>
#include <cdl/interfaces/vehicledata/VehicleData.h>
#include <cdl/interfaces/vehicledata/VehicleDataRunningStatus.h>

VehicleDataConsumerCluster * g_vehicle_data_consumer_instance = nullptr;

VehicleDataConsumerCluster * VehicleDataConsumerCluster::instance()
{
    if ( g_vehicle_data_consumer_instance == nullptr )
    {
        g_vehicle_data_consumer_instance = new VehicleDataConsumerCluster;
    }

    return g_vehicle_data_consumer_instance;
}

void VehicleDataConsumerCluster::finalize()
{
    if ( g_vehicle_data_consumer_instance != nullptr )
    {
        delete g_vehicle_data_consumer_instance;
        g_vehicle_data_consumer_instance = nullptr;
    }
}

VehicleDataConsumerCluster::~VehicleDataConsumerCluster()
{
    auto runtime = CommonAPI::Runtime::get();

    runtime->unregisterService("local", ClusterData::getInterface(), ClusterData::getInterface());

    DLT_UNREGISTER_CONTEXT(mContext);
}

VehicleDataConsumerCluster::VehicleDataConsumerCluster()
{
    DLT_REGISTER_CONTEXT(mContext, "vdcs", "Vehicle Data Consumer Service");
    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("Vehicle Data Consumer Service !!"));
//    DLT_REGISTER_CONTEXT_LL_TS(mContext, "vdcs", "Vehicle Data Consumer Service", DLT_LOG_DEBUG, DLT_TRACE_STATUS_OFF);

    initClusterDataService();
    initCDLClientAPI();
}

void VehicleDataConsumerCluster::onCDLData(std::string domain, std::string sub_domain, std::string id, CDL::CDLData data)
{
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("new data!!!"), DLT_STRING(id.data()));
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("new data!!!"), DLT_STRING(id.data()));

    if ( domain == DOMAIN_VEHICLE_DATA && sub_domain == VehicleData::SUB_DOMAIN_RUNNING_STATUS )
    {
        processRunningStatusData(id, data);
    }
}

void VehicleDataConsumerCluster::initClusterDataService()
{
    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("register cluster data service.."));

    mClusterDataService = std::make_shared<ClusterDataStubDefault>();

    auto runtime = CommonAPI::Runtime::get();
    if ( runtime->registerService("local", ClusterData::getInterface(), mClusterDataService) )
    {
        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("register cluster data service done!!"));
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("register cluster data service failed"));
    }
}

void VehicleDataConsumerCluster::initCDLClientAPI()
{
    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("initialize ClientAPI.."));

    if ( CDL::initClientAPI(CDL::RUNTIME_DBUS) == CDL::CDL_OK )
    {
        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("initialize ClientAPI done!!"));

        CDL::registerNotifyCallback( std::bind(&VehicleDataConsumerCluster::onCDLData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4) );

        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("callback for CDL data notification registered!!"));
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("initialize ClientAPI failed"));
    }
}

void VehicleDataConsumerCluster::processRunningStatusData(std::string id, CDL::CDLData & data)
{
    if ( id == VehicleData::RunningStatus::ID_SPEEDOMETER )
    {
        processVehicleSpeedData(data);
    }
    else if ( id == VehicleData::RunningStatus::ID_ENGINE_SPEED )
    {
        processEngineSpeedData(data);
    }
    else if ( id == VehicleData::RunningStatus::ID_FUEL )
    {
        processFuelLevelData(data);
    }
}

void VehicleDataConsumerCluster::processVehicleSpeedData(CDL::CDLData & data)
{
    if ( data.isType<uint16_t>() )
    {
        if ( mClusterDataService != nullptr )
        {
            if ( mClusterDataService->getVehicleSpeedAttribute() != data.get<uint16_t>() )
            {
                DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("Vehicle Speed : "), DLT_UINT16(data.get<uint16_t>()), DLT_STRING(" km/h") );
            }

            mClusterDataService->setVehicleSpeedAttribute( data.get<uint16_t>() );
        }
        else
        {
            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("ClusterDataService is not registered"));
        }
    }
}

void VehicleDataConsumerCluster::processEngineSpeedData(CDL::CDLData & data)
{
    if ( data.isType<uint16_t>() )
    {
        if ( mClusterDataService != nullptr )
        {
            uint16_t engineSpeed;

            if ( data.get<uint16_t>() > 8000 )
            {
                DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("max engine speed is 8000 rpm.."));

                engineSpeed = 8000;
            }
            else
            {
                engineSpeed = data.get<uint16_t>();
            }

            if ( mClusterDataService->getEngineSpeedAttribute() != engineSpeed )
            {
                DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("Engine Speed : "), DLT_UINT16(engineSpeed), DLT_STRING(" RPM") );
            }

            mClusterDataService->setEngineSpeedAttribute( engineSpeed );
        }
        else
        {
            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("ClusterDataService is not registered"));
        }
    }
}

void VehicleDataConsumerCluster::processFuelLevelData(CDL::CDLData & data)
{
    if ( data.isType<uint16_t>() )
    {
        if ( mClusterDataService != nullptr )
        {
            if ( mClusterDataService->getFuelLevelAttribute() != data.get<uint16_t>() )
            {
                DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("Fuel Level : "), DLT_UINT16(data.get<uint16_t>()), DLT_STRING(" %") );
            }

            mClusterDataService->setFuelLevelAttribute( data.get<uint16_t>() );
        }
        else
        {
            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("ClusterDataService is not registered"));
        }
    }
}
