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
 * \file ModeManagerDebug.cpp
*/

#include "ModeManagerDebug.h"

namespace DebugHelper
{

const char * toString(ModeManagerTypes::DeviceType param)
{

    switch ( param )
    {
    case ModeManagerTypes::DeviceType::USB:               return "DeviceType::USB";
    case ModeManagerTypes::DeviceType::IPOD:              return "DeviceType::IPOD";
    case ModeManagerTypes::DeviceType::BLUETOOTH:         return "DeviceType::BLUETOOTH";
    case ModeManagerTypes::DeviceType::AUX:               return "DeviceType::AUX";
    }

    return "Invalid Value";
}

const char * toString(ModeManagerTypes::ApplicationType param)
{
    switch ( param )
    {
    case ModeManagerTypes::ApplicationType::APP_NONE:           return "APP_NONE";
    case ModeManagerTypes::ApplicationType::APP_FM:             return "APP_FM";
    case ModeManagerTypes::ApplicationType::APP_AM:             return "APP_AM";
    case ModeManagerTypes::ApplicationType::APP_USB:            return "APP_USB";
    case ModeManagerTypes::ApplicationType::APP_IPOD:           return "APP_IPOD";
    case ModeManagerTypes::ApplicationType::APP_BLUETOOTH:      return "APP_BLUETOOTH";
    case ModeManagerTypes::ApplicationType::APP_AUX:            return "APP_AUX";
    }

    return "Invalid Value";
}

const char * toString(ModeManagerTypes::SubApplicationType param)
{
    switch ( param )
    {
    case ModeManagerTypes::SubApplicationType::SUB_APP_NONE:        return "SUB_APP_NONE";
    case ModeManagerTypes::SubApplicationType::SUB_APP_AUDIO:       return "SUB_APP_AUDIO";
    case ModeManagerTypes::SubApplicationType::SUB_APP_VIDEO:       return "SUB_APP_VIDEO";
    }

    return "Invalid Value";
}

const char * toString(ModeManagerTypes::AppChangeRequester param)
{
    switch ( param )
    {
    case ModeManagerTypes::AppChangeRequester::INVALID:         return "INVALID";
    case ModeManagerTypes::AppChangeRequester::BY_HMI:          return "BY_HMI";
    case ModeManagerTypes::AppChangeRequester::AUTOMATIC:       return "AUTOMATIC";
    }

    return "Invalid Value";
}

const char * toString(ModeManagerTypes::AppChangeResult param)
{
    switch ( param )
    {
    case ModeManagerTypes::AppChangeResult::RESULT_OK:         return "RESULT_OK";
    case ModeManagerTypes::AppChangeResult::RESULT_FAIL:       return "RESULT_FAIL";
    }

    return "Invalid Value";
}


QString toString(const ModeManagerTypes::ApplicationInfo & param)
{
    return QString("deviceId = %1, deviceType = %2, app = %3, subApp = %4")
            .arg(param.getDeviceId())
            .arg(toString(param.getDeviceType()))
            .arg(toString(param.getApp()))
            .arg(toString(param.getSubApp()));
}

}
