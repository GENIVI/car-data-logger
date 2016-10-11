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
 * \file DATCDataHandler.h
*/

#ifndef DATCDATAHANDLER_H
#define DATCDATAHANDLER_H

#include <QObject>
#include <CommonAPI/CommonAPI.hpp>
#include <com/ivis/DATCManager/DATCManagerTypes.hpp>

#include "DataHandlerFactory.h"
#include <dlt.h>

using namespace v1::com::ivis::DATCManager;

class DATCDataHandler : public IDataHandler
{
public:
    // callbacks for attributes
    DECLARE_CALLBACK (TemperatureModeChanged,                   const DATCManagerTypes::ETemperatureMode &);
    DECLARE_CALLBACK (DualModeChanged,                          const bool &);
    DECLARE_CALLBACK (AutoModeChanged,                          const bool &);
    DECLARE_CALLBACK (AirConditionerRunChanged,                 const bool &);
    DECLARE_CALLBACK (HeaterRunChanged,                         const bool &);
    DECLARE_CALLBACK (InteriorTemperautreChanged,               const double &);
    DECLARE_CALLBACK (ExteriorTemperatureChanged,               const double &);
    DECLARE_CALLBACK (TargetTemperaturesChanged,                const DATCManagerTypes::TargetTemperatures &);
    DECLARE_CALLBACK (FanDirectionsChanged,                     const DATCManagerTypes::FanDirections &);
    DECLARE_CALLBACK (FanSpeedsChanged,                         const DATCManagerTypes::FanSpeeds &);
    DECLARE_CALLBACK (DefrostsChanged,                          const DATCManagerTypes::Defrosts &);
    DECLARE_CALLBACK (AirRecirculationChanged,                  const bool &);
    DECLARE_CALLBACK (SteeringWheelHeaterChanged,               const bool &);
    DECLARE_CALLBACK (SeatHeatersChanged,                       const DATCManagerTypes::SeatHeaters &);
    DECLARE_CALLBACK (SeatCoolersChanged,                       const DATCManagerTypes::SeatCoolers &);

    // callbacks for request response
    DECLARE_CALLBACK (ResponseGetSupportedTemperatureRange,     const DATCManagerTypes::TemperatureRange &);
    DECLARE_CALLBACK (ResponseSetTargetTemperature,             const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const double &);
    DECLARE_CALLBACK (ResponseGetSupportedFanDirection,         const DATCManagerTypes::SupportedFanDirectionList &);
    DECLARE_CALLBACK (ResponseSetFanDirection,                  const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const DATCManagerTypes::EHvacFanDirection &);
    DECLARE_CALLBACK (ResponseGetSupportedFanSpeedRange,        const DATCManagerTypes::FanSpeedRange &);
    DECLARE_CALLBACK (ResponseSetFanSpeed,                      const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const uint16_t &);
    DECLARE_CALLBACK (ResponseGetSupportedDefrostTarget,        const DATCManagerTypes::SupportedDefrostTargetList &);
    DECLARE_CALLBACK (ResponseSetAirRecirculation,              const DATCManagerTypes::EDatcControlResult &, const bool &);
    DECLARE_CALLBACK (ResponseGetSteeringWheelHeaterSupported,  const bool &);
    DECLARE_CALLBACK (ResponseSetSteeringWheelHeater,           const DATCManagerTypes::EDatcControlResult &, const bool &);
    DECLARE_CALLBACK (ResponseGetSeatHeaterSupported,           const bool &);
    DECLARE_CALLBACK (ResponseSetSeatHeater,                    const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const bool &);
    DECLARE_CALLBACK (ResponseGetSeatCoolerSupported,           const bool &);
    DECLARE_CALLBACK (ResponseSetSeatCooler,                    const DATCManagerTypes::EDatcControlResult &, const DATCManagerTypes::EAreaType &, const bool &);

public:
    DATCDataHandler();
    virtual ~DATCDataHandler();

public:
    virtual void initHandler() {}

public:
    virtual void requestGetSupportedTemperatureRange() = 0;
    virtual void requestSetTargetTemperature(const DATCManagerTypes::EAreaType &_areaType, const double &_temperature) = 0;
    virtual void requestSetTargetTemperatureByDelta(const DATCManagerTypes::EAreaType &_areaType, const double &_temperatureDelta) = 0;
    virtual void requestGetSupportedFanDirection() = 0;
    virtual void requestGetSupportedFanSpeedRange() = 0;
    virtual void requestSetFanSpeed(const DATCManagerTypes::EAreaType &_areaType, const uint16_t &_fanSpeed) = 0;
    virtual void requestSetFanSpeedByDelta(const DATCManagerTypes::EAreaType &_areaType, const uint16_t &_fanSpeedDelta) = 0;
    virtual void requestGetSupportedDefrostTarget() = 0;
    virtual void requestGetSteeringWheelHeaterSupported() = 0;
    virtual void requestGetSeatHeaterSupported() = 0;
    virtual void requestGetSeatCoolerSupported() = 0;

protected:
    DATCManagerTypes::ETemperatureMode mTemperatureMode;

    double mTargetTemperatureDriver;
    double mTargetTemperaturePassenger;

    DATCManagerTypes::EHvacFanDirection mFanDirectionDriver;
    DATCManagerTypes::EHvacFanDirection mFanDirectionPassenger;

    quint16 mFanSpeedDriver;
    quint16 mFanSpeedPassenger;
};

#endif // DATCDATAHANDLER_H
