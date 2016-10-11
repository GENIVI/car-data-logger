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
 * \file VehicleDataRunningStatus.h
*/

#ifndef RUNNINGSTATUSDEFINE
#define RUNNINGSTATUSDEFINE

#include "VehicleData.h"

namespace VehicleData
{

namespace RunningStatus
{

// unsigned short
// the current vehicle power mode. It can represents the key position in the key cylinder or any type of power mode in the IVI system.
static const std::string ID_VEHICLE_POWER_MODE              = "vehiclepowermode";

enum VehiclePowerMode
{
    VEHICLEPOWERMODE_OFF = 1,
    VEHICLEPOWERMODE_ACC = 2,
    VEHICLEPOWERMODE_RUN = 3,
    VEHICLEPOWERMODE_IGNITION = 4,
};

// unsigned short
// This attribute contains the current speed of this vehicle. The unit of value is km/h or mph, which can be checked by measurementSystem attribute of PersonalizationEvent.
static const std::string ID_SPEEDOMETER                     = "speedometer";

// unsigned short
// current speed of engine. The unit is RPM.
static const std::string ID_ENGINE_SPEED                    = "enginespeed";

// unsigned short
// current mileage of tripmeter 1. The unit of value is km or mile.
static const std::string ID_TRIP_METER_ONE_MILEAGE          = "tripmeter_1_mileage";

// unsigned short
// current mileage of tripmeter 2. The unit of value is km or mile.
static const std::string ID_TRIP_METER_TWO_MILEAGE          = "tripmeter_2_mileage";

// unsigned short
// current average speed of tripmeter 1. The unit of value is km/h or mph.
static const std::string ID_TRIP_METER_ONE_AVERAGE_SPEED    = "tripmeter_1_averagespeed";

// unsigned short
// current average speed of tripmeter 2. The unit of value is km/h or mph.
static const std::string ID_TRIP_METER_TWO_AVERAGE_SPEED    = "tripmeter_2_averagespeed";

// unsigned long
// current fuel consumption(efficiency) of tripmeter 1. The unit of value is l/100, mpg or km/l.
static const std::string ID_TRIP_METER_ONE_FUEL_CONSUMPTION = "tripmeter_1_fuelconsumption";

// unsigned long
// current fuel consumption(efficiency) of tripmeter 2. The unit of value is l/100, mpg or km/l.
static const std::string ID_TRIP_METER_TWO_FUEL_CONSUMPTION = "tripmeter_2_fuelconsumption";

// unsigned short
// current status of transmission gear.
static const std::string ID_TRANSMISSION_GEAR_STATUS        = "transmissiongearstatus";

enum TransmissionGearStatus
{
    TRANSMISSIONGEARSTATUS_NEUTRAL = 0,
    TRANSMISSIONGEARSTATUS_MANUAL1 = 1,
    TRANSMISSIONGEARSTATUS_MANUAL2 = 2,
    TRANSMISSIONGEARSTATUS_MANUAL3 = 3,
    TRANSMISSIONGEARSTATUS_MANUAL4 = 4,
    TRANSMISSIONGEARSTATUS_MANUAL5 = 5,
    TRANSMISSIONGEARSTATUS_MANUAL6 = 6,
    TRANSMISSIONGEARSTATUS_MANUAL7 = 7,
    TRANSMISSIONGEARSTATUS_MANUAL8 = 8,
    TRANSMISSIONGEARSTATUS_MANUAL9 = 9,
    TRANSMISSIONGEARSTATUS_MANUAL10 = 10,
    TRANSMISSIONGEARSTATUS_AUTO1 = 11,
    TRANSMISSIONGEARSTATUS_AUTO2 = 12,
    TRANSMISSIONGEARSTATUS_AUTO3 = 13,
    TRANSMISSIONGEARSTATUS_AUTO4 = 14,
    TRANSMISSIONGEARSTATUS_AUTO5 = 15,
    TRANSMISSIONGEARSTATUS_AUTO6 = 16,
    TRANSMISSIONGEARSTATUS_AUTO7 = 17,
    TRANSMISSIONGEARSTATUS_AUTO8 = 18,
    TRANSMISSIONGEARSTATUS_AUTO9 = 19,
    TRANSMISSIONGEARSTATUS_AUTO10 = 20,
    TRANSMISSIONGEARSTATUS_DRIVE = 32,
    TRANSMISSIONGEARSTATUS_PARKING = 64,
    TRANSMISSIONGEARSTATUS_REVERSE = 128,
};

// boolean
// 'true' means cruise control is activated. 'false' means it is deactivated.
static const std::string ID_CRUISE_CONTROL_STATUS           = "cruisecontrol_status";

// unsigned short
// setting value of desired speed of cruise control. The unit of value is km/h or mph.
static const std::string ID_CRUISE_CONTROL_SPEED            = "cruisecontrol_speed";

// unsigned short
// current status of wheel brake.
static const std::string ID_WHEEL_BREAK                     = "wheelbrake";

enum WheelBreak
{
    WHEELBRAKE_IDLE = 1,
    WHEELBRAKE_ENGAGED = 2,
    WHEELBRAKE_MALFUNCTION = 3,
};

// boolean
// 'true' means headlight is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_HEAD                   = "lightsstatus_head";

// boolean
// 'true' means headlight is high. 'false' means it is low.
static const std::string ID_LIGHT_STATUS_HIGH_BEEM              = "lightsstatus_highbeam";

// boolean
// 'true' means left turn signal is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_TURN_LEFT              = "lightsstatus_turnleft";

// boolean
// 'true' means right turn signal is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_TURN_RIGHT             = "lightsstatus_turnright";

// boolean
// 'true' means brake light is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_BREAK                  = "lightsstatus_brake";

// boolean
// 'true' means front fog light is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_FOG_FRONT              = "lightsstatus_fogfront";

// boolean
// 'true' means rear fog light is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_FOG_REAR               = "lightsstatus_fogrear";

// boolean
// 'true' means hazard light is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_HAZARD                 = "lightsstatus_hazard";

// boolean
// 'true' means parking light is on. 'false' means it is off.
static const std::string ID_LIGHT_STATUS_PARKING                = "lightsstatus_parking";

// boolean
// 'true' means driver's interior light is on. 'false' means it is off.
static const std::string ID_INTERIOR_LIGHTS_STATUS_DRIVER       = "interiorlightsstatus_driver";

// boolean
// 'true' means passenger's interior light is on. 'false' means it is off.
static const std::string ID_INTERIOR_LIGHTS_STATUS_PASSENGER    = "interiorlightsstatus_passenger";

// boolean
// 'true' means central interior light is on. 'false' means it is off.
static const std::string ID_INTERIOR_LIGHTS_STATUS_CENTER       = "interiorlightsstatus_center";

// boolean
// 'true' means automatic headlight control is activated. 'false' means it is deactivated.
static const std::string ID_AUTOMATIC_HEADLIGHTS                = "automaticheadlights";

// boolean
// 'true' means dynamic highbeam control is activated. 'false' means it is deactivated.
static const std::string ID_DYNAMIC_HIGH_BEEAM                  = "dynamichighbeam";

// boolean
// 'true' means horn is on. 'false' means it is off.
static const std::string ID_HORN                                = "horn";

// boolean
// 'true' means chime is on. 'false' means it is off.
static const std::string ID_CHIME                               = "chime";

// unsigned short
// current percentage of remaining fuel over total capacity. The unit is %.
static const std::string ID_FUEL                                = "fuel";

// unsigned long
// estimated reachable distance with the available fuel. The unit of value is km or mile.
static const std::string ID_ESIMATED_RANGE                      = "estimatedrange";

// unsigned short
// The value 0% means starvation. 100% means normal.
static const std::string ID_ENGINE_OIL_REMAINING                = "engineoil_remaining";

// boolean
// 'true' means engine oil should be changed soon. 'false' means engine oil is normal now.
static const std::string ID_ENGINE_OIL_CHANGE                   = "engineoil_change";

// short
// This attribute contains the current temperature of engine oil. The unit of value is °C or °F.
static const std::string ID_ENGINE_OIL_TEMPERATURE              = "engineoil_temp";

// unsigned short
// level of engine coolant.
static const std::string ID_ENGINE_COOLANT_LEVEL                = "enginecoolant_level";

enum EngineCoolantLevel
{
    ENGINECOOLANTLEVEL_NORMAL = 0,
    ENGINECOOLANTLEVEL_LOW = 1,
};

// short
// current temperature of engine oil coolant. The unit of value is °C or °F.
static const std::string ID_ENGINE_COOLANT_TEMPERATURE          = "enginecoolant_temp";

// short
// current angle of steering wheel. The range of value is from -400 to +400 degrees.
static const std::string ID_STEERING_WHEEL_ANGLE                = "steeringwheelangle";


}

}

#endif // RUNNINGSTATUSDEFINE

