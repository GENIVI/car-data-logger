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
 * \file MediaManagerDebug.h
*/

#ifndef MEDIAMANAGERDEBUG_H
#define MEDIAMANAGERDEBUG_H

#include <QString>
#include <com/ivis/MediaManager/MediaManagerTypes.hpp>
#include <dlt.h>

using namespace v1_0::com::ivis::MediaManager;

namespace DebugHelper
{
const char * toString(MediaManagerTypes::MetadataType param);
const char * toString(MediaManagerTypes::BrowserError param);
const char * toString(MediaManagerTypes::PlaybackError param);
const char * toString(MediaManagerTypes::MediaType param);
const char * toString(MediaManagerTypes::SyncLevel param);
const char * toString(MediaManagerTypes::Action param);
const char * toString(MediaManagerTypes::RepeatMode param);
const char * toString(MediaManagerTypes::BrowsingStatus param);
const char * toString(MediaManagerTypes::IndexerState param);
const char * toString(MediaManagerTypes::PlayMode param);
const char * toString(MediaManagerTypes::SyncState param);

}

#endif // MEDIAMANAGERDEBUG_H
