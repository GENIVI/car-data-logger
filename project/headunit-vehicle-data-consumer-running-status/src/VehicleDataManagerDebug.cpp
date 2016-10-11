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
 * \file VehicleDataManagerDebug.cpp
*/

#include "VehicleDataManagerDebug.h"

namespace DebugHelper
{
const char * toString(VehicleDataManagerTypes::TransmissionGearStatus param)
{
	switch ( param )
	{
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_UNKNOWN:		return "TRANSMISSIONGEARSTATUS_UNKNOWN";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_NEUTRAL:		return "TRANSMISSIONGEARSTATUS_NEUTRAL";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL1:		return "TRANSMISSIONGEARSTATUS_MANUAL1";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL2:		return "TRANSMISSIONGEARSTATUS_MANUAL2";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL3:		return "TRANSMISSIONGEARSTATUS_MANUAL3";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL4:		return "TRANSMISSIONGEARSTATUS_MANUAL4";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL5:		return "TRANSMISSIONGEARSTATUS_MANUAL5";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL6:		return "TRANSMISSIONGEARSTATUS_MANUAL6";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL7:		return "TRANSMISSIONGEARSTATUS_MANUAL7";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL8:		return "TRANSMISSIONGEARSTATUS_MANUAL8";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL9:		return "TRANSMISSIONGEARSTATUS_MANUAL9";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_MANUAL10:		return "TRANSMISSIONGEARSTATUS_MANUAL10";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO1:		return "TRANSMISSIONGEARSTATUS_AUTO1";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO2:		return "TRANSMISSIONGEARSTATUS_AUTO2";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO3:		return "TRANSMISSIONGEARSTATUS_AUTO3";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO4:		return "TRANSMISSIONGEARSTATUS_AUTO4";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO5:		return "TRANSMISSIONGEARSTATUS_AUTO5";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO6:		return "TRANSMISSIONGEARSTATUS_AUTO6";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO7:		return "TRANSMISSIONGEARSTATUS_AUTO7";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO8:		return "TRANSMISSIONGEARSTATUS_AUTO8";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO9:		return "TRANSMISSIONGEARSTATUS_AUTO9";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_AUTO10:		return "TRANSMISSIONGEARSTATUS_AUTO10";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_DRIVE:		return "TRANSMISSIONGEARSTATUS_DRIVE";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_PARKING:		return "TRANSMISSIONGEARSTATUS_PARKING";
	case VehicleDataManagerTypes::TransmissionGearStatus::TRANSMISSIONGEARSTATUS_REVERSE:		return "TRANSMISSIONGEARSTATUS_REVERSE";
	}

	return "Invalid Value";
}

}
