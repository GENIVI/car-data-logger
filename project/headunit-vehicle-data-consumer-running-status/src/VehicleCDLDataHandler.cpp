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
 * \file VehicleCDLDataHandler.cpp
*/

#include "VehicleCDLDataHandler.h"

#include <cdl/CDLClientAPI.h>

#include <com/ivis/CDL/ClientAPILocalDBusProxy.hpp>
#include <com/ivis/VehicleDataManager/VehicleDataManagerTypes.hpp>

#include <cdl/interfaces/CDLData.h>
#include <cdl/interfaces/vehicledata/VehicleDataRunningStatus.h>

using namespace v1_0::com::ivis::CDL;
using namespace v1_0::com::ivis::VehicleDataManager;

VehicleCDLDataHandler* g_VehicleDataClient = nullptr;

INITIALIZER(VehicleCDLDataHandlerInit)
{
    DataHandlerFactory::instance()->setCreateDataHandlerFunction("VehicleCDL", VehicleCDLDataHandler::instance);
}

DEINITIALIZER(finalizeVehicleCDLDatahandler)
{
    VehicleCDLDataHandler::finalize();
}

VehicleCDLDataHandler::VehicleCDLDataHandler()
{
    DLT_REGISTER_CONTEXT( mContext, "vcdh", "Vehicle CDL Data Handler" );

    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("Vehicle Data Handler (CDL) created"));

    CDL::initClientAPI( CDL::CDLRuntimeType::RUNTIME_SOMEIP );
    CDL::registerNotifyCallback( std::bind( &VehicleCDLDataHandler::callbackVehicleClient, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 ) ) ;
}

VehicleCDLDataHandler::~VehicleCDLDataHandler()
{
    DLT_UNREGISTER_CONTEXT(mContext);
}

VehicleCDLDataHandler *VehicleCDLDataHandler::instance()
{
    if ( g_VehicleDataClient == nullptr )
    {
        g_VehicleDataClient = new VehicleCDLDataHandler();
    }

    return g_VehicleDataClient;
}

void VehicleCDLDataHandler::finalize()
{
    if ( g_VehicleDataClient != Q_NULLPTR )
    {
        delete g_VehicleDataClient;
        g_VehicleDataClient = Q_NULLPTR;
    }
}

void VehicleCDLDataHandler::callbackVehicleClient(std::string _domain, std::string _subDomain, std::string _id, CDL::CDLData _data)
{
    if( _domain != DOMAIN_VEHICLE_DATA )
    {
        return;
    }

    if( _subDomain != VehicleData::SUB_DOMAIN_RUNNING_STATUS )
    {
        return;
    }

    if( _id == VehicleData::RunningStatus::ID_SPEEDOMETER )
    {
        if( _data.isType<uint16_t>() )
        {
            if ( mVehicleSpeedChangedCallback != nullptr )
            {
                mVehicleSpeedChangedCallback( VehicleDataManagerTypes::VehicleSpeed( _data.get<uint16_t>(), "km/h" ) );
            }

            if ( mDrivingRestrictionChangedCallback != nullptr )
            {
                if ( _data.get<uint16_t>() > 20 )   mDrivingRestrictionChangedCallback( true );
                else                                mDrivingRestrictionChangedCallback( false );
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_WARN, DLT_STRING("not a speed type. return") );
            return;
        }
    }
    else if( _id == VehicleData::RunningStatus::ID_FUEL )
    {
        if( _data.isType<uint16_t>() )
        {
            if ( mLowFuelWarningChangedCallback != nullptr )
            {
                if ( _data.get<uint16_t>() <= 10 )  mLowFuelWarningChangedCallback( true );
                else                                mLowFuelWarningChangedCallback( false );
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a fuel gauge type. return") );
            return;
        }
    }
}

