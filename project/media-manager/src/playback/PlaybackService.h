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
 * \file PlaybackService.h
*/

#ifndef PLAYBACKSERVICE
#define PLAYBACKSERVICE

#include "com/ivis/MediaManager/PlaybackControlStubDefault.hpp"

using namespace v1::com::ivis::MediaManager;

/*!
 \brief

 \class PlaybackService playbackservice.h "playbackservice.h"
*/
class PlaybackService : public PlaybackControlStubDefault
{

private:
    PlaybackService();

public:
    static std::shared_ptr<PlaybackService> &getInstance();

public:
    virtual ~PlaybackService();

public:
    void fireNotifiyTimePositionInfoChangedEvent(const MediaManagerTypes::TimePositionInfo &timePositionInfo) override;
    void fireResponseGetPlaylistEvent(const uint32_t &startIndex, const int32_t &amount, const MediaManagerTypes::Playlist &playlist) override;
    void fireNotifyPlaylistChangedEvent() override;
    void fireNotifyPlaybackErrorEvent(const MediaManagerTypes::PlaybackError &errType) override;

    void setRepeatModeAttribute(MediaManagerTypes::RepeatMode value) override;
    void setPlayModeAttribute(MediaManagerTypes::PlayMode value) override;
    void setCurrentTrackInfoAttribute(MediaManagerTypes::TrackInfo value) override;
    void setCurrentTrackNumberAttribute(uint32_t value) override;
    void setTotalTrackNumberAttribute(uint32_t value) override;
    void setVideoVisibleAttribute(bool value) override;
    void setPlayStateInfoAttribute(MediaManagerTypes::PlayStateInfo value) override;

public:
    virtual void requestAction(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::Action _action, uint64_t _value, requestActionReply_t _reply) override;
    virtual void requestPlay(const std::shared_ptr<CommonAPI::ClientId> _client, uint64_t _indexOfplaylist, requestPlayReply_t _reply) override;
    virtual void requestPlayBrowsingSession(const std::shared_ptr<CommonAPI::ClientId> _client, uint64_t _browsingSessionId, uint64_t _uniqueId, requestPlayBrowsingSessionReply_t _reply) override;
    virtual void requestSetTimePosition(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _time, requestSetTimePositionReply_t _reply) override;
    virtual void requestGetPlaylist(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::ResultTypeList _resultTypes, uint32_t _startIndex, int32_t _amount, requestGetPlaylistReply_t _reply) override;
    virtual void requestSetRepeatMode(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::RepeatMode _mode, requestSetRepeatModeReply_t _reply) override;
    virtual void requestSetPlayMode(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1_0::com::ivis::MediaManager::MediaManagerTypes::PlayMode _mode, requestSetPlayModeReply_t _reply) override;
};

#endif // PLAYBACKSERVICE

