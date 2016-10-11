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
 * \file DATCManagerDebug.cpp
*/

#include "DATCManagerDebug.h"

namespace DebugHelper
{

const char * toString(DATCManagerTypes::EHvacFanDirection param)
{
	switch ( param )
	{
	case DATCManagerTypes::EHvacFanDirection::FRONT_PANEL:		return "FRONT_PANEL";
	case DATCManagerTypes::EHvacFanDirection::FLOOR_DUCT:		return "FLOOR_DUCT";
	case DATCManagerTypes::EHvacFanDirection::FRONT_AND_FLOOR:		return "FRONT_AND_FLOOR";
	case DATCManagerTypes::EHvacFanDirection::DEFROSTER_AND_FLOOR:		return "DEFROSTER_AND_FLOOR";
	case DATCManagerTypes::EHvacFanDirection::DEFROSTER:		return "DEFROSTER";
	}

	return "Invalid Value";
}

const char * toString(DATCManagerTypes::EAreaType param)
{
	switch ( param )
	{
	case DATCManagerTypes::EAreaType::DRIVER:		return "DRIVER";
	case DATCManagerTypes::EAreaType::PASSENGER:		return "PASSENGER";
	case DATCManagerTypes::EAreaType::REAR_DRIVER:		return "REAR_DRIVER";
	case DATCManagerTypes::EAreaType::REAR_PASSENGER:		return "REAR_PASSENGER";
	}

	return "Invalid Value";
}

const char * toString(DATCManagerTypes::EDefrostTarget param)
{
	switch ( param )
	{
	case DATCManagerTypes::EDefrostTarget::WIND_SHIELD:		return "WIND_SHIELD";
	case DATCManagerTypes::EDefrostTarget::SIDE_MIRROR:		return "SIDE_MIRROR";
	case DATCManagerTypes::EDefrostTarget::REAR:		return "REAR";
	case DATCManagerTypes::EDefrostTarget::WINDOW:		return "WINDOW";
	}

	return "Invalid Value";
}

const char * toString(DATCManagerTypes::ETemperatureMode param)
{
	switch ( param )
	{
	case DATCManagerTypes::ETemperatureMode::CELSIUS:		return "CELSIUS";
	case DATCManagerTypes::ETemperatureMode::FRENHEIT:		return "FRENHEIT";
	}

	return "Invalid Value";
}

const char * toString(DATCManagerTypes::EDatcControlResult param)
{
	switch ( param )
	{
	case DATCManagerTypes::EDatcControlResult::SUCCESS:		return "SUCCESS";
	case DATCManagerTypes::EDatcControlResult::FAIL_RANGE_OUT:		return "FAIL_RANGE_OUT";
	case DATCManagerTypes::EDatcControlResult::FAIL_BUSY:		return "FAIL_BUSY";
	case DATCManagerTypes::EDatcControlResult::FAIL_NO_TARGET:		return "FAIL_NO_TARGET";
	case DATCManagerTypes::EDatcControlResult::FAIL_UNKNOWN:		return "FAIL_UNKNOWN";
	}

	return "Invalid Value";
}

}
