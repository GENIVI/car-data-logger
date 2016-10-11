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
 * \file VehicleDataMaintenance.h
*/

#ifndef MAINTENANCEDEFINE
#define MAINTENANCEDEFINE

#include "VehicleData.h"

namespace VehicleData
{

namespace Maintenance
{

// unsigned long
// current odometer in this vehicle. The unit of value is km or mile.
static const std::string ID_ODOMETER                            = "odometer";

// boolean
// 'true' means the level of transmission oil is low, so should be checked. 'false' means it is normal now.
static const std::string ID_TRANSMISSION_OIL_LIFE_LEVEL         = "transmissionoil_lifelevel";

// short
// current temperature of transmission oil. The unit of value is °C or °F.
static const std::string ID_TRANSMISSON_OIL_TEMPERATURE         = "transmissionoil_temp";

// boolean
// 'true' means the level of brake fluid is low, so should be checked. 'false' means it is normal now.
static const std::string ID_BREAK_FLUID_LEVEL                   = "brakefluidlevel";

// boolean
// 'true' means the level of washer fluid is low, so should be refilled. 'false' means it is normal now.
static const std::string ID_WASHER_FLUID_LEVEL                  = "washerfluidlevel";

// boolean
// 'true' means the indicator lamp is on, the engine should be checked. 'false' means it is normal now.
static const std::string ID_MALFUNCTION_INDICATOR_LAMP          = "malfunctionindicatorlamp";

// unsigned short
// voltage value of battery. The unit of value is V.
static const std::string ID_BATTERY_VOLTAGE                     = "battery_voltage";

// unsigned short
// current value of battery. The unit of value is AH.
static const std::string ID_BATTERY_CURRENT                     = "battery_current";

// unsigned short
// current pressure of each tire. The unit of value is PSI.
static const std::string ID_TIRE_PRESSURE_FRONT_LEFT            = "tirepressure_frontleft";
static const std::string ID_TIRE_PRESSURE_FRONT_RIGHT           = "tirepressure_frontright";
static const std::string ID_TIRE_PRESSURE_REAR_LEFT             = "tirepressure_rearleft";
static const std::string ID_TIRE_PRESSURE_REAR_RIGHT            = "tirepressure_rearright";

// unsigned short
// status of each tire.
static const std::string ID_TIRE_PRESSURE_STATUS_FRONT_LEFT     = "tirepressurestatus_frontleft";
static const std::string ID_TIRE_PRESSURE_STATUS_FRONT_RIGHT    = "tirepressurestatus_frontright";
static const std::string ID_TIRE_PRESSURE_STATUS_REAR_LEFT      = "tirepressurestatus_rearleft";
static const std::string ID_TIRE_PRESSURE_STATUS_REAR_RIGHT     = "tirepressurestatus_rearright";

enum TirePressureStatus
{
    TIREPRESSURESTATUS_NORMAL = 0,
    TIREPRESSURESTATUS_LOW = 1,
    TIREPRESSURESTATUS_HIGH = 2,
};

}

}

#endif // MAINTENANCEDEFINE

