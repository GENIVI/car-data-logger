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
 * \file DATCCDLDataHandler.cpp
*/

#include "DATCCDLDataHandler.h"

#include <com/ivis/CDL/ClientAPILocalDBusProxy.hpp>
#include <cdl/CDLClientAPI.h>
#include <cdl/interfaces/CDLData.h>
#include <cdl/interfaces/vehicledata/VehicleDataClimates.h>
#include <cdl/interfaces/vehicledata/VehicleData.h>
#include <cdl/interfaces/vehicledata/VehicleDataRunningStatus.h>

using namespace v1_0::com::ivis::CDL;

DATCCDLDataHandler * g_datc_cdl_data_handler = Q_NULLPTR;

INITIALIZER(DATCCDLDataHandlerInit)
{
    DataHandlerFactory::instance()->setCreateDataHandlerFunction("DATCCDL", DATCCDLDataHandler::instance);
}

DEINITIALIZER(finalizeDATCCDLDatahandler)
{
    DATCCDLDataHandler::finalize();
}

DATCCDLDataHandler::DATCCDLDataHandler()
{
    DLT_REGISTER_CONTEXT( mContext, "dcdh", "DATC CDL Data Handler" );

    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("DATC Data Handler (CDL) created"));

    CDL::initClientAPI( CDL::CDLRuntimeType::RUNTIME_SOMEIP );
    CDL::registerNotifyCallback( std::bind( &DATCCDLDataHandler::callbackDATCClient, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 ) ) ;

    mTargetTemperatureDriver = 25.0;
    mTargetTemperaturePassenger = 25.0;

    mFanDirectionDriver = DATCManagerTypes::EHvacFanDirection::FRONT_AND_FLOOR;
    mFanDirectionPassenger = DATCManagerTypes::EHvacFanDirection::FRONT_AND_FLOOR;

    mFanSpeedDriver = 1;
    mFanSpeedPassenger = 0;
}

DATCCDLDataHandler::~DATCCDLDataHandler()
{
    DLT_UNREGISTER_CONTEXT(mContext);
}

DATCCDLDataHandler *DATCCDLDataHandler::instance()
{
    if ( g_datc_cdl_data_handler == Q_NULLPTR )
    {
        g_datc_cdl_data_handler = new DATCCDLDataHandler;
    }

    return g_datc_cdl_data_handler;
}

void DATCCDLDataHandler::finalize()
{
    if ( g_datc_cdl_data_handler != Q_NULLPTR )
    {
        delete g_datc_cdl_data_handler;
        g_datc_cdl_data_handler = Q_NULLPTR;
    }
}

void DATCCDLDataHandler::initHandler()
{
    if ( mTargetTemperaturesChangedCallback != nullptr )
    {
        DATCManagerTypes::TargetTemperatures targetTemperature;

        targetTemperature.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::DRIVER, mTargetTemperatureDriver));
        targetTemperature.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::PASSENGER, mTargetTemperaturePassenger));

        mTargetTemperaturesChangedCallback(targetTemperature);
    }

    if ( mFanDirectionsChangedCallback != nullptr )
    {
        DATCManagerTypes::FanDirections fanDirection;

        fanDirection.push_back(DATCManagerTypes::FanDirection(DATCManagerTypes::EAreaType::DRIVER, mFanDirectionDriver));
        fanDirection.push_back(DATCManagerTypes::FanDirection(DATCManagerTypes::EAreaType::PASSENGER, mFanDirectionPassenger));

        mFanDirectionsChangedCallback(fanDirection);
    }

    if ( mFanSpeedsChangedCallback != nullptr )
    {
        DATCManagerTypes::FanSpeeds fanSpeed;

        fanSpeed.push_back(DATCManagerTypes::FanSpeed(DATCManagerTypes::EAreaType::DRIVER, mFanSpeedDriver));
        fanSpeed.push_back(DATCManagerTypes::FanSpeed(DATCManagerTypes::EAreaType::PASSENGER, mFanSpeedPassenger));

        mFanSpeedsChangedCallback(fanSpeed);
    }
}

