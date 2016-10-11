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
 * \file VideoPlayControl.cpp
*/

#include "VideoPlayControl.h"
#include "MusicPlayControl.h"
#include "../system/HMIModeManager.h"

#include <QQuickView>
#include <QQmlContext>
#include <QDebug>

#include <CommonAPI/CommonAPI.hpp>


static QSharedPointer<VideoPlayControl> videoPlayControlInstance;

VideoPlayControl::VideoPlayControl(QObject *parent) : QObject(parent),    
    m_driveRestrict(false), m_playState(true), m_progressbarState(false),
    m_curPlayTime(0), m_curPlayIndex(0), m_curMediaIndex(0), m_mediaType(0),
    m_title(""), m_artist(""), m_albumArtPath("")
{
    setObjectName("VideoPlayControl");
    init();
}

QSharedPointer<VideoPlayControl> VideoPlayControl::instance(QObject *parent)
{
    if (videoPlayControlInstance.isNull())
    {
        videoPlayControlInstance =  QSharedPointer<VideoPlayControl>(new VideoPlayControl(parent));
    }

    return videoPlayControlInstance.constCast<VideoPlayControl>();
}

VideoPlayControl::~VideoPlayControl()
{
}

void VideoPlayControl::init()
{
    auto runtime = CommonAPI::Runtime::get();

    mPlayBackProxy = runtime->buildProxy<PlaybackControlProxy>("local", PlaybackControl::getInterface());

    mPlayBackProxy->getCurrentTrackInfoAttribute().getChangedEvent().subscribe(
                std::bind(&VideoPlayControl::onTrackInfoChanged, this, std::placeholders::_1));

    mPlayBackProxy->getNotifiyTimePositionInfoChangedEvent().subscribe(
                std::bind(&VideoPlayControl::onTimePositionChanged, this, std::placeholders::_1));

}

bool VideoPlayControl::playState() const
{
    return m_playState;
}

int VideoPlayControl::curMediaIndex() const
{
    return m_curMediaIndex;
}

QString VideoPlayControl::artist() const
{
    return m_artist;
}

QString VideoPlayControl::title() const
{
    return m_title;
}

QString VideoPlayControl::albumArtPath() const
{
    return m_albumArtPath;
}

bool VideoPlayControl::driveRestrict() const
{
    return m_driveRestrict;
}

int VideoPlayControl::mediaPlayTime() const
{
    return m_mediaPlayTime;
}

int VideoPlayControl::curPlayTime() const
{
    return m_curPlayTime;
}




void VideoPlayControl::setPlayState(bool playState)
{
    m_playState = playState;
    emit playStateChanged(playState);
}

void VideoPlayControl::setcurMediaIndex(int curMediaIndex)
{
    if (m_curMediaIndex == curMediaIndex)
        return;

    m_curMediaIndex = curMediaIndex;
    emit curMediaIndexChanged(curMediaIndex);
}

void VideoPlayControl::setArtist(QString artist)
{
    if (m_artist == artist)
        return;

    m_artist = artist;
    emit artistChanged(artist);
}

void VideoPlayControl::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(title);
}

void VideoPlayControl::setAlbumArtPath(QString albumArtPath)
{
    if (m_albumArtPath == albumArtPath)
        return;

    m_albumArtPath = albumArtPath;
    emit albumArtPathChanged(albumArtPath);
}

void VideoPlayControl::setCurPlayTime(int curPlayTime)
{
    if (m_curPlayTime == curPlayTime)
        return;

    m_curPlayTime = curPlayTime;
    emit curPlayTimeChanged(curPlayTime);
}

void VideoPlayControl::setMediaPlayTime(int mediaPlayTime)
{
    if (m_mediaPlayTime == mediaPlayTime)
        return;

    m_mediaPlayTime = mediaPlayTime;
    emit mediaPlayTimeChanged(mediaPlayTime);
}








void VideoPlayControl::onTrackInfoChanged(const MediaManagerTypes::TrackInfo &trackInfo)
{
    if ( HMIModeManager::instance()->mCurrentApplicationType == ModeManagerTypes::SubApplicationType::SUB_APP_VIDEO )
    {
        QString albumArtPath = QString::fromStdString(trackInfo.getAlbumArtPath());
        int mediaPlayTime = trackInfo.getTotalTimeLength();

        setAlbumArtPath(albumArtPath);
        setMediaPlayTime(mediaPlayTime);
    }
}

void VideoPlayControl::onTimePositionChanged(const MediaManagerTypes::TimePositionInfo &timePositionInfo)
{
    int currentPlayTime=timePositionInfo.getCurrentTimePosition();

    if(!m_playState){
        setPlayState(true);
    }
    else
    {
        if(m_progressbarState)
        {

        }
        else
        {
            setCurPlayTime(currentPlayTime);
        }
    }
}







void VideoPlayControl::setDriveRestrict(bool driveRestrict)
{
    if (m_driveRestrict == driveRestrict)
        return;

    m_driveRestrict = driveRestrict;
    emit driveRestrictChanged(driveRestrict);
}

void VideoPlayControl::requestPlayPause(bool checked)
{
    m_playState=checked;

    if(!checked)
        mPlayBackProxy->requestActionAsync(MediaManagerTypes::Action::PAUSE, 0);
    else
        mPlayBackProxy->requestActionAsync(MediaManagerTypes::Action::PLAY, 0);
}

void VideoPlayControl::requestNext()
{    
    setCurPlayTime(0);
    mPlayBackProxy->requestActionAsync(MediaManagerTypes::Action::NEXT_TRACK, 0);
}

void VideoPlayControl::requestPrev()
{
    setCurPlayTime(0);
    mPlayBackProxy->requestActionAsync(MediaManagerTypes::Action::PREV_TRACK, 0);
}

void VideoPlayControl::progressbarPress(int value)
{
    mPlayBackProxy->requestSetTimePositionAsync(value, 0);
}

void VideoPlayControl::setMediaType(int mediaType)
{
    m_mediaType = mediaType;
}

void VideoPlayControl::progressbarPressState(bool state)
{
    m_progressbarState = state;    
}
