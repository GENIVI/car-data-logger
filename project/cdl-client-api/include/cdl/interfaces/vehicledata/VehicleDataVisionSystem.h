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
 * \file VehicleDataVisionSystem.h
*/

#ifndef VISIONSYSTEM
#define VISIONSYSTEM

#include "VehicleData.h"

namespace VehicleData
{

namespace VisionSystem
{

// boolean
// 'true' means lane departure detection is activated. 'false' means it is deactivated.
static const std::string ID_LANE_DEPARTURE_DETECTION_STATUS         = "lanedeparturedetectionstatus";

// boolean
// 'true' means this vehicle is departed from its lane. 'false' means it is not departed.
static const std::string ID_LANE_DEPARTED                           = "lanedeparted";

}

}

#endif // VISIONSYSTEM

