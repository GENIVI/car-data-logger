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
 * \file VehicleDataDrivingSafety.h
*/

#ifndef DRIVINGSAFETYDEFINE
#define DRIVINGSAFETYDEFINE

#include "VehicleData.h"

namespace VehicleData
{

namespace DrivingSafety
{

// unsigned short
// status of ABS (Antilock Braking System).
static const std::string ID_ANTILOCK_BREAKING_SYSTEM                = "antilockbrakingsystem";

enum AntilockBreakingSystem
{
    ANTILOCKBRAKINGSYSTEM_AVAILABLE = 1,
    ANTILOCKBRAKINGSYSTEM_IDLE = 2,
    ANTILOCKBRAKINGSYSTEM_ENGAGED = 3,
};

// unsigned short
// status of TCS (Traction Control System).
static const std::string ID_TRACTION_CONTROL_SYSTEM                 = "tractioncontrolsystem";

enum TractionControlSystem
{
    TRACTIONCONTROLSYSTEM_AVAILABLE = 1,
    TRACTIONCONTROLSYSTEM_IDLE = 2,
    TRACTIONCONTROLSYSTEM_ENGAGED = 3,
};

// unsigned short
// status of ESC (Electronic Stability Control).
static const std::string ID_ELECTRONIC_STABILITY_CONTROL            = "electronicstabilitycontrol";

enum ElectronicStabilityControl
{
    ELECTRONICSTABILITYCONTROL_AVAILABLE = 1,
    ELECTRONICSTABILITYCONTROL_IDLE = 2,
    ELECTRONICSTABILITYCONTROL_ENGAGED = 3,
};

// unsigned short
// setting value of desired limit speed of this vehicle. The unit of value is km/h or mph.
static const std::string ID_VEHICLE_TOP_SPEED_LIMIT                 = "vehicletopspeedlimit";

// unsigned short
// status of each airbag.
static const std::string ID_AIRBAG_STATUS_DRIVER                    = "airbagstatus_driver";
static const std::string ID_AIRBAG_STATUS_PASSENGER                 = "airbagstatus_passenger";
static const std::string ID_AIRBAG_STATUS_SIDE                      = "airbagstatus_side";

enum AirbagStatus
{
    AIRBAGSTATUS_ACTIVATE = 1,
    AIRBAGSTATUS_DEACTIVATE = 2,
    AIRBAGSTATUS_DEPLOYMENT = 3,
};

// unsigned short
// status of each door whether it is open or not.
static const std::string ID_DOOR_OPEN_STATUS_DRIVER                 = "dooropenstatus_driver";
static const std::string ID_DOOR_OPEN_STATUS_PASSENGER              = "dooropenstatus_passenger";
static const std::string ID_DOOR_OPEN_STATUS_REAR_LEFT              = "dooropenstatus_rearleft";
static const std::string ID_DOOR_OPEN_STATUS_REAR_RIGHT             = "dooropenstatus_rearright";
static const std::string ID_DOOR_OPEN_STATUS_TRUNK                  = "dooropenstatus_trunk";
static const std::string ID_DOOR_OPEN_STATUS_FUEL_FILTER_CAP        = "dooropenstatus_fuelfiltercap";
static const std::string ID_DOOR_OPEN_STATUS_HOOD                   = "dooropenstatus_hood";

enum DoorOpenStatus
{
    DOOROPENSTATUS_OPEN = 1,
    DOOROPENSTATUS_AJAR = 2,
    DOOROPENSTATUS_CLOSE = 3,
};

// boolean
// 'true' means the door is locked. 'false' means it is unlocked.
static const std::string ID_DOOR_LOCK_STATUS_DRIVER                 = "doorlockstatus_driver";
static const std::string ID_DOOR_LOCK_STATUS_PASSENGER              = "doorlockstatus_passenger";
static const std::string ID_DOOR_LOCK_STATUS_REAR_LEFT              = "doorlockstatus_rearleft";
static const std::string ID_DOOR_LOCK_STATUS_REAR_RIGHT             = "doorlockstatus_rearright";

// boolean
// 'true' means child safety lock is on. 'false' means it is off.
static const std::string ID_CHILD_SAFETY_LOCK                       = "childsafetylock";

// unsigned short
// status of each seat whether it is occupied or not.
static const std::string ID_OCCUPANTS_STATUS_DRIVER                 = "occupantsstatus_driver";
static const std::string ID_OCCUPANTS_STATUS_PASSENGER              = "occupantsstatus_passenger";
static const std::string ID_OCCUPANTS_STATUS_REAR_LEFT              = "occupantsstatus_rearleft";
static const std::string ID_OCCUPANTS_STATUS_REAR_RIGHT             = "occupantsstatus_rearright";

enum OccupantsStatus
{
    OCCUPANTSSTATUS_ADULT = 1,
    OCCUPANTSSTATUS_CHILD = 2,
    OCCUPANTSSTATUS_VACANT = 3,
};

// boolean
// 'true' means the seat belt is fasten. 'false' means it is unfasten.
static const std::string ID_SEAT_BELT_DRIVER                        = "seatbelt_driver";
static const std::string ID_SEAT_BELT_PASSENGER                     = "seatbelt_passenger";
static const std::string ID_SEAT_BELT_REAR_LEFT                     = "seatbelt_rearleft";
static const std::string ID_SEAT_BELT_REAR_RIGHT                    = "seatbelt_rearright";

// boolean
// 'true' means the window is locked. 'false' means it is unlocked.
static const std::string ID_WINDOW_LOCK_DRIVER                      = "windowlock_driver";
static const std::string ID_WINDOW_LOCK_PASSENGER                   = "windowlock_passenger";
static const std::string ID_WINDOW_LOCK_REAR_LEFT                   = "windowlock_rearleft";
static const std::string ID_WINDOW_LOCK_REAR_RIGHT                  = "windowlock_rearright";

// boolean
// 'true' means obstacle distance sensor is activated. 'false' means it is deactivated.
static const std::string ID_OBSTACLE_DISTANCE_SENSOR_STATUS         = "obstacledistance_sensorstatus";

// unsigned short
// distance to a barrier from each sensor position. The unit of value is cm or in.
static const std::string ID_OBSTACLE_DISTANCE_FRONT_CENTER          = "obstacledistance_frontcenter";
static const std::string ID_OBSTACLE_DISTANCE_REAR_CENTER           = "obstacledistance_rearcenter";
static const std::string ID_OBSTACLE_DISTANCE_FRONT_LEFT            = "obstacledistance_frontleft";
static const std::string ID_OBSTACLE_DISTANCE_FRONT_RIGHT           = "obstacledistance_frontright";
static const std::string ID_OBSTACLE_DISTANCE_MIDDLE_LEFT           = "obstacledistance_middleleft";
static const std::string ID_OBSTACLE_DISTANCE_MIDDLE_RIGHT          = "obstacledistance_middleright";
static const std::string ID_OBSTACLE_DISTANCE_REAR_LEFT             = "obstacledistance_rearleft";
static const std::string ID_OBSTACLE_DISTANCE_REAR_RIGHT            = "obstacledistance_rearright";

// boolean
// 'true' means front collision detection is activated. 'false' means it is deactivated.
static const std::string ID_FRONT_COLLISION_DETECTION_STATUS        = "frontcollisiondetection_status";

// unsigned short
// distance to a front barrier from this vehicle. The unit of value is m or feet.
static const std::string ID_FRONT_COLLISION_DETECTION_DISTANCE      = "frontcollisiondetection_distance";

// unsigned short
// estimated remaining time to crash into a front barrier. The unit of value is ms.
static const std::string ID_FRONT_COLLISION_DETECTION_TIME          = "frontcollisiondetection_time";

}

}

#endif // DRIVINGSAFETYDEFINE

