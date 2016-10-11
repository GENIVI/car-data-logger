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
 * \file VehicleDataPersonalization.h
*/

#ifndef PERSONALIZATIONDEFINE
#define PERSONALIZATIONDEFINE

#include "VehicleData.h"

namespace VehicleData
{

namespace Personalization
{

// string
// string representation of ID of remote control key. It can be used to identify the driver and to apply his personal settings.
static const std::string ID_KEY_ID                                      = "keyid";

// unsigned short
// setting of language used by the system currently.
static const std::string ID_LANGUAGE                                    = "language";

enum Language
{
    LANGUAGE_ENGLISH = 1,
    LANGUAGE_SPANISH = 2,
    LANGUAGE_FRENCH = 3,
};

// boolean
// 'true' means the current measurement system is km(litter). 'false' means it is mile(gallon).
static const std::string ID_MEASUREMENT_SYSTEM                          = "measurementsystem";

// string
// The value is one of both "litter" and "gallon".
static const std::string ID_MEASUREMENT_SYSTEM_STRING_FUEL              = "measurementsystemstring_fuel";

// string
// The value is one of both "km" and "mile".
static const std::string ID_MEASUREMENT_SYSTEM_STRING_DISTANCE          = "measurementsystemstring_distance";

// string
// The value is one of both "km/h" and "mph".
static const std::string ID_MEASUREMENT_SYSTEM_STRING_SPEED             = "measurementsystemstring_speed";

// string
// The value is one of following values: "l/100", "mpg", "km/l".
static const std::string ID_MEASUREMENT_SYSTEM_STRING_CONSUMPTION       = "measurementsystemstring_consumption";

// unsigned short
// The value is 2 bytes compound type where the first byte is tilt value and the last byte is pan value.
static const std::string ID_MIRROR_DRIVER                               = "mirror_driver";
static const std::string ID_MIRROR_PASSENGER                            = "mirror_passenger";
static const std::string ID_MIRROR_INSIDE                               = "mirror_inside";

// unsigned short
// position setting of steering wheel sliding.
static const std::string ID_STEERING_WHEEL_POSITION_SLIDE               = "steeringwheelposition_slide";

// unsigned short
// position setting of steering wheel tilting.
static const std::string ID_STEERING_WHEEL_POSITION_TILT                = "steeringwheelposition_tilt";

// unsigned short
// setting of current driving mode.
static const std::string ID_DRIVING_MODE                                = "drivingmode";

enum DrivingMode
{
    DRIVINGMODE_COMFORT = 1,
    DRIVINGMODE_AUTO = 2,
    DRIVINGMODE_SPORT = 3,
    DRIVINGMODE_ECO = 4,
    DRIVINGMODE_MANUAL = 5,
};

// unsigned short
// position setting of driver seatback reclining.
static const std::string ID_DRIVER_SEAT_POSITION_RECLINE_SEATBACK       = "driverseatposition_reclineseatback";

// unsigned short
// position setting of driver seat sliding.
static const std::string ID_DRIVER_SEAT_POSITION_SLIDE                  = "driverseatposition_slide";

// unsigned short
// height setting of driver seat cushion.
static const std::string ID_DRIVER_SEAT_POSITION_CUSHION_HEIGHT         = "driverseatposition_cushionheight";

// unsigned short
// position setting of driver seat headrest.
static const std::string ID_DRIVER_SEAT_POSITION_HEADREST               = "driverseatposition_headrest";

// unsigned short
// position setting of driver seat back cushion.
static const std::string ID_DRIVER_SEAT_POSITION_BACK_CUSHION           = "driverseatposition_backcushion";

// unsigned short
// position setting of driver seat side cushion.
static const std::string ID_DRIVER_SEAT_POSITION_SIDE_CUSHION           = "driverseatposition_sidecushion";

// unsigned short
// position setting of passenger seatback reclining.
static const std::string ID_PASSENGER_SEAT_POSITION_RECLINE_SEATBACK    = "passengerseatposition_reclineseatback";

// unsigned short
// position setting of passenger seat sliding.
static const std::string ID_PASSENGER_SEAT_POSITION_SLIDE               = "passengerseatposition_slide";

// unsigned short
// height setting of passenger seat cushion.
static const std::string ID_PASSENGER_SEAT_POSITION_CUSHION_HEIGHT      = "passengerseatposition_cushionheight";

// unsigned short
// position setting of passenger seat headrest.
static const std::string ID_PASSENGER_SEAT_POSITION_HEADREST            = "passengerseatposition_headrest";

// unsigned short
// position setting of passenger seat back cushion.
static const std::string ID_PASSENGER_SEAT_POSITION_BACK_CUSHION        = "passengerseatposition_backcushion";

// unsigned short
// position setting of passenger seat side cushion.
static const std::string ID_PASSENGER_SEAT_POSITION_SIDE_CUSHION        = "passengerseatposition_sidecushion";

// unsigned short
// The value 0% means darkest. 100% means brightest.
static const std::string ID_DASHBOARD_ILLUMINATION                      = "dashboardillumination";

// unsigned short
// setting of generated vehicle sound mode. It is usually supported in electric vehicles
static const std::string ID_GENERATED_VEHICLE_SOUND_MODE                = "generatedvehiclesoundmode";

enum GeneratedVehicleSoundMode
{
    GENERATEDVEHICLESOUNDMODE_NORMAL = 1,
    GENERATEDVEHICLESOUNDMODE_QUIET = 2,
    GENERATEDVEHICLESOUNDMODE_SPORTIVE = 3,
};

}

}

#endif // PERSONALIZATIONDEFINE

