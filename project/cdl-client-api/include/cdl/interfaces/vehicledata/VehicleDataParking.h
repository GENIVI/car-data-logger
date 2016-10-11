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
 * \file VehicleDataParking.h
*/

#ifndef PARKINGDEFINE
#define PARKINGDEFINE

#include "VehicleData.h"

namespace VehicleData
{

namespace Parking
{

// unsigned short
// status of security alert.
static const std::string ID_SECURITY_ALERT              = "securityalert";

enum SecurityAlert
{
    SECURITYALERT_AVAILABLE = 1,
    SECURITYALERT_IDLE = 2,
    SECURITYALERT_ACTIVATED = 3,
    SECURITYALERT_ALARM_DETECTED = 4,
};

// boolean
// 'true' means parking brake is engaged. 'false' means it is not engaged.
static const std::string ID_PARKING_BREAK               = "parkingbrake";

// boolean
// 'true' means parking light is activated. 'false' means it is deactivated.
static const std::string ID_PARKING_LIGHTS              = "parkinglights";

}

}

#endif // PARKINGDEFINE

