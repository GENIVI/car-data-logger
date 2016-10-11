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
 * \file ModeManagerDebug.h
*/

#ifndef MODEMANAGERDEBUG
#define MODEMANAGERDEBUG

#include <QString>
#include <com/ivis/ModeManager/ModeManagerTypes.hpp>
#include <dlt.h>

using namespace v1::com::ivis::ModeManager;

namespace DebugHelper
{

const char * toString(ModeManagerTypes::DeviceType param);
const char * toString(ModeManagerTypes::ApplicationType param);
const char * toString(ModeManagerTypes::SubApplicationType param);
const char * toString(ModeManagerTypes::AppChangeRequester param);
const char * toString(ModeManagerTypes::AppChangeResult param);

QString toString(const ModeManagerTypes::ApplicationInfo & param);

}

#endif // MODEMANAGERDEBUG

