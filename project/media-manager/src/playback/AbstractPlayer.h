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
 * \file AbstractPlayer.h
*/

#ifndef ABSTRACTPLAYER
#define ABSTRACTPLAYER

#include <QObject>
#include <QTimer>
#include <com/ivis/MediaManager/MediaManagerTypes.hpp>

using namespace v1::com::ivis::MediaManager;

class AbstractPlayer : public QObject
{
    Q_OBJECT

public:
    AbstractPlayer();
    virtual ~AbstractPlayer();

public:
    virtual void requestAction(MediaManagerTypes::Action action, uint64_t value);
    virtual void requestPlay(uint64_t indexOfplaylist);
    virtual void requestPlayBrowsingSession(uint64_t browsingSessionId, uint64_t uniqueId);
    virtual void requestSetTimePosition(uint32_t time);
    virtual void requestGetPlaylist(std::vector<MediaManagerTypes::MetadataType> resultTypes, uint32_t startIndex, int32_t amount);
    virtual void requestSetRepeatMode(MediaManagerTypes::RepeatMode mode);
    virtual void requestSetPlayMode(MediaManagerTypes::PlayMode mode);

public:
    void updateCurrentTrackInfo();

signals:
    void signalStartPlayTimer();
    void signalStopPlayTimer();

public slots:
    void updatePlayPosition();
    void startPlayTimer();
    void stopPlayTimer();

private:
    void playNextTrack();
    void playPrevTrack();

protected:
    MediaManagerTypes::Playlist mPlaylist;

    QTimer * mPlayPositionTimer;
    quint32 mCurrentTrackIndex;
    quint32 mPlayPosition;
};

#endif // ABSTRACTPLAYER
