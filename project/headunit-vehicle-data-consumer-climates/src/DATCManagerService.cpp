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
 * \file DATCManagerService.cpp
*/

#include "DATCManagerService.h"
#include "DATCDataHandler.h"
#include "DATCCDLDataHandler.h"
#include "DATCManagerDebug.h"

std::shared_ptr<DATCManagerService> g_datc_manager_service = Q_NULLPTR;

DATCManagerService::DATCManagerService()
{
    DLT_REGISTER_CONTEXT(mContext, "dms", "DATC Manager Service");
    DLT_REGISTER_INJECTION_CALLBACK(mContext, 0xFFF, DATCManagerService::DATCCallback);

    mDataHandler = Q_NULLPTR;

    connect(this, SIGNAL(callBackCommand(QString)), this, SLOT(callbackCommandReceived(QString)));
}

DATCManagerService::~DATCManagerService()
{
    DLT_UNREGISTER_CONTEXT(mContext);
}

std::shared_ptr<DATCManagerService> &DATCManagerService::instance()
{
    if ( g_datc_manager_service == Q_NULLPTR )
    {
        g_datc_manager_service = std::shared_ptr<DATCManagerService> (new DATCManagerService );
    }

    return g_datc_manager_service;
}

void DATCManagerService::finalize()
{
    if ( g_datc_manager_service != Q_NULLPTR )
    {
        g_datc_manager_service = Q_NULLPTR;
    }

    DATCCDLDataHandler::finalize();
}

void DATCManagerService::initService()
{
    if ( mDataHandler == Q_NULLPTR )
    {
        mDataHandler = DataHandlerFactory::instance()->createDataHandler<DATCDataHandler>("DATCCDL");

        if ( mDataHandler != Q_NULLPTR )
        {
            BIND_CALLBACK (mDataHandler, DATCManagerService, TemperatureModeChanged,                   PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, DualModeChanged,                          PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, AutoModeChanged,                          PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, AirConditionerRunChanged,                 PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, HeaterRunChanged,                         PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, InteriorTemperautreChanged,               PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ExteriorTemperatureChanged,               PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, TargetTemperaturesChanged,                PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, FanDirectionsChanged,                     PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, FanSpeedsChanged,                         PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, DefrostsChanged,                          PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, AirRecirculationChanged,                  PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, SteeringWheelHeaterChanged,               PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, SeatHeatersChanged,                       PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, SeatCoolersChanged,                       PLACEHOLDERS(1));

            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseGetSupportedTemperatureRange,     PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseSetTargetTemperature,             PLACEHOLDERS(3));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseGetSupportedFanDirection,         PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseSetFanDirection,                  PLACEHOLDERS(3));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseGetSupportedFanSpeedRange,        PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseSetFanSpeed,                      PLACEHOLDERS(3));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseGetSupportedDefrostTarget,        PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseSetAirRecirculation,              PLACEHOLDERS(2));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseGetSteeringWheelHeaterSupported,  PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseSetSteeringWheelHeater,           PLACEHOLDERS(2));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseGetSeatHeaterSupported,           PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseSetSeatHeater,                    PLACEHOLDERS(3));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseGetSeatCoolerSupported,           PLACEHOLDERS(1));
            BIND_CALLBACK (mDataHandler, DATCManagerService, ResponseSetSeatCooler,                    PLACEHOLDERS(3));

            mDataHandler->initHandler();
        }
        else
        {
            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("create datc data handler failed"));
        }
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler already initialized!!"));
    }
}

void DATCManagerService::requestGetSupportedTemperatureRange(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedTemperatureRangeReply_t _reply)
{
    Q_UNUSED(_client);

    requestGetSupportedTemperatureRange();

    _reply();
}

void DATCManagerService::requestSetTargetTemperature(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, double _temperature, requestSetTargetTemperatureReply_t _reply)
{
    Q_UNUSED(_client);

    requestSetTargetTemperature(_areaType, _temperature);

    _reply();
}

