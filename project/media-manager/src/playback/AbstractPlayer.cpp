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
 * \file AbstractPlayer.cpp
*/

#include "AbstractPlayer.h"
#include "PlaybackService.h"
#include "PlaybackLogHelper.h"
#include "src/MediaManagerDebug.h"

AbstractPlayer::AbstractPlayer()
    : QObject()
{
    mCurrentTrackIndex = 0;
    mPlayPosition = 0;

    mPlayPositionTimer = new QTimer(this);

    connect(mPlayPositionTimer, SIGNAL(timeout()), this, SLOT(updatePlayPosition()));
    connect(this, SIGNAL(signalStartPlayTimer()), this, SLOT(startPlayTimer()));
    connect(this, SIGNAL(signalStopPlayTimer()), this, SLOT(stopPlayTimer()));
}

AbstractPlayer::~AbstractPlayer()
{

}

void AbstractPlayer::requestAction(MediaManagerTypes::Action action, uint64_t value)
{
    Q_UNUSED(value);

    switch ( action )
    {
    case MediaManagerTypes::Action::PLAY:           emit signalStartPlayTimer();        break;
    case MediaManagerTypes::Action::PAUSE:          emit signalStopPlayTimer();         break;
    case MediaManagerTypes::Action::NEXT_TRACK:     playNextTrack();                    break;
    case MediaManagerTypes::Action::PREV_TRACK:     playPrevTrack();                    break;
    default:
        LOG_WARN(QString("not implemented action -> %1").arg(DebugHelper::toString(action)));
        break;
    }
}

void AbstractPlayer::requestPlay(uint64_t indexOfplaylist)
{
    Q_UNUSED(indexOfplaylist);

    LOG_WARN("not implemented..");
}

void AbstractPlayer::requestPlayBrowsingSession(uint64_t browsingSessionId, uint64_t uniqueId)
{
    Q_UNUSED(browsingSessionId);
    Q_UNUSED(uniqueId);

    LOG_WARN("not implemented..");
}

void AbstractPlayer::requestSetTimePosition(uint32_t time)
{
    emit signalStopPlayTimer();

    mPlayPosition = time;

    const MediaManagerTypes::TrackInfo & currentTrackInfo = mPlaylist.at( mCurrentTrackIndex );

    MediaManagerTypes::TimePositionInfo timePositionInfo(currentTrackInfo.getFid(), mPlayPosition, currentTrackInfo.getTotalTimeLength(), 1);

    PlaybackService::getInstance()->fireNotifiyTimePositionInfoChangedEvent( timePositionInfo );

    emit signalStartPlayTimer();
}

void AbstractPlayer::requestGetPlaylist(std::vector<MediaManagerTypes::MetadataType> resultTypes, uint32_t startIndex, int32_t amount)
{
    Q_UNUSED(resultTypes);
    Q_UNUSED(startIndex);
    Q_UNUSED(amount);

    LOG_WARN("not implemented..");
}

void AbstractPlayer::requestSetRepeatMode(MediaManagerTypes::RepeatMode mode)
{
    Q_UNUSED(mode);

    LOG_WARN("not implemented..");
}

void AbstractPlayer::requestSetPlayMode(MediaManagerTypes::PlayMode mode)
{
    Q_UNUSED(mode);

    LOG_WARN("not implemented..");
}






void AbstractPlayer::updatePlayPosition()
{
    const MediaManagerTypes::TrackInfo & currentTrackInfo = mPlaylist.at( mCurrentTrackIndex );

    mPlayPosition++;

    if ( mPlayPosition > currentTrackInfo.getTotalTimeLength() )
    {
        requestAction(MediaManagerTypes::Action::NEXT_TRACK, 0);
    }
    else
    {
        MediaManagerTypes::TimePositionInfo timePositionInfo(currentTrackInfo.getFid(), mPlayPosition, currentTrackInfo.getTotalTimeLength(), 1);

        PlaybackService::getInstance()->fireNotifiyTimePositionInfoChangedEvent( timePositionInfo );
    }
}

void AbstractPlayer::updateCurrentTrackInfo()
{
    mPlayPosition = 0;

    const MediaManagerTypes::TrackInfo & currentTrackInfo = mPlaylist.at( mCurrentTrackIndex );

    PlaybackService::getInstance()->setCurrentTrackInfoAttribute( currentTrackInfo );
    PlaybackService::getInstance()->setCurrentTrackNumberAttribute( mCurrentTrackIndex + 1 );
    PlaybackService::getInstance()->setTotalTrackNumberAttribute( mPlaylist.size() );

    MediaManagerTypes::TimePositionInfo timePositionInfo(currentTrackInfo.getFid(), mPlayPosition, currentTrackInfo.getTotalTimeLength(), 1);

    PlaybackService::getInstance()->fireNotifiyTimePositionInfoChangedEvent( timePositionInfo );
}

void AbstractPlayer::playNextTrack()
{
    emit signalStopPlayTimer();

    mCurrentTrackIndex++;

    if ( mCurrentTrackIndex == mPlaylist.size() )
    {
        mCurrentTrackIndex = 0;
    }

    updateCurrentTrackInfo();

    emit signalStartPlayTimer();
}

void AbstractPlayer::playPrevTrack()
{
    emit signalStopPlayTimer();

    if ( mCurrentTrackIndex == 0 )
    {
        mCurrentTrackIndex = mPlaylist.size() - 1;
    }
    else
    {
        mCurrentTrackIndex--;
    }

    updateCurrentTrackInfo();

    emit signalStartPlayTimer();
}

void AbstractPlayer::startPlayTimer()
{
    if ( !mPlayPositionTimer->isActive() )
    {
        mPlayPositionTimer->start(1000);
    }
}

void AbstractPlayer::stopPlayTimer()
{
    if ( mPlayPositionTimer->isActive() )
    {
        mPlayPositionTimer->stop();
    }
}
