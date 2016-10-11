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
 * \file MediaManagerDebug.cpp
*/

#include "MediaManagerDebug.h"

namespace DebugHelper
{
const char * toString(MediaManagerTypes::MetadataType param)
{
	switch ( param )
	{
	case MediaManagerTypes::MetadataType::TITLE:		return "TITLE";
	case MediaManagerTypes::MetadataType::ARTIST:		return "ARTIST";
	case MediaManagerTypes::MetadataType::ALBUM:		return "ALBUM";
	case MediaManagerTypes::MetadataType::GENRE:		return "GENRE";
	case MediaManagerTypes::MetadataType::ALBUMART:		return "ALBUMART";
	case MediaManagerTypes::MetadataType::DURATION:		return "DURATION";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::BrowserError param)
{
	switch ( param )
	{
	case MediaManagerTypes::BrowserError::BR_OK:		return "BR_OK";
	case MediaManagerTypes::BrowserError::BR_NO_RESULT:		return "BR_NO_RESULT";
	case MediaManagerTypes::BrowserError::BR_INVALID_PARAMETER:		return "BR_INVALID_PARAMETER";
	case MediaManagerTypes::BrowserError::BR_INVALID_QUERY:		return "BR_INVALID_QUERY";
	case MediaManagerTypes::BrowserError::BR_UNKNOWN:		return "BR_UNKNOWN";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::PlaybackError param)
{
	switch ( param )
	{
	case MediaManagerTypes::PlaybackError::ERROR:		return "ERROR";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::MediaType param)
{
	switch ( param )
	{
	case MediaManagerTypes::MediaType::INVALID:		return "INVALID";
	case MediaManagerTypes::MediaType::AUDIO:		return "AUDIO";
	case MediaManagerTypes::MediaType::VIDEO:		return "VIDEO";
	case MediaManagerTypes::MediaType::IMAGE:		return "IMAGE";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::SyncLevel param)
{
	switch ( param )
	{
	case MediaManagerTypes::SyncLevel::NONE:		return "NONE";
	case MediaManagerTypes::SyncLevel::FILE:		return "FILE";
	case MediaManagerTypes::SyncLevel::FILEANDMETADATA:		return "FILEANDMETADATA";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::Action param)
{
	switch ( param )
	{
	case MediaManagerTypes::Action::PLAY:		return "PLAY";
	case MediaManagerTypes::Action::PAUSE:		return "PAUSE";
	case MediaManagerTypes::Action::STOP:		return "STOP";
	case MediaManagerTypes::Action::FAST_FOWARD:		return "FAST_FOWARD";
	case MediaManagerTypes::Action::FAST_FOWARD_AUTO:		return "FAST_FOWARD_AUTO";
	case MediaManagerTypes::Action::FAST_REWIND:		return "FAST_REWIND";
	case MediaManagerTypes::Action::FAST_REWIND_AUTO:		return "FAST_REWIND_AUTO";
	case MediaManagerTypes::Action::NEXT_TRACK:		return "NEXT_TRACK";
	case MediaManagerTypes::Action::PREV_TRACK:		return "PREV_TRACK";
	case MediaManagerTypes::Action::STEP_FOWARD:		return "STEP_FOWARD";
	case MediaManagerTypes::Action::STEP_REWIND:		return "STEP_REWIND";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::RepeatMode param)
{
	switch ( param )
	{
	case MediaManagerTypes::RepeatMode::REPEAT_OFF:		return "REPEAT_OFF";
	case MediaManagerTypes::RepeatMode::REPEAT_ALL:		return "REPEAT_ALL";
	case MediaManagerTypes::RepeatMode::REPEAT_ONE_SONG:		return "REPEAT_ONE_SONG";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::BrowsingStatus param)
{
	switch ( param )
	{
	case MediaManagerTypes::BrowsingStatus::START:		return "START";
	case MediaManagerTypes::BrowsingStatus::RUNNING:		return "RUNNING";
	case MediaManagerTypes::BrowsingStatus::FINISHED:		return "FINISHED";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::IndexerState param)
{
	switch ( param )
	{
	case MediaManagerTypes::IndexerState::IDLE:		return "IDLE";
	case MediaManagerTypes::IndexerState::RUNNING:		return "RUNNING";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::PlayMode param)
{
	switch ( param )
	{
	case MediaManagerTypes::PlayMode::NORMAL:		return "NORMAL";
	case MediaManagerTypes::PlayMode::SUFFLE:		return "SUFFLE";
	}

	return "Invalid Value";
}

const char * toString(MediaManagerTypes::SyncState param)
{
	switch ( param )
	{
	case MediaManagerTypes::SyncState::IDLE:		return "IDLE";
	case MediaManagerTypes::SyncState::RUNNING:		return "RUNNING";
	case MediaManagerTypes::SyncState::PAUSE:		return "PAUSE";
	case MediaManagerTypes::SyncState::ERROR:		return "ERROR";
	}

	return "Invalid Value";
}

}
