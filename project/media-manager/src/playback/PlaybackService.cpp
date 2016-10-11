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
 * \file PlaybackService.cpp
*/

#include <CommonAPI/CommonAPI.hpp>

#include "PlaybackService.h"

#include "PlaybackManager.h"
#include "PlaybackLogHelper.h"
#include "src/MediaManagerDebug.h"


std::shared_ptr<PlaybackService> playbackManagerServiceInstance = nullptr;

std::shared_ptr<PlaybackService> &PlaybackService::getInstance()
{
    if ( nullptr == playbackManagerServiceInstance )
    {
        playbackManagerServiceInstance = std::shared_ptr<PlaybackService>(new PlaybackService);
    }
    return playbackManagerServiceInstance;
}

PlaybackService::PlaybackService()
{
    PlaybackManager::getInstance()->init();
}

PlaybackService::~PlaybackService()
{
}



void PlaybackService::fireNotifiyTimePositionInfoChangedEvent(const MediaManagerTypes::TimePositionInfo &timePositionInfo)
{
    QString msg = QString("currentTimePosition = %1, totalTimeLength = %2, seekFactor = %3, currentFid = %4,")
            .arg(timePositionInfo.getCurrentTimePosition())
            .arg(timePositionInfo.getTotalTimeLength())
            .arg(timePositionInfo.getSeekFactor())
            .arg(timePositionInfo.getCurrentFid());

    LOG_INFO(msg)

    PlaybackControlStubDefault::fireNotifiyTimePositionInfoChangedEvent(timePositionInfo);
}

void PlaybackService::fireResponseGetPlaylistEvent(const uint32_t &startIndex, const int32_t &amount, const MediaManagerTypes::Playlist &playlist)
{
    LOG_INFO(QString("startIndex = %1, amount = %2").arg(startIndex).arg(amount))

    PlaybackControlStubDefault::fireResponseGetPlaylistEvent(startIndex, amount, playlist);
}

void PlaybackService::fireNotifyPlaylistChangedEvent()
{
    LOG_INFO("notifyPlaylistChangedEvent")

    PlaybackControlStubDefault::fireNotifyPlaylistChangedEvent();
}

void PlaybackService::fireNotifyPlaybackErrorEvent(const MediaManagerTypes::PlaybackError &errType)
{
    LOG_INFO(QString("MediaManagerTypes::PlaybackError = %1").arg(DebugHelper::toString(errType)))

    PlaybackControlStubDefault::fireNotifyPlaybackErrorEvent(errType);
}












void PlaybackService::setRepeatModeAttribute(MediaManagerTypes::RepeatMode value)
{
    LOG_INFO(QString("MediaManagerTypes::RepeatMode = %1").arg(DebugHelper::toString(value)))

    PlaybackControlStubDefault::setRepeatModeAttribute(value);
}

void PlaybackService::setPlayModeAttribute(MediaManagerTypes::PlayMode value)
{
    LOG_INFO(QString("MediaManagerTypes::PlayMode = %1").arg(DebugHelper::toString(value)))

    PlaybackControlStubDefault::setPlayModeAttribute(value);
}

void PlaybackService::setCurrentTrackInfoAttribute(MediaManagerTypes::TrackInfo value)
{
    QString msg;
    msg.append("fid = ").append(QString::number(value.getFid()));
    msg.append(", deviceId = ").append(QString::number(value.getDeviceId()));
    msg.append(", totalTimeLength = ").append(QString::number(value.getTotalTimeLength()));
    msg.append(", title = ").append(QString::fromUtf8(value.getTitle().c_str()));
    msg.append(", artist = ").append(QString::fromUtf8(value.getArtist().c_str()));
    msg.append(", album = ").append(QString::fromUtf8(value.getAlbum().c_str()));
    msg.append(", genre = ").append(QString::fromUtf8(value.getGenre().c_str()));
    msg.append(", albumArtPath = ").append(QString::fromUtf8(value.getAlbumArtPath().c_str()));
    msg.append(", filePath = ").append(QString::fromUtf8(value.getFilePath().c_str()));

    LOG_INFO(msg)

    PlaybackControlStubDefault::setCurrentTrackInfoAttribute(value);
}