void DATCManagerService::requestSetTargetTemperatureByDelta(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, double _temperatureDelta, requestSetTargetTemperatureByDeltaReply_t _reply)
{
    Q_UNUSED(_client);

    requestSetTargetTemperatureByDelta(_areaType, _temperatureDelta);

    _reply();
}

void DATCManagerService::requestGetSupportedFanDirection(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedFanDirectionReply_t _reply)
{
    Q_UNUSED(_client);

    requestGetSupportedFanDirection();

    _reply();
}

void DATCManagerService::requestGetSupportedFanSpeedRange(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedFanSpeedRangeReply_t _reply)
{
    Q_UNUSED(_client);

    requestGetSupportedFanSpeedRange();

    _reply();
}

void DATCManagerService::requestSetFanSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeed, requestSetFanSpeedReply_t _reply)
{
    Q_UNUSED(_client);

    requestSetFanSpeed( _areaType, _fanSpeed );

    _reply();
}

void DATCManagerService::requestSetFanSpeedByDelta(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeedDelta, requestSetFanSpeedByDeltaReply_t _reply)
{
    Q_UNUSED(_client);

    requestSetFanSpeedByDelta( _areaType, _fanSpeedDelta );

    _reply();
}

void DATCManagerService::requestGetSupportedDefrostTarget(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedDefrostTargetReply_t _reply)
{
    Q_UNUSED(_client);

    requestGetSupportedDefrostTarget();

    _reply();
}

void DATCManagerService::requestGetSteeringWheelHeaterSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSteeringWheelHeaterSupportedReply_t _reply)
{
    Q_UNUSED(_client);

    requestGetSteeringWheelHeaterSupported();

    _reply();
}

void DATCManagerService::requestGetSeatHeaterSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSeatHeaterSupportedReply_t _reply)
{
    Q_UNUSED(_client);

    requestGetSeatHeaterSupported();

    _reply();
}

void DATCManagerService::requestGetSeatCoolerSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSeatCoolerSupportedReply_t _reply)
{
    Q_UNUSED(_client);

    requestGetSeatCoolerSupported();

    _reply();
}






void DATCManagerService::requestGetSupportedTemperatureRange()
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestGetSupportedTemperatureRange();
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestSetTargetTemperature(DATCManagerTypes::EAreaType _areaType, double _temperature)
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestSetTargetTemperature(_areaType, _temperature);
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestSetTargetTemperatureByDelta(DATCManagerTypes::EAreaType _areaType, double _temperatureDelta)
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestSetTargetTemperatureByDelta(_areaType, _temperatureDelta);
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestGetSupportedFanDirection()
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestGetSupportedFanDirection();
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestGetSupportedFanSpeedRange()
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestGetSupportedFanSpeedRange();
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestSetFanSpeed(DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeed)
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestSetFanSpeed(_areaType, _fanSpeed);
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestSetFanSpeedByDelta(DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeedDelta)
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestSetFanSpeedByDelta(_areaType, _fanSpeedDelta);
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestGetSupportedDefrostTarget()
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestGetSupportedDefrostTarget();
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestGetSteeringWheelHeaterSupported()
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestGetSteeringWheelHeaterSupported();
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestGetSeatHeaterSupported()
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestGetSeatHeaterSupported();
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}

void DATCManagerService::requestGetSeatCoolerSupported()
{
    if ( mDataHandler != nullptr )
    {
        mDataHandler->requestGetSeatCoolerSupported();
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initialized!!"));
    }
}





IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, TemperatureModeChanged,                   const DATCManagerTypes::ETemperatureMode & temperatureMode)
{
    if ( getTemperatureModeAttribute() != temperatureMode )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Temperature Mode Changed =>"), DLT_STRING(DebugHelper::toString(temperatureMode)));
    }

    setTemperatureModeAttribute( temperatureMode );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, DualModeChanged,                          const bool & on)
{
    if ( getDualModeAttribute() != on )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Dual Mode Changed =>"), DLT_BOOL(on));
    }

    setDualModeAttribute( on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, AutoModeChanged,                          const bool & on)
{
    if ( getAutoModeAttribute() != on )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Auto Mode Changed =>"), DLT_BOOL(on));
    }

    setAutoModeAttribute( on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, AirConditionerRunChanged,                 const bool & on)
{
    if ( getAirConditionerRunAttribute() != on )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Air Conditioner Run Changed =>"), DLT_BOOL(on));
    }

    setAirConditionerRunAttribute( on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, HeaterRunChanged,                         const bool & on)
{
    if ( getHeaterRunAttribute() != on )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Heater Run Changed =>"), DLT_BOOL(on));
    }

    setHeaterRunAttribute( on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, InteriorTemperautreChanged,               const double & temperature)
{
    if ( getInteriorTemperautreAttribute() != temperature )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Interior Temperature Changed =>"), DLT_FLOAT32(temperature));
    }

    setInteriorTemperautreAttribute( temperature );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ExteriorTemperatureChanged,               const double & temperature)
{
    if ( getExteriorTemperatureAttribute() != temperature )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Exterior Temperature Changed =>"), DLT_FLOAT32(temperature));
    }

    setExteriorTemperatureAttribute( temperature );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, TargetTemperaturesChanged,                const DATCManagerTypes::TargetTemperatures & targetTemperatures)
{
    if ( getTargetTemperaturesAttribute() != targetTemperatures )
    {
        for (size_t i = 0; i < targetTemperatures.size(); i++)
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Target Temperature Changed => "), DLT_STRING(DebugHelper::toString(targetTemperatures[i].getAreaType())), DLT_FLOAT32(targetTemperatures[i].getTemperature()));
        }
    }

    setTargetTemperaturesAttribute( targetTemperatures );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, FanDirectionsChanged,                     const DATCManagerTypes::FanDirections & fanDirections)
{
    if ( getFanDirectionsAttribute() != fanDirections )
    {
        for (size_t i = 0; i < fanDirections.size(); i++)
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Fan Direction Changed => "), DLT_STRING(DebugHelper::toString(fanDirections[i].getAreaType())), DLT_STRING(DebugHelper::toString(fanDirections[i].getFanDirection())));
        }
    }

    setFanDirectionsAttribute( fanDirections );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, FanSpeedsChanged,                         const DATCManagerTypes::FanSpeeds & fanSpeeds)
{
    if ( getFanSpeedsAttribute() != fanSpeeds )
    {
        for (size_t i = 0; i < fanSpeeds.size(); i++)
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Fan Speed Changed => "), DLT_STRING(DebugHelper::toString(fanSpeeds[i].getAreaType())), DLT_INT(fanSpeeds[i].getFanSpeed()));
        }
    }

    setFanSpeedsAttribute( fanSpeeds );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, DefrostsChanged,                          const DATCManagerTypes::Defrosts & defrosts)
{
    if ( getDefrostsAttribute() != defrosts )
    {
        for (size_t i = 0; i < defrosts.size(); i++)
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Defrost Changed => "), DLT_STRING(DebugHelper::toString(defrosts[i].getDefrostTarget())), DLT_BOOL(defrosts[i].getOn()));
        }
    }

    setDefrostsAttribute( defrosts );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, AirRecirculationChanged,                  const bool & on)
{
    if ( getAirRecirculationAttribute() != on )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Air Recirculation Changed =>"), DLT_BOOL(on));
    }

    setAirRecirculationAttribute( on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, SteeringWheelHeaterChanged,               const bool & on)
{
    if ( getSteeringWheelHeaterAttribute() != on )
    {
        DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Steering Wheel Heater Changed =>"), DLT_BOOL(on));
    }

    setSteeringWheelHeaterAttribute( on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, SeatHeatersChanged,                       const DATCManagerTypes::SeatHeaters & seatHeaters)
{
    if ( getSeatHeatersAttribute() != seatHeaters )
    {
        for (size_t i = 0; i < seatHeaters.size(); i++)
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Seat Heater Changed =>"), DLT_STRING(DebugHelper::toString(seatHeaters[i].getAreaType())), DLT_BOOL(seatHeaters[i].getOn()));
        }
    }

    setSeatHeatersAttribute( seatHeaters );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, SeatCoolersChanged,                       const DATCManagerTypes::SeatCoolers & seatCoolers)
{
    if ( getSeatCoolersAttribute() != seatCoolers )
    {
        for (size_t i = 0; i < seatCoolers.size(); i++)
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Seat Coolers Changed =>"), DLT_STRING(DebugHelper::toString(seatCoolers[i].getAreaType())), DLT_BOOL(seatCoolers[i].getOn()));
        }
    }

    setSeatCoolersAttribute( seatCoolers );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseGetSupportedTemperatureRange,     const DATCManagerTypes::TemperatureRange & temperatureRange)
{
    fireResponseGetSupportedTemperatureRangeEvent( temperatureRange );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseSetTargetTemperature,             const DATCManagerTypes::EDatcControlResult & result, const DATCManagerTypes::EAreaType & areaType, const double & temperature)
{
    fireResponseSetTargetTemperatureEvent( result, areaType, temperature);
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseGetSupportedFanDirection,         const DATCManagerTypes::SupportedFanDirectionList & _supportedFanDirectionList)
{
    fireResponseGetSupportedFanDirectionEvent( _supportedFanDirectionList );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseSetFanDirection,                  const DATCManagerTypes::EDatcControlResult & result, const DATCManagerTypes::EAreaType & areaType, const DATCManagerTypes::EHvacFanDirection & fanDirection)
{
    fireResponseSetFanDirectionEvent( result, areaType, fanDirection );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseGetSupportedFanSpeedRange,        const DATCManagerTypes::FanSpeedRange & fanSpeedRange)
{
    fireResponseGetSupportedFanSpeedRangeEvent( fanSpeedRange );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseSetFanSpeed,                      const DATCManagerTypes::EDatcControlResult & result, const DATCManagerTypes::EAreaType & areaType, const uint16_t & fanSpeed)
{
    fireResponseSetFanSpeedEvent( result, areaType, fanSpeed );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseGetSupportedDefrostTarget,        const DATCManagerTypes::SupportedDefrostTargetList & supportedDefrostTargetList)
{
    fireResponseGetSupportedDefrostTargetEvent( supportedDefrostTargetList );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseSetAirRecirculation,              const DATCManagerTypes::EDatcControlResult & result, const bool & on)
{
    fireResponseSetAirRecirculationEvent( result, on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseGetSteeringWheelHeaterSupported,  const bool & steeringWheelHeaterSupported)
{
    fireResponseGetSteeringWheelHeaterSupportedEvent( steeringWheelHeaterSupported );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseSetSteeringWheelHeater,           const DATCManagerTypes::EDatcControlResult & result, const bool & on)
{
    fireResponseSetSteeringWheelHeaterEvent( result, on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseGetSeatHeaterSupported,           const bool & seatHeaterSupported)
{
    fireResponseGetSeatHeaterSupportedEvent( seatHeaterSupported );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseSetSeatHeater,                    const DATCManagerTypes::EDatcControlResult & result, const DATCManagerTypes::EAreaType & areaType, const bool & on)
{
    fireResponseSetSeatHeaterEvent( result, areaType, on );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseGetSeatCoolerSupported,           const bool & seatCoolerSupported)
{
    fireResponseGetSeatCoolerSupportedEvent( seatCoolerSupported );
}

IMPLEMENT_SERVICE_CALLBACK (DATCManagerService, ResponseSetSeatCooler,                    const DATCManagerTypes::EDatcControlResult & result, const DATCManagerTypes::EAreaType & areaType, const bool & on)
{
    fireResponseSetSeatCoolerEvent( result, areaType, on );
}

int DATCManagerService::DATCCallback(u_int32_t service_id, void *data, u_int32_t length)
{
    Q_UNUSED(service_id);

    if ( data == NULL || length == 0 )
    {
        return -1;
    }

    QString command = QString::fromUtf8(static_cast<const char *>(data));

    emit DATCManagerService::instance()->callBackCommand( command );

    return 0;
}

void DATCManagerService::callbackCommandReceived(QString command)
{
    if ( mDataHandler == Q_NULLPTR )
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("DATC data handler is not initalized.. callback is not avaliable"));

        return;
    }

    QStringList list = command.split(",");

    if ( list.size() > 0 )
    {
        if ( list[0] == "help" )
        {
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("available command list"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set temperature unit,<unit> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     CELSIUS = 0"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     FRENHEIT = 1"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set dual mode,<1 or 0> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set auto mode,<1 or 0> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set air condition,<1 or 0> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set heater,<1 or 0> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set interior temperature,<temperature> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set exterior temperature,<temperature> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set target temperature,<driver>,<passenger>,<rear left>,<rear right>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set fan direction,<driver>,<passenger>,<rear left>,<rear right>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     Front panel = 0"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     Floor Duct = 1"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     Front And Floor = 2"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     Defroster And Floor = 3"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     Defroster = 4"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set fan speed,<driver>,<passenger>,<rear left>,<rear right>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     level(0~8)>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set defrost,<driver>,<passenger>,<rear left>,<rear right>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     value is 1 or 0"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set air recirculation,<1 or 0> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set steering wheel heater,<1 or 0> "));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set seat heater,<driver>,<passenger>,<rear left>,<rear right>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     value is 1 or 0"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > set seat cooler,<driver>,<passenger>,<rear left>,<rear right>"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("     value is 1 or 0"));
            DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING(" > get current values"));
        }
        else if ( list[0] == "set temperature unit")
        {
            if ( list.size() == 2 ) TemperatureModeChangedCallback( static_cast<DATCManagerTypes::ETemperatureMode::Literal>( list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set dual mode")
        {
            if ( list.size() == 2 ) DualModeChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set auto mode")
        {
            if ( list.size() == 2 ) AutoModeChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set air condition")
        {
            if ( list.size() == 2 ) AirConditionerRunChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set heater")
        {
            if ( list.size() == 2 ) HeaterRunChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set interior temperature")
        {
            if ( list.size() == 2 ) InteriorTemperautreChangedCallback( list[1].toDouble() );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set exterior temperature")
        {
            if ( list.size() == 2 ) ExteriorTemperatureChangedCallback( list[1].toDouble() );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set target temperature" )
        {
            if ( list.size() == 5 )
            {
                DATCManagerTypes::TargetTemperatures targetTemperatures;

                targetTemperatures.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::DRIVER, list[1].toDouble()));
                targetTemperatures.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::PASSENGER, list[2].toDouble()));
                targetTemperatures.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::REAR_DRIVER, list[3].toDouble()));
                targetTemperatures.push_back(DATCManagerTypes::TargetTemperature(DATCManagerTypes::EAreaType::REAR_PASSENGER, list[4].toDouble()));

                TargetTemperaturesChangedCallback( targetTemperatures );
            }
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set fan direction" )
        {
            if ( list.size() == 5 )
            {
                DATCManagerTypes::FanDirections fanDirections;

                fanDirections.push_back(DATCManagerTypes::FanDirection(DATCManagerTypes::EAreaType::DRIVER, static_cast<DATCManagerTypes::EHvacFanDirection::Literal>(list[1].toInt())) );
                fanDirections.push_back(DATCManagerTypes::FanDirection(DATCManagerTypes::EAreaType::PASSENGER, static_cast<DATCManagerTypes::EHvacFanDirection::Literal>(list[2].toInt())) );
                fanDirections.push_back(DATCManagerTypes::FanDirection(DATCManagerTypes::EAreaType::REAR_DRIVER, static_cast<DATCManagerTypes::EHvacFanDirection::Literal>(list[3].toInt())) );
                fanDirections.push_back(DATCManagerTypes::FanDirection(DATCManagerTypes::EAreaType::REAR_PASSENGER, static_cast<DATCManagerTypes::EHvacFanDirection::Literal>(list[4].toInt())) );

                FanDirectionsChangedCallback( fanDirections );
            }
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set fan speed" )
        {
            if ( list.size() == 5 )
            {
                DATCManagerTypes::FanSpeeds fanSpeeds;

                fanSpeeds.push_back(DATCManagerTypes::FanSpeed(DATCManagerTypes::EAreaType::DRIVER, list[1].toInt()));
                fanSpeeds.push_back(DATCManagerTypes::FanSpeed(DATCManagerTypes::EAreaType::PASSENGER, list[2].toInt()));
                fanSpeeds.push_back(DATCManagerTypes::FanSpeed(DATCManagerTypes::EAreaType::REAR_DRIVER, list[3].toInt()));
                fanSpeeds.push_back(DATCManagerTypes::FanSpeed(DATCManagerTypes::EAreaType::REAR_PASSENGER, list[4].toInt()));

                FanSpeedsChangedCallback( fanSpeeds );
            }
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set defrost" )
        {
            if ( list.size() == 5 )
            {
                DATCManagerTypes::Defrosts defrosts;

                defrosts.push_back(DATCManagerTypes::Defrost(DATCManagerTypes::EDefrostTarget::WIND_SHIELD, static_cast<bool>(list[1].toInt())) );
                defrosts.push_back(DATCManagerTypes::Defrost(DATCManagerTypes::EDefrostTarget::SIDE_MIRROR, static_cast<bool>(list[2].toInt())) );
                defrosts.push_back(DATCManagerTypes::Defrost(DATCManagerTypes::EDefrostTarget::REAR, static_cast<bool>(list[3].toInt())) );
                defrosts.push_back(DATCManagerTypes::Defrost(DATCManagerTypes::EDefrostTarget::WINDOW, static_cast<bool>(list[4].toInt())) );

                DefrostsChangedCallback( defrosts );
            }
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set air recirculation")
        {
            if ( list.size() == 2 ) AirRecirculationChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set steering wheel heater")
        {
            if ( list.size() == 2 ) SteeringWheelHeaterChangedCallback( static_cast<bool>(list[1].toInt()) );
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set seat heater" )
        {
            if ( list.size() == 5 )
            {
                DATCManagerTypes::SeatHeaters seatHeaters;

                seatHeaters.push_back( DATCManagerTypes::SeatHeater(DATCManagerTypes::EAreaType::DRIVER, static_cast<bool>(list[1].toInt())) );
                seatHeaters.push_back( DATCManagerTypes::SeatHeater(DATCManagerTypes::EAreaType::PASSENGER, static_cast<bool>(list[2].toInt())) );
                seatHeaters.push_back( DATCManagerTypes::SeatHeater(DATCManagerTypes::EAreaType::REAR_DRIVER, static_cast<bool>(list[3].toInt())) );
                seatHeaters.push_back( DATCManagerTypes::SeatHeater(DATCManagerTypes::EAreaType::REAR_PASSENGER, static_cast<bool>(list[4].toInt())) );

                SeatHeatersChangedCallback( seatHeaters );
            }
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "set seat cooler" )
        {
            if ( list.size() == 5 )
            {
                DATCManagerTypes::SeatCoolers seatCoolers;

                seatCoolers.push_back(DATCManagerTypes::SeatCooler(DATCManagerTypes::EAreaType::DRIVER, static_cast<bool>(list[1].toInt())) );
                seatCoolers.push_back(DATCManagerTypes::SeatCooler(DATCManagerTypes::EAreaType::PASSENGER, static_cast<bool>(list[2].toInt())) );
                seatCoolers.push_back(DATCManagerTypes::SeatCooler(DATCManagerTypes::EAreaType::REAR_DRIVER, static_cast<bool>(list[3].toInt())) );
                seatCoolers.push_back(DATCManagerTypes::SeatCooler(DATCManagerTypes::EAreaType::REAR_PASSENGER, static_cast<bool>(list[4].toInt())) );

                SeatCoolersChangedCallback( seatCoolers );
            }
            else                    DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("too few parameters.."));
        }
        else if ( list[0] == "get current values" )
        {
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("current values..."));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Temperature Mode :"), DLT_STRING(DebugHelper::toString(getTemperatureModeAttribute())));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Dual Mode :"), DLT_BOOL(getDualModeAttribute()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Auto Mode :"), DLT_BOOL(getAutoModeAttribute()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Air Conditioner Run :"), DLT_BOOL(getAirConditionerRunAttribute()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Heater Run :"), DLT_BOOL(getHeaterRunAttribute()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Interior Temperature :"), DLT_FLOAT32(getInteriorTemperautreAttribute()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Exterior Temperature :"), DLT_FLOAT32(getExteriorTemperatureAttribute()));

            do {
                DATCManagerTypes::FanDirections fanDirections = getFanDirectionsAttribute();

                DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Fan Directions"));

                for (size_t i = 0; i < fanDirections.size(); i++)
                {
                    DLT_LOG(mContext, DLT_LOG_DEBUG,
                            DLT_STRING("    - "),
                            DLT_STRING(DebugHelper::toString(fanDirections[i].getAreaType())),
                            DLT_STRING(":"),
                            DLT_STRING(DebugHelper::toString(fanDirections[i].getFanDirection())));
                }
            } while(0);

            do {
                DATCManagerTypes::FanSpeeds fanSpeeds = getFanSpeedsAttribute();

                DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Fan Speeds"));

                for (size_t i = 0; i < fanSpeeds.size(); i++)
                {
                    DLT_LOG(mContext, DLT_LOG_DEBUG,
                            DLT_STRING("    - "),
                            DLT_STRING(DebugHelper::toString(fanSpeeds[i].getAreaType())),
                            DLT_STRING(":"),
                            DLT_INT(fanSpeeds[i].getFanSpeed()));
                }
            } while(0);

            do {
                DATCManagerTypes::Defrosts defrosts = getDefrostsAttribute();

                DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Defrosts"));

                for (size_t i = 0; i < defrosts.size(); i++)
                {
                    DLT_LOG(mContext, DLT_LOG_DEBUG,
                            DLT_STRING("    - "),
                            DLT_STRING(DebugHelper::toString(defrosts[i].getDefrostTarget())),
                            DLT_STRING(":"),
                            DLT_INT(defrosts[i].getOn()));
                }
            } while(0);

            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Air Recirculation :"), DLT_BOOL(getAirRecirculationAttribute()));
            DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Steering Wheel Heater :"), DLT_BOOL(getSteeringWheelHeaterAttribute()));

            do {
                DATCManagerTypes::SeatHeaters seatHeaters = getSeatHeatersAttribute();

                DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Seat Heaters"));

                for (size_t i = 0; i < seatHeaters.size(); i++)
                {
                    DLT_LOG(mContext, DLT_LOG_DEBUG,
                            DLT_STRING("    - "),
                            DLT_STRING(DebugHelper::toString(seatHeaters[i].getAreaType())),
                            DLT_STRING(":"),
                            DLT_INT(seatHeaters[i].getOn()));
                }
            } while(0);

            do {
                DATCManagerTypes::SeatCoolers seatCoolers = getSeatCoolersAttribute();

                DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(" - Seat Coolers"));

                for (size_t i = 0; i < seatCoolers.size(); i++)
                {
                    DLT_LOG(mContext, DLT_LOG_DEBUG,
                            DLT_STRING("    - "),
                            DLT_STRING(DebugHelper::toString(seatCoolers[i].getAreaType())),
                            DLT_STRING(":"),
                            DLT_INT(seatCoolers[i].getOn()));
                }
            } while(0);
        }
        else
        {
            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("invalid command!! =>"), DLT_STRING(command.toStdString().data()));
        }
    }
}

