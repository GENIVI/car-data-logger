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
 * \file DATCDataHandler.cpp
*/

#include "DATCDataHandler.h"

DATCDataHandler::DATCDataHandler()
{
    INIT_CALLBACK (TemperatureModeChanged);
    INIT_CALLBACK (DualModeChanged);
    INIT_CALLBACK (AutoModeChanged);
    INIT_CALLBACK (AirConditionerRunChanged);
    INIT_CALLBACK (HeaterRunChanged);
    INIT_CALLBACK (InteriorTemperautreChanged);
    INIT_CALLBACK (ExteriorTemperatureChanged);
    INIT_CALLBACK (TargetTemperaturesChanged);
    INIT_CALLBACK (FanDirectionsChanged);
    INIT_CALLBACK (FanSpeedsChanged);
    INIT_CALLBACK (DefrostsChanged);
    INIT_CALLBACK (AirRecirculationChanged);
    INIT_CALLBACK (SteeringWheelHeaterChanged);
    INIT_CALLBACK (SeatHeatersChanged);
    INIT_CALLBACK (SeatCoolersChanged);

    INIT_CALLBACK (ResponseGetSupportedTemperatureRange);
    INIT_CALLBACK (ResponseSetTargetTemperature);
    INIT_CALLBACK (ResponseGetSupportedFanDirection);
    INIT_CALLBACK (ResponseSetFanDirection);
    INIT_CALLBACK (ResponseGetSupportedFanSpeedRange);
    INIT_CALLBACK (ResponseSetFanSpeed);
    INIT_CALLBACK (ResponseGetSupportedDefrostTarget);
    INIT_CALLBACK (ResponseSetAirRecirculation);
    INIT_CALLBACK (ResponseGetSteeringWheelHeaterSupported);
    INIT_CALLBACK (ResponseSetSteeringWheelHeater);
    INIT_CALLBACK (ResponseGetSeatHeaterSupported);
    INIT_CALLBACK (ResponseSetSeatHeater);
    INIT_CALLBACK (ResponseGetSeatCoolerSupported);
    INIT_CALLBACK (ResponseSetSeatCooler);

    mTemperatureMode = DATCManagerTypes::ETemperatureMode::CELSIUS;

    mTargetTemperatureDriver = 0;
    mTargetTemperaturePassenger = 0;

    mFanDirectionDriver = DATCManagerTypes::EHvacFanDirection::FRONT_PANEL;
    mFanDirectionPassenger = DATCManagerTypes::EHvacFanDirection::FRONT_PANEL;

    mFanSpeedDriver = 0;
    mFanSpeedPassenger = 0;
}

DATCDataHandler::~DATCDataHandler()
{

}

IMPLEMENT_CALLBACK (DATCDataHandler, TemperatureModeChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, DualModeChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, AutoModeChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, AirConditionerRunChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, HeaterRunChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, InteriorTemperautreChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, ExteriorTemperatureChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, TargetTemperaturesChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, FanDirectionsChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, FanSpeedsChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, DefrostsChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, AirRecirculationChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, SteeringWheelHeaterChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, SeatHeatersChanged)
IMPLEMENT_CALLBACK (DATCDataHandler, SeatCoolersChanged)

IMPLEMENT_CALLBACK (DATCDataHandler, ResponseGetSupportedTemperatureRange)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseSetTargetTemperature)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseGetSupportedFanDirection)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseSetFanDirection)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseGetSupportedFanSpeedRange)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseSetFanSpeed)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseGetSupportedDefrostTarget)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseSetAirRecirculation)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseGetSteeringWheelHeaterSupported)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseSetSteeringWheelHeater)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseGetSeatHeaterSupported)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseSetSeatHeater)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseGetSeatCoolerSupported)
IMPLEMENT_CALLBACK (DATCDataHandler, ResponseSetSeatCooler)
