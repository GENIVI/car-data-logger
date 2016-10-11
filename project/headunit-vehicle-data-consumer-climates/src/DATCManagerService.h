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
 * \file DATCManagerService.h
*/

#ifndef DATCMANAGERSERVICE_H
#define DATCMANAGERSERVICE_H

#include <QObject>
#include <com/ivis/DATCManager/DATCManagerStubDefault.hpp>
#include <dlt.h>
#include "DataHandlerFactory.h"

using namespace v1::com::ivis::DATCManager;

class DATCDataHandler;

class DATCManagerService : public QObject, public DATCManagerStubDefault
{
    Q_OBJECT

private:
    DATCManagerService();

public:
    ~DATCManagerService();

    static std::shared_ptr<DATCManagerService> & instance();
    static void finalize();

public:
    void initService();

public:
    static int DATCCallback(u_int32_t service_id, void *data, u_int32_t length);

signals:
    void callBackCommand(QString command);

public slots:
    void callbackCommandReceived(QString command);

public:
    DECLARE_SERVICE_CALLBACK (TemperatureModeChanged,                   const DATCManagerTypes::ETemperatureMode &);
    DECLARE_SERVICE_CALLBACK (DualModeChanged,                          const bool &);
    DECLARE_SERVICE_CALLBACK (AutoModeChanged,                          const bool &);
    DECLARE_SERVICE_CALLBACK (AirConditionerRunChanged,                 const bool &);
    DECLARE_SERVICE_CALLBACK (HeaterRunChanged,                         const bool &);
    DECLARE_SERVICE_CALLBACK (InteriorTemperautreChanged,               const double &);
    DECLARE_SERVICE_CALLBACK (ExteriorTemperatureChanged,               const double &);
    DECLARE_SERVICE_CALLBACK (TargetTemperaturesChanged,                const DATCManagerTypes::TargetTemperatures &);
    DECLARE_SERVICE_CALLBACK (FanDirectionsChanged,                     const DATCManagerTypes::FanDirections &);
    DECLARE_SERVICE_CALLBACK (FanSpeedsChanged,                         const DATCManagerTypes::FanSpeeds &);
    DECLARE_SERVICE_CALLBACK (DefrostsChanged,                          const DATCManagerTypes::Defrosts &);
    DECLARE_SERVICE_CALLBACK (AirRecirculationChanged,                  const bool &);
    DECLARE_SERVICE_CALLBACK (SteeringWheelHeaterChanged,               const bool &);
    DECLARE_SERVICE_CALLBACK (SeatHeatersChanged,                       const DATCManagerTypes::SeatHeaters &);
    DECLARE_SERVICE_CALLBACK (SeatCoolersChanged,                       const DATCManagerTypes::SeatCoolers &);

    DECLARE_SERVICE_CALLBACK (ResponseGetSupportedTemperatureRange,     const DATCManagerTypes::TemperatureRange &);
    DECLARE_SERVICE_CALLBACK (ResponseSetTargetTemperature,             const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const double &);
    DECLARE_SERVICE_CALLBACK (ResponseGetSupportedFanDirection,         const DATCManagerTypes::SupportedFanDirectionList &);
    DECLARE_SERVICE_CALLBACK (ResponseSetFanDirection,                  const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const DATCManagerTypes::EHvacFanDirection &);
    DECLARE_SERVICE_CALLBACK (ResponseGetSupportedFanSpeedRange,        const DATCManagerTypes::FanSpeedRange &);
    DECLARE_SERVICE_CALLBACK (ResponseSetFanSpeed,                      const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const uint16_t &);
    DECLARE_SERVICE_CALLBACK (ResponseGetSupportedDefrostTarget,        const DATCManagerTypes::SupportedDefrostTargetList &);
    DECLARE_SERVICE_CALLBACK (ResponseSetAirRecirculation,              const DATCManagerTypes::EDatcControlResult &, const bool &);
    DECLARE_SERVICE_CALLBACK (ResponseGetSteeringWheelHeaterSupported,  const bool &);
    DECLARE_SERVICE_CALLBACK (ResponseSetSteeringWheelHeater,           const DATCManagerTypes::EDatcControlResult &, const bool &);
    DECLARE_SERVICE_CALLBACK (ResponseGetSeatHeaterSupported,           const bool &);
    DECLARE_SERVICE_CALLBACK (ResponseSetSeatHeater,                    const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const bool &);
    DECLARE_SERVICE_CALLBACK (ResponseGetSeatCoolerSupported,           const bool &);
    DECLARE_SERVICE_CALLBACK (ResponseSetSeatCooler,                    const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const bool &);

public:
    virtual void requestGetSupportedTemperatureRange(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedTemperatureRangeReply_t _reply);
    virtual void requestSetTargetTemperature(const std::shared_ptr<CommonAPI::ClientId> _client, DATCManagerTypes::EAreaType _areaType, double _temperature, requestSetTargetTemperatureReply_t _reply);
    virtual void requestSetTargetTemperatureByDelta(const std::shared_ptr<CommonAPI::ClientId> _client, DATCManagerTypes::EAreaType _areaType, double _temperatureDelta, requestSetTargetTemperatureByDeltaReply_t _reply);
    virtual void requestGetSupportedFanDirection(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedFanDirectionReply_t _reply);
    virtual void requestGetSupportedFanSpeedRange(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedFanSpeedRangeReply_t _reply);
    virtual void requestSetFanSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeed, requestSetFanSpeedReply_t _reply);
    virtual void requestSetFanSpeedByDelta(const std::shared_ptr<CommonAPI::ClientId> _client, DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeedDelta, requestSetFanSpeedByDeltaReply_t _reply);
    virtual void requestGetSupportedDefrostTarget(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedDefrostTargetReply_t _reply);
    virtual void requestGetSteeringWheelHeaterSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSteeringWheelHeaterSupportedReply_t _reply);
    virtual void requestGetSeatHeaterSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSeatHeaterSupportedReply_t _reply);
    virtual void requestGetSeatCoolerSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSeatCoolerSupportedReply_t _reply);

public:
    virtual void requestGetSupportedTemperatureRange();
    virtual void requestSetTargetTemperature(DATCManagerTypes::EAreaType _areaType, double _temperature);
    virtual void requestSetTargetTemperatureByDelta(DATCManagerTypes::EAreaType _areaType, double _temperatureDelta);
    virtual void requestGetSupportedFanDirection();
    virtual void requestGetSupportedFanSpeedRange();
    virtual void requestSetFanSpeed(DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeed);
    virtual void requestSetFanSpeedByDelta(DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeedDelta);
    virtual void requestGetSupportedDefrostTarget();
    virtual void requestGetSteeringWheelHeaterSupported();
    virtual void requestGetSeatHeaterSupported();
    virtual void requestGetSeatCoolerSupported();

private:
    DLT_DECLARE_CONTEXT(mContext)

    DATCDataHandler * mDataHandler;
};

#endif // DATCMANAGERSERVICE_H