void PlaybackService::setCurrentTrackNumberAttribute(uint32_t value)
{
    LOG_INFO(QString("currentTrackNumber = %1").arg(value))

    PlaybackControlStubDefault::setCurrentTrackNumberAttribute(value);
}

void PlaybackService::setTotalTrackNumberAttribute(uint32_t value)
{
    LOG_INFO(QString("totalTrackNumber = %1").arg(value))

    PlaybackControlStubDefault::setTotalTrackNumberAttribute(value);
}

void PlaybackService::setVideoVisibleAttribute(bool value)
{
    LOG_INFO(QString("videoVisible = %1").arg(value))

    PlaybackControlStubDefault::setVideoVisibleAttribute(value);
}

void PlaybackService::setPlayStateInfoAttribute(MediaManagerTypes::PlayStateInfo value)
{
    LOG_INFO(QString("currentFid = %1, state = %2").arg(value.getCurrentFid()).arg(DebugHelper::toString(value.getState())));

    PlaybackControlStubDefault::setPlayStateInfoAttribute(value);
}









void PlaybackService::requestAction(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::Action _action, uint64_t _value, requestActionReply_t _reply)
{
    Q_UNUSED(_client);

    LOG_INFO(QString("MediaManagerTypes::Action = %1, value= %2").arg(DebugHelper::toString(_action)).arg(_value));

    PlaybackManager::getInstance()->requestAction(_action, _value);

    _reply();
}

void PlaybackService::requestPlay(const std::shared_ptr<CommonAPI::ClientId> _client, uint64_t _indexOfplaylist, requestPlayReply_t _reply)
{
    Q_UNUSED(_client);

    LOG_INFO(QString("indexOfplaylist = %1").arg(_indexOfplaylist))

    PlaybackManager::getInstance()->requestPlay(_indexOfplaylist);

    _reply();
}

void PlaybackService::requestPlayBrowsingSession(const std::shared_ptr<CommonAPI::ClientId> _client, uint64_t _browsingSessionId, uint64_t _uniqueId, requestPlayBrowsingSessionReply_t _reply)
{
    Q_UNUSED(_client);

    LOG_INFO(QString("browsingSessionId = %1, uniqueId = %2").arg(_browsingSessionId).arg(_uniqueId))

    PlaybackManager::getInstance()->requestPlayBrowsingSession(_browsingSessionId, _uniqueId);

    _reply();
}

void PlaybackService::requestSetTimePosition(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _time, requestSetTimePositionReply_t _reply)
{
    Q_UNUSED(_client);

    LOG_INFO(QString("time = %1").arg(_time))

    PlaybackManager::getInstance()->requestSetTimePosition(_time);

    _reply();
}

void PlaybackService::requestGetPlaylist(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::ResultTypeList _resultTypes, uint32_t _startIndex, int32_t _amount, requestGetPlaylistReply_t _reply)
{
    Q_UNUSED(_client);

    LOG_INFO(QString("startIndex = %1, amount = %2").arg(_startIndex).arg(_amount))

    for (uint32_t i = 0; i < _resultTypes.size(); i++)
    {
        LOG_INFO(QString(" resultTypes[%1] = %2").arg(i).arg(DebugHelper::toString(_resultTypes.at(i))));
    }

    PlaybackManager::getInstance()->requestGetPlaylist(_resultTypes, _startIndex, _amount);

    _reply();
}

void PlaybackService::requestSetRepeatMode(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::RepeatMode _mode, requestSetRepeatModeReply_t _reply)
{
    Q_UNUSED(_client);

    LOG_INFO(QString("MediaManagerTypes::RepeatMode = %1").arg(DebugHelper::toString(_mode)))

    PlaybackManager::getInstance()->requestSetRepeatMode(_mode);

    _reply();
}

void PlaybackService::requestSetPlayMode(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::PlayMode _mode, requestSetPlayModeReply_t _reply)
{
    Q_UNUSED(_client);

    LOG_INFO(QString("MediaManagerTypes::PlayMode = %1").arg(DebugHelper::toString(_mode)))

    PlaybackManager::getInstance()->requestSetPlayMode(_mode);

    _reply();
}
