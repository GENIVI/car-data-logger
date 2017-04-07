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
 * \file PlaybackManager.cpp
*/

#include "PlaybackManager.h"
#include "PlaybackLogHelper.h"
#include "USBMusicPlayer.h"
#include "USBVideoPlayer.h"
#include "src/MediaManagerDebug.h"

#include <CommonAPI/CommonAPI.hpp>

PlaybackManager * gp_playbackManagerInstance = nullptr;

void PlaybackManager::init()
{
    LOG_DEBUG("");

    auto runtime = CommonAPI::Runtime::get();
    mModeManagerProxy = runtime->buildProxy<ModeManagerProxy>("local", "com.ivis.ModeManager.ModeManager");

    mModeManagerProxy->getActiveApplicationAttribute().getChangedEvent().subscribe(
                std::bind(&PlaybackManager::onActiveApplicationChanged, this, std::placeholders::_1));
}

PlaybackManager *PlaybackManager::getInstance()
{
    LOG_DEBUG("");

    if ( nullptr == gp_playbackManagerInstance )
    {
        gp_playbackManagerInstance = new PlaybackManager;
    }

    return gp_playbackManagerInstance;
}

void PlaybackManager::requestAction( MediaManagerTypes::Action _action, uint64_t _value )
{
    if ( mCurrentPlayer != nullptr )
    {
        LOG_DEBUG( QString("Action : %1, value : %2").arg( DebugHelper::toString( _action ) ).arg( _value ) );
        mCurrentPlayer->requestAction( _action, _value );
    }
    else
    {
        LOG_WARN("current player is nullptr")
    }
}

void PlaybackManager::requestPlay( uint64_t _index )
{
    if ( mCurrentPlayer != nullptr )
    {
        LOG_DEBUG( QString("index : %1").arg( _index ) );
        mCurrentPlayer->requestPlay( _index );
    }
    else
    {
        LOG_WARN("current player is nullptr")
    }
}



void PlaybackManager::requestPlayBrowsingSession( uint64_t _sessionId, uint64_t _pk )
{
    if ( mCurrentPlayer != nullptr )
    {
        LOG_DEBUG( QString("session : %1, pk : %2").arg( _sessionId ).arg( _pk ) );
        mCurrentPlayer->requestPlayBrowsingSession( _sessionId, _pk );
    }
    else
    {
        LOG_WARN("current player is nullptr")
    }
}



void PlaybackManager::requestSetTimePosition( uint32_t _timePosition )
{
    if ( mCurrentPlayer != nullptr )
    {
        LOG_DEBUG( QString("time position : %1").arg( _timePosition ) );
        mCurrentPlayer->requestSetTimePosition( _timePosition );
    }
    else
    {
        LOG_WARN("current player is nullptr")
    }
}



void PlaybackManager::requestGetPlaylist( std::vector<MediaManagerTypes::MetadataType> _resultTypes, uint32_t _startIndex, int32_t _amount )
{
    if ( mCurrentPlayer != nullptr )
    {
        LOG_DEBUG( QString("start index : %1, amount : %2").arg( _startIndex ).arg( _amount ) );
        mCurrentPlayer->requestGetPlaylist( _resultTypes, _startIndex, _amount );
    }
    else
    {
        LOG_WARN("current player is nullptr")
    }
}



void PlaybackManager::requestSetRepeatMode( MediaManagerTypes::RepeatMode _mode )
{
    if ( mCurrentPlayer != nullptr )
    {
        LOG_DEBUG( QString("Repeat Mode : %1").arg( DebugHelper::toString( _mode ) ) );
        mCurrentPlayer->requestSetRepeatMode( _mode );
    }
    else
    {
        LOG_WARN("current player is nullptr")
    }
}



void PlaybackManager::requestSetPlayMode( MediaManagerTypes::PlayMode _mode )
{
    if ( mCurrentPlayer != nullptr )
    {
        LOG_DEBUG( QString("Play Mode : %1").arg( DebugHelper::toString( _mode ) ) );
        mCurrentPlayer->requestSetPlayMode( _mode );
    }
    else
    {
        LOG_WARN("current player is nullptr")
    }
}

void PlaybackManager::onActiveApplicationChanged(const ModeManagerTypes::ApplicationInfo &applicationInfo)
{
    AbstractPlayer * newPlayback = nullptr;

    if ( applicationInfo.getApp() == ModeManagerTypes::ApplicationType::APP_USB )
    {
        if ( applicationInfo.getSubApp() == ModeManagerTypes::SubApplicationType::SUB_APP_AUDIO )
        {
            newPlayback = mUSBMusicPlayer;
        }
        else if ( applicationInfo.getSubApp() == ModeManagerTypes::SubApplicationType::SUB_APP_VIDEO )
        {
            newPlayback = mUSBVideoPlayer;
        }
        else
        {
            LOG_WARN("unhandled sub app type");
        }
    }
    else
    {
        LOG_WARN("unhandled app type");
    }

    if ( newPlayback != nullptr )
    {
        if ( mCurrentPlayer != nullptr )
        {
            mCurrentPlayer->requestAction(MediaManagerTypes::Action::PAUSE, 0);
        }

        mCurrentPlayer = newPlayback;

        mCurrentPlayer->updateCurrentTrackInfo();
        mCurrentPlayer->requestAction(MediaManagerTypes::Action::PLAY, 0);
    }
}

PlaybackManager::~PlaybackManager()
{
    mCurrentPlayer = nullptr;

    if ( mUSBMusicPlayer != nullptr )
    {
        delete mUSBMusicPlayer;
        mUSBMusicPlayer = nullptr;
    }

    if ( mUSBVideoPlayer != nullptr )
    {
        delete mUSBVideoPlayer;
        mUSBVideoPlayer = nullptr;
    }
}

PlaybackManager::PlaybackManager()
    : mCurrentPlayer(nullptr),
      mUSBMusicPlayer(nullptr),
      mUSBVideoPlayer(nullptr)
{
    LOG_DEBUG("");

    mUSBMusicPlayer = new USBMusicPlayer;
    mUSBVideoPlayer = new USBVideoPlayer;
}
