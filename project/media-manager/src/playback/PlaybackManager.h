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
 * \file PlaybackManager.h
*/

#ifndef PLAYBACKMANAGER_H
#define PLAYBACKMANAGER_H

#include <com/ivis/MediaManager/MediaManagerTypes.hpp>
#include <com/ivis/ModeManager/ModeManagerProxy.hpp>

using namespace v1::com::ivis::MediaManager;
using namespace v1::com::ivis::ModeManager;

class AbstractPlayer;

class PlaybackManager
{
private:
    explicit PlaybackManager();

public:
    static PlaybackManager * getInstance();

public:
    ~PlaybackManager();

public:
    void init();

public: // playbackService interface
    void requestAction(MediaManagerTypes::Action _action, uint64_t _value);
    void requestPlay(uint64_t _index);
    void requestPlayBrowsingSession(uint64_t _sessionId, uint64_t _pk);
    void requestSetTimePosition(uint32_t _timePosition);
    void requestGetPlaylist(std::vector<MediaManagerTypes::MetadataType> _resultTypes, uint32_t _startIndex, int32_t _amount);
    void requestSetRepeatMode(MediaManagerTypes::RepeatMode _mode);
    void requestSetPlayMode(MediaManagerTypes::PlayMode _mode);

public:
    void onActiveApplicationChanged(const ModeManagerTypes::ApplicationInfo & applicationInfo);

private:
    AbstractPlayer * mCurrentPlayer;
    AbstractPlayer * mUSBMusicPlayer;
    AbstractPlayer * mUSBVideoPlayer;

    std::shared_ptr<ModeManagerProxy<> > mModeManagerProxy;
};

#endif // COM_IVIS_MEDIAMANAGER_PLAYBACKMANAGER_H
