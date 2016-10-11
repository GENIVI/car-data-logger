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
 * \file VechielDataManagerDebug.h
*/

#ifndef VEHICLEDATAMANAGERDEBUG_H
#define VEHICLEDATAMANAGERDEBUG_H

#include <com/ivis/VehicleDataManager/VehicleDataManagerTypes.hpp>
#include <dlt.h>

using namespace v1_0::com::ivis::VehicleDataManager;

namespace DebugHelper
{

const char * toString(VehicleDataManagerTypes::TransmissionGearStatus param);

}

#endif // VEHICLEDATAMANAGERDEBUG_H