void DATCCDLDataHandler::callbackDATCClient(std::string _domain, std::string _subDomain, std::string _id, CDL::CDLData _data)
{
    if( _domain != DOMAIN_VEHICLE_DATA )
    {
        return;
    }

    if( _subDomain != VehicleData::SUB_DOMAIN_CLIMATE )
    {
        return;
    }

    DLT_LOG( mContext, DLT_LOG_INFO, DLT_STRING(QString("domain: %1, subdomain: %2, id: %3")
                                                          .arg( QString::fromStdString( _domain ) )
                                                          .arg( QString::fromStdString( _subDomain ) )
                                                          .arg( QString::fromStdString( _id ) ).toLocal8Bit().data()) );

    if( _id == VehicleData::Climates::ID_AIR_CONDITIONING )
    {
        if( _data.isType<bool>() )
        {
            if ( mAirRecirculationChangedCallback != nullptr)
                mAirRecirculationChangedCallback( _data.get<bool>() );
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not an air condition type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_AUTO )
    {
        if( _data.isType<bool>() )
        {
            if ( mAutoModeChangedCallback != nullptr)
                mAutoModeChangedCallback( _data.get<bool>() );
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not an auto mode type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_SYNC )
    {
        if( _data.isType<bool>() )
        {
            if ( mDualModeChangedCallback != nullptr)
                mDualModeChangedCallback( !(_data.get<bool>()) );
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a sync type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_DEFROST_WINDSHIELD )
    {
        if( _data.isType<bool>() )
        {
            if ( mDefrostsChangedCallback != nullptr )
            {
                DATCManagerTypes::Defrosts defrost;

                defrost.push_back(DATCManagerTypes::Defrost(DATCManagerTypes::EDefrostTarget::WIND_SHIELD, _data.get<bool>()));

                mDefrostsChangedCallback(defrost);
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a defrost windshield type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_AIR_RECIRCULATION )
    {
        if( _data.isType<bool>() )
        {
            if ( mAirRecirculationChangedCallback != nullptr )
            {
                mAirRecirculationChangedCallback( _data.get<bool>() );
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not an air recirculation type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_HVAC_FAN_SPEED )
    {
        if( _data.isType<uint16_t>() )
        {
            if ( mFanSpeedsChangedCallback != nullptr )
            {
                DATCManagerTypes::FanSpeeds fanSpeed;

                fanSpeed.push_back(DATCManagerTypes::FanSpeed(DATCManagerTypes::EAreaType::DRIVER, _data.get<uint16_t>()) );

                mFanSpeedsChangedCallback(fanSpeed);
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a fan speed type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_HVAC_FAN_DIRECTION )
    {
        if( _data.isType<uint16_t>() )
        {
            if ( mFanDirectionsChangedCallback != nullptr )
            {
                DATCManagerTypes::EHvacFanDirection fanDirection;
                DATCManagerTypes::FanDirections fanDirections;

                if ( _data.get<uint16_t>()== 0x01 )
                {
                    fanDirection = DATCManagerTypes::EHvacFanDirection::FRONT_PANEL;
                }
                else if ( _data.get<uint16_t>()== 0x02 )
                {
                    fanDirection = DATCManagerTypes::EHvacFanDirection::FRONT_AND_FLOOR;
                }
                else if ( _data.get<uint16_t>()== 0x03 )
                {
                    fanDirection = DATCManagerTypes::EHvacFanDirection::FLOOR_DUCT;
                }
                else if ( _data.get<uint16_t>()== 0x04 )
                {
                    fanDirection = DATCManagerTypes::EHvacFanDirection::DEFROSTER_AND_FLOOR;
                }
                else if ( _data.get<uint16_t>()== 0x05 )
                {
                    fanDirection = DATCManagerTypes::EHvacFanDirection::DEFROSTER;
                }
                else
                {
                    return;
                }

                fanDirections.push_back(DATCManagerTypes::FanDirection(DATCManagerTypes::EAreaType::DRIVER, fanDirection) );

                mFanDirectionsChangedCallback(fanDirections);
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a fan direction type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_HEATER )
    {
        if( _data.isType<bool>() )
        {
            if ( mHeaterRunChangedCallback != nullptr )
            {
                mHeaterRunChangedCallback( _data.get<bool>() );
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a heater type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_HVAC_FAN_TARGET_TEMPERATURE_DRIVER )
    {
        if( _data.isType<int16_t>() )
        {
            mTargetTemperatureDriver = static_cast<double>(_data.get<int16_t>()) * 0.1;

            if ( mTargetTemperaturesChangedCallback != nullptr )
            {
                DATCManagerTypes::TargetTemperatures targetTemperature;

                targetTemperature.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::DRIVER, mTargetTemperatureDriver));
                targetTemperature.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::PASSENGER, mTargetTemperaturePassenger));

                mTargetTemperaturesChangedCallback(targetTemperature);
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a driver temperature type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_HVAC_FAN_TARGET_TEMPERATURE_PASSENGER )
    {
        if( _data.isType<int16_t>() )
        {
            mTargetTemperaturePassenger = static_cast<double>(_data.get<int16_t>()) * 0.1;

            if ( mTargetTemperaturesChangedCallback != nullptr )
            {
                DATCManagerTypes::TargetTemperatures targetTemperature;

                targetTemperature.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::DRIVER, mTargetTemperatureDriver));
                targetTemperature.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::PASSENGER, mTargetTemperaturePassenger));

                mTargetTemperaturesChangedCallback(targetTemperature);
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a passenger temperature type. return") );
            return;
        }
    }
    else if( _id == VehicleData::Climates::ID_EXTERIOR_TEMPERATURE )
    {
        if( _data.isType<int16_t>() )
        {
            if ( mExteriorTemperatureChangedCallback != nullptr )
            {
                mExteriorTemperatureChangedCallback( static_cast<double>(_data.get<int16_t>()) * 0.1 );
            }
        }
        else
        {
            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("not a exterior temperature type. return") );
            return;
        }
    }
    else
    {
        DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("incorrect data id. return") );
        return;
    }
}


void DATCCDLDataHandler::requestGetSupportedTemperatureRange()
{
    if ( mResponseGetSupportedTemperatureRangeCallback != nullptr )
    {
        mResponseGetSupportedTemperatureRangeCallback(DATCManagerTypes::TemperatureRange(15.0, 32.0));
    }
}

void DATCCDLDataHandler::requestSetTargetTemperature(const DATCManagerTypes::EAreaType &_areaType, const double &_temperature)
{
    if ( mResponseSetTargetTemperatureCallback != nullptr )
    {
        mResponseSetTargetTemperatureCallback(DATCManagerTypes::EDatcControlResult::FAIL_UNKNOWN, _areaType, _temperature);
    }
}

void DATCCDLDataHandler::requestSetTargetTemperatureByDelta(const DATCManagerTypes::EAreaType &_areaType, const double &_temperatureDelta)
{
    if ( mResponseSetTargetTemperatureCallback != nullptr )
    {
        mResponseSetTargetTemperatureCallback(DATCManagerTypes::EDatcControlResult::FAIL_UNKNOWN, _areaType, _temperatureDelta);
    }
}

void DATCCDLDataHandler::requestGetSupportedFanDirection()
{
    if ( mResponseGetSupportedFanDirectionCallback != nullptr )
    {
        DATCManagerTypes::SupportedFanDirectionList supportedFanDirectionList;

        supportedFanDirectionList.push_back(DATCManagerTypes::EHvacFanDirection::FRONT_PANEL);
        supportedFanDirectionList.push_back(DATCManagerTypes::EHvacFanDirection::FLOOR_DUCT);
        supportedFanDirectionList.push_back(DATCManagerTypes::EHvacFanDirection::FRONT_AND_FLOOR);
        supportedFanDirectionList.push_back(DATCManagerTypes::EHvacFanDirection::DEFROSTER_AND_FLOOR);
        supportedFanDirectionList.push_back(DATCManagerTypes::EHvacFanDirection::DEFROSTER);

        mResponseGetSupportedFanDirectionCallback(supportedFanDirectionList);
    }
}

void DATCCDLDataHandler::requestGetSupportedFanSpeedRange()
{
    if ( mResponseGetSupportedFanSpeedRangeCallback != nullptr )
    {
        mResponseGetSupportedFanSpeedRangeCallback(DATCManagerTypes::FanSpeedRange(0, 8));
    }
}

void DATCCDLDataHandler::requestSetFanSpeed(const DATCManagerTypes::EAreaType &_areaType, const uint16_t &_fanSpeed)
{
    if ( mResponseSetFanSpeedCallback != nullptr )
    {
        mResponseSetFanSpeedCallback(DATCManagerTypes::EDatcControlResult::FAIL_UNKNOWN, _areaType, _fanSpeed);
    }
}

void DATCCDLDataHandler::requestSetFanSpeedByDelta(const DATCManagerTypes::EAreaType &_areaType, const uint16_t &_fanSpeedDelta)
{
    if ( mResponseSetFanSpeedCallback != nullptr )
    {
        mResponseSetFanSpeedCallback(DATCManagerTypes::EDatcControlResult::FAIL_UNKNOWN, _areaType, _fanSpeedDelta);
    }
}

void DATCCDLDataHandler::requestGetSupportedDefrostTarget()
{
    if ( mResponseGetSupportedDefrostTargetCallback != nullptr )
    {
        DATCManagerTypes::SupportedDefrostTargetList supportedDefrostTargetList;

        supportedDefrostTargetList.push_back(DATCManagerTypes::EDefrostTarget::WIND_SHIELD);

        mResponseGetSupportedDefrostTargetCallback(supportedDefrostTargetList);
    }
}

void DATCCDLDataHandler::requestGetSteeringWheelHeaterSupported()
{
    if ( mResponseGetSteeringWheelHeaterSupportedCallback != nullptr )
    {
        mResponseGetSteeringWheelHeaterSupportedCallback(false);
    }
}

void DATCCDLDataHandler::requestGetSeatHeaterSupported()
{
    if ( mResponseGetSeatHeaterSupportedCallback != nullptr )
    {
        mResponseGetSeatHeaterSupportedCallback(false);
    }
}

void DATCCDLDataHandler::requestGetSeatCoolerSupported()
{
    if ( mResponseGetSeatCoolerSupportedCallback != nullptr )
    {
        mResponseGetSeatCoolerSupportedCallback(false);
    }
}



/*
 *  UNUSED SET ATTR FUNC
 *
    virtual void setTemperatureModeAttribute(::v1_0::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode _value);
    virtual void setInteriorTemperautreAttribute(double _value);
    virtual void setSteeringWheelHeaterAttribute(bool _value);
    virtual void setSeatHeatersAttribute(::v1_0::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters _value);
    virtual void setSeatCoolersAttribute(::v1_0::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers _value);
*/
