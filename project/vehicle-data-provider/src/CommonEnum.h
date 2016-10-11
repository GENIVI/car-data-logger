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
 * \file CommonEnum.h
*/

#ifndef COMMON_ENUM_H
#define COMMON_ENUM_H

#include <QObject>

class CommonEnum : public QObject
{
    Q_OBJECT

    Q_ENUMS(VEHICLE_DATA_TYPE)
    Q_ENUMS(SIMULATOR_TYPE)
    Q_ENUMS(HVAC_FAN_DIRECTION_TYPE)

public:
    enum SIMULATOR_TYPE{
        VEHICLE_SIMULATOR_TYPE=0,
        HVAC_SIMULATOR_TYPE,

        SIMULATOR_TYPE_MAX
    };

    enum VEHICLE_DATA_TYPE{
        VEHICLE_FUEL_DATA=0,
        VEHICLE_SPEED_DATA,
        VEHICLE_ENGINE_SPEED_DATA,

        VEHICLE_DATA_MAX
    };

    enum HVAC_FAN_DIRECTION_TYPE{
        Air_D_FRONT_PANEL=1,
        Air_D_FRONT_AND_FLOOR,
        Air_D_FLOOR_DUCT,
        Air_D_DEFROSTER_AND_FLOOR,
        Air_D_DEFROSTER,

        Air_MAX
    };
};

#endif // COMMON_ENUM_H
