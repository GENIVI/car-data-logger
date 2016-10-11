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
 * \file VehicleDataClimates.h
*/

#ifndef CLIMATESDEFINE
#define CLIMATESDEFINE

#include "VehicleData.h"

namespace VehicleData
{

namespace Climates
{

// short
// current temperature of the inside vehicle. The unit of value is 0.1°C or 0.1°F. e.g. value 205 means 20.5°C
static const std::string ID_INTERIOR_TEMPERATURE                = "interiortemp";

// short
// current temperature of the outside vehicle. The unit of value is 0.1°C or 0.1°F. e.g. value 205 means 20.5°C
static const std::string ID_EXTERIOR_TEMPERATURE                = "exteriortemp";

// unsigned long
// brightness of the outside vehicle. The unit of value is lux.
static const std::string ID_EXTERIOR_BRIGHTNESS                 = "exteriorbrightness";

// unsigned short
// level of rain intensity.
static const std::string ID_RAIN_SENSOR                         = "rainsensor";

enum RainSensor
{
    RAINSENSOR_NORAIN = 0,
    RAINSENSOR_LEVEL1 = 1,
    RAINSENSOR_LEVEL2 = 2,
    RAINSENSOR_LEVEL3 = 3,
    RAINSENSOR_LEVEL4 = 4,
    RAINSENSOR_LEVEL5 = 5,
    RAINSENSOR_LEVEL6 = 6,
    RAINSENSOR_LEVEL7 = 7,
    RAINSENSOR_LEVEL8 = 8,
    RAINSENSOR_LEVEL9 = 9,
    RAINSENSOR_HEAVIESTRAIN = 10,
};

// unsigned short
// current setting of each wiper.
static const std::string ID_WINDSHIELD_WIPER                    = "windshieldwiper";
static const std::string ID_REAR_WIPER                          = "rearwiper";

enum Wiper
{
    WIPER_OFF = 0,
    WIPER_ONCE = 1,
    WIPER_SLOWEST = 2,
    WIPER_SLOW = 3,
    WIPER_FAST = 4,
    WIPER_FASTEST = 5,
    WIPER_AUTO = 10,
};

// unsigned short
// direction setting of HVAC fan.
static const std::string ID_HVAC_FAN_DIRECTION                  = "hvacfan_direction";

enum HVACFanDirection
{
    HVACFAN_DIRECTION_FRONTPANEL = 1,
    HVACFAN_DIRECTION_FLOORDUCT = 2,
    HVACFAN_DIRECTION_FRONTFLOOR = 3,
    HVACFAN_DIRECTION_DEFROSTERFLOOR = 4,
    HVACFAN_DIRECTION_DEFROSTER = 5,
};

// unsigned short
// level of HVAC fan speed. The range of value is from 0(weakest) to 7(strongest).
static const std::string ID_HVAC_FAN_SPEED                      = "hvacfan_speed";

// short
// 	desired target temperature of the inside vehicle. The unit of value is 0.1°C or 0.1°F. e.g. value 205 means 20.5°C
static const std::string ID_HVAC_FAN_TARGET_TEMPERATURE_DRIVER    = "hvacfan_targettemp_driver";
static const std::string ID_HVAC_FAN_TARGET_TEMPERATURE_PASSENGER = "hvacfan_targettemp_passenger";

// boolean
// 'true' means air conditioner is on. 'false' means it is off.
static const std::string ID_AIR_CONDITIONING                    = "airconditioning";

// boolean
// whether air recirculation system is on or off. 'true' means air recirculation system is on. 'false' means it is off.
static const std::string ID_AIR_RECIRCULATION                   = "airrecirculation";

// boolean
// whether heater is on or off. 'true' means heater is on. 'false' means it is off.
static const std::string ID_HEATER                              = "heater";

// boolean
// whether sync mode is on or off. 'true' means sync mode is on. 'false' means it is off.
static const std::string ID_SYNC                                = "sync";

// boolean
// whether auto mode is on or off. 'true' means auto mode is on. 'false' means it is off.
static const std::string ID_AUTO                                = "auto";

// boolean
// whether defrost per each position is on or off. 'true' means defrost is on. 'false' means it is off.
static const std::string ID_DEFROST_WINDSHIELD                  = "defrost_windshield";
static const std::string ID_DEFROST_REAR_WINDOW                 = "defrost_rearwindow";
static const std::string ID_DEFROST_SIDE_MIRRORS                = "defrost_sidemirrors";

// boolean
// whether steering wheel heater is on or off. 'true' means steering wheel heater is on. 'false' means it is off.
static const std::string ID_STEERING_WHEEL_HEATER               = "steeringwheelheater";

// boolean
// whether seat heater is on or off. 'true' means seat heater is on. 'false' means it is off.
static const std::string ID_SEAT_HEATER                         = "seatheater";

// boolean
// whether seat cooler is on or off. 'true' means seat cooler is on. 'false' means it is off.
static const std::string ID_SEAT_COOLER                         = "seatcooler";

// unsigned short
// percentage of openness per each window. The unit of value is . 0 means it's completely closed, 100% means it's fully opened.
static const std::string ID_WINDOW_DRIVER                       = "window_driver";
static const std::string ID_WINDOW_PASSENGER                    = "window_passenger";
static const std::string ID_WINDOW_REAR_LEFT                    = "window_rearleft";
static const std::string ID_WINDOW_REAR_RIGHT                   = "window_rearright";

// unsigned short
// percentage of openness of sunroof. The unit of value is . 0 means sunroof is completely closed, 100% means it's fully opened.
static const std::string ID_SUNROOF_OPENNESS                    = "sunroof_openness";

// unsigned short
// percentage of current degrees of sunroof tilting. The unit of value is . 0 means sunroof is completely closed, 100% means it's tilted to maximum.
static const std::string ID_SUNROOF_TILT                        = "sunroof_tilt";

// boolean
// whether convertible roof is opened or closed. 'true' means roof is opened. 'false' means it is closed.
static const std::string ID_CONVERTIBLE_ROOF                    = "convertibleroof";

}

}

#endif // CLIMATESDEFINE

