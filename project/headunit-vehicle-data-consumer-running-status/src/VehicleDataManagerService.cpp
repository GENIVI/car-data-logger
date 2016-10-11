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
 * \file VehicleDataManagerService.cpp
*/

#include "VehicleDataManagerService.h"

#include <dlt.h>
#include "VehicleDataManagerDebug.h"
#include "DataHandlerFactory.h"
#include "VehicleDataHandler.h"

std::shared_ptr<VehicleManagerService> g_vehicle_data_manager_service = Q_NULLPTR;

VehicleManagerService::VehicleManagerService()
{
    mDataHandler = Q_NULLPTR;

    DLT_REGISTER_CONTEXT(mContext, "vdms", "Vehicle Data Manaer Service");
    DLT_REGISTER_INJECTION_CALLBACK(mContext, 0xFFF, VehicleManagerService::VehicleCallback);

    connect(this, SIGNAL(callBackCommand(QString)), this, SLOT(callbackCommandReceived(QString)));
}

VehicleManagerService::~VehicleManagerService()
{
    DLT_UNREGISTER_CONTEXT(mContext);
}

void VehicleManagerService::initService()
{
    if ( mDataHandler == Q_NULLPTR )
    {
        mDataHandler = DataHandlerFactory::instance()->createDataHandler<VehicleDataHandler>("VehicleCDL");

        if ( mDataHandler != Q_NULLPTR )
        {
            BIND_CALLBACK (mDataHandler, VehicleManagerService, VehicleSpeedChanged,           PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, VehicleManagerService, VinChanged,                    PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, VehicleManagerService, TransmissionGearStatusChanged, PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, VehicleManagerService, DrivingRestrictionChanged,     PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, VehicleManagerService, LowFuelWarningChanged,         PLACEHOLDERS(1));

            VehicleSpeedChangedCallback(VehicleDataManagerTypes::VehicleSpeed(0, "km/h"));
            DrivingRestrictionChangedCallback(false);
            TransmissionGearStatusChangedCallback(VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_UNKNOWN);
            VinChangedCallback(std::string());
        }
        else
        {
            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("create vehicle data handler failed"));
        }
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("Vehicle data handler already initialized!!"));
    }
}

std::shared_ptr<VehicleManagerService> &VehicleManagerService::instance()
{
    if ( g_vehicle_data_manager_service == Q_NULLPTR )
    {
        g_vehicle_data_manager_service = std::shared_ptr<VehicleManagerService> (new VehicleManagerService);
    }

    return g_vehicle_data_manager_service;
}

void VehicleManagerService::finalize()
{
    if ( g_vehicle_data_manager_service != Q_NULLPTR )
    {
        g_vehicle_data_manager_service = Q_NULLPTR;
    }
}

IMPLEMENT_SERVICE_CALLBACK (VehicleManagerService, VehicleSpeedChanged,           const VehicleDataManagerTypes::VehicleSpeed & vehicleSpeed)
{
    if ( getVehicleSpeedAttribute().getSpeedometer() != vehicleSpeed.getSpeedometer() )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Vehicle Speed Changed =>"), DLT_INT(vehicleSpeed.getSpeedometer()), DLT_STRING(vehicleSpeed.getVehicleSpeedUnit().data()));
    }

    setVehicleSpeedAttribute( vehicleSpeed );
}

IMPLEMENT_SERVICE_CALLBACK (VehicleManagerService, VinChanged,                    const std::string & vin)
{
    if ( vin != getVinAttribute().data() )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("VIN Changed =>"), DLT_STRING(vin.data()));
    }

    setVinAttribute( vin );
}

IMPLEMENT_SERVICE_CALLBACK (VehicleManagerService, TransmissionGearStatusChanged, const VehicleDataManagerTypes::TransmissionGearStatus & transmissionGearStatus)
{
    if ( getTransmissionGearStatusAttribute() != transmissionGearStatus )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Transmission Gear Status Changed =>"), DLT_STRING(DebugHelper::toString(transmissionGearStatus)));
    }

    setTransmissionGearStatusAttribute( transmissionGearStatus );

}

IMPLEMENT_SERVICE_CALLBACK (VehicleManagerService, DrivingRestrictionChanged,     const bool & drivingRestriction)
{
    if ( getDrivingRestrictionAttribute() != drivingRestriction )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Driving Restriction Changed =>"), DLT_BOOL(drivingRestriction));
    }

    setDrivingRestrictionAttribute( drivingRestriction );
}

IMPLEMENT_SERVICE_CALLBACK (VehicleManagerService, LowFuelWarningChanged,         const bool & lowFuelWarning)
{
    if ( getLowFuelWarningAttribute() != lowFuelWarning )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Low Fuel Warning Changed =>"), DLT_BOOL(lowFuelWarning));
    }

    setLowFuelWarningAttribute( lowFuelWarning );
}


int VehicleManagerService::VehicleCallback(u_int32_t service_id, void *data, u_int32_t length)
{
    Q_UNUSED(service_id);

    if ( data == NULL || length == 0 )
    {
        return -1;
    }

    QString command = QString::fromUtf8(static_cast<const char *>(data));

    emit VehicleManagerService::instance()->callBackCommand( command );

    return 0;
}

void VehicleManagerService::callbackCommandReceived(QString command)
{
    if ( mDataHandler == Q_NULLPTR )
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("Vehicle data handler is not initalized.. callback is not avaliable"));

        return;
    }

    QStringList list = command.split(",");

    if ( list.size() > 0 )
    {
        if(list[0] == "help")
        {
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("available command list"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set gear status,<value>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     UNKNOWN = 0"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     NEUTRAL = 1"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     DRIVE = 22"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     PARKING = 23"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     REVERSE = 24"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set speed,<value>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set vin,<value>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set driving restriction,<1 or 0>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set low fuel warning,<1 or 0>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > get current values"));
        }
        else if(list[0] == "set gear status")
        {
            if ( list.size() == 2 ) TransmissionGearStatusChangedCallback( static_cast<VehicleDataManagerTypes::TransmissionGearStatus::Literal>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if(list[0]=="set speed")
        {
            if ( list.size() == 2 ) VehicleSpeedChangedCallback(VehicleDataManagerTypes::VehicleSpeed(list[1].toInt(), "km/h"));
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if(list[0]=="set vin")
        {
            if ( list.size() == 2 ) VinChangedCallback( list[1].toStdString() );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if(list[0]=="set driving restriction")
        {
            if ( list.size() == 2 ) DrivingRestrictionChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if(list[0]=="set low fuel warning")
        {
            if ( list.size() == 2 ) LowFuelWarningChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if(list[0]=="get current values")
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("current values..."));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("  - Vehicle Speed :"),
                    DLT_INT(getVehicleSpeedAttribute().getSpeedometer()),
                    DLT_STRING(getVehicleSpeedAttribute().getVehicleSpeedUnit().data()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("  - VIN :"), DLT_STRING(getVinAttribute().data()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("  - Transmission Gear Status :"),
                    DLT_STRING(DebugHelper::toString(getTransmissionGearStatusAttribute())));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("  - Driving Restriction :"), DLT_BOOL(getDrivingRestrictionAttribute()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("  - Low Fuel Warning :"), DLT_BOOL(getLowFuelWarningAttribute()));
        }
        else
        {
            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("invalid command!! =>"), DLT_STRING(command.toStdString().data()));
        }
    }
}
