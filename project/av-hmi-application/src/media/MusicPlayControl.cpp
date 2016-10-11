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
 * \file MusicPlayControl.cpp
*/

#include "MusicPlayControl.h"
#include "../system/HMIModeManager.h"

#include <QQuickView>
#include <QQmlContext>
#include <QDebug>

#include <CommonAPI/CommonAPI.hpp>

static QSharedPointer<MusicPlayControl> mediaPlayControlInstance;

MusicPlayControl::MusicPlayControl(QObject *parent) : QObject(parent),
    m_playState(true), m_progressbarState(false),
    m_curPlayTime(0), m_curPlayIndex(0), m_curMediaIndex(0),
    m_title(""), m_artist(""), m_albumArtPath("")
{
    setObjectName("MediaPlayControl");
    init();
}

QSharedPointer<MusicPlayControl> MusicPlayControl::instance(QObject *parent)
{
    if (mediaPlayControlInstance.isNull())
    {
        mediaPlayControlInstance =  QSharedPointer<MusicPlayControl>(new MusicPlayControl(parent));
    }

    return mediaPlayControlInstance.constCast<MusicPlayControl>();
}

MusicPlayControl::~MusicPlayControl()
{
}

void MusicPlayControl::init()
{
    auto runtime = CommonAPI::Runtime::get();

    mPlaybackProxy = runtime->buildProxy<PlaybackControlProxy>("local", PlaybackControl::getInterface());

    mPlaybackProxy->getCurrentTrackInfoAttribute().getChangedEvent().subscribe(
                std::bind(&MusicPlayControl::onTrackInfoChanged, this, std::placeholders::_1));

    mPlaybackProxy->getCurrentTrackNumberAttribute().getChangedEvent().subscribe(
                std::bind(&MusicPlayControl::onCurrentTrackNumberChanged, this, std::placeholders::_1));

    mPlaybackProxy->getTotalTrackNumberAttribute().getChangedEvent().subscribe(
                std::bind(&MusicPlayControl::onTotalTrackNumberChanged, this, std::placeholders::_1));

    mPlaybackProxy->getNotifiyTimePositionInfoChangedEvent().subscribe(
                std::bind(&MusicPlayControl::onTimePositionChanged, this, std::placeholders::_1));
}

bool MusicPlayControl::playState() const
{
    return m_playState;
}

int MusicPlayControl::curMediaIndex() const
{
    return m_curMediaIndex;
}

QString MusicPlayControl::artist() const
{
    return m_artist;
}

QString MusicPlayControl::title() const
{
    return m_title;
}

QString MusicPlayControl::albumArtPath() const
{
    return m_albumArtPath;
}

int MusicPlayControl::mediaPlayTime() const
{
    return m_mediaPlayTime;
}

int MusicPlayControl::curPlayTime() const
{
    return m_curPlayTime;
}






void MusicPlayControl::setPlayState(bool playState)
{
    m_playState = playState;
    emit playStateChanged(playState);
}

void MusicPlayControl::setcurMediaIndex(int curMediaIndex)
{
    if (m_curMediaIndex == curMediaIndex)
        return;

    m_curMediaIndex = curMediaIndex;
    emit curMediaIndexChanged(curMediaIndex);
}

void MusicPlayControl::setArtist(QString artist)
{
    if (m_artist == artist)
        return;

    m_artist = artist;
    emit artistChanged(artist);
}

void MusicPlayControl::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(title);
}

void MusicPlayControl::setAlbumArtPath(QString albumArtPath)
{
    if (m_albumArtPath == albumArtPath)
        return;

    m_albumArtPath = albumArtPath;
    emit albumArtPathChanged(albumArtPath);
}

void MusicPlayControl::setCurPlayTime(int curPlayTime)
{
    if (m_curPlayTime == curPlayTime)
        return;

    m_curPlayTime = curPlayTime;
    emit curPlayTimeChanged(curPlayTime);
}

void MusicPlayControl::setMediaPlayTime(int mediaPlayTime)
{
    if (m_mediaPlayTime == mediaPlayTime)
        return;

    m_mediaPlayTime = mediaPlayTime;
    emit mediaPlayTimeChanged(mediaPlayTime);
}

void MusicPlayControl::onTrackInfoChanged(const MediaManagerTypes::TrackInfo &trackInfo)
{
    if ( HMIModeManager::instance()->mCurrentApplicationType == ModeManagerTypes::SubApplicationType::SUB_APP_AUDIO )
    {
        QString title=QString::fromStdString(trackInfo.getTitle().data());
        QString artist=QString::fromStdString(trackInfo.getArtist().data());
        QString albumArtPath=QString::fromStdString(trackInfo.getAlbumArtPath().data());
        int mediaPlayTime=trackInfo.getTotalTimeLength();

//        qDebug()<<"Music Title : "<<title;
//        qDebug()<<"Music Artist : "<<artist;
//        qDebug()<<"Music Path : "<<albumArtPath;

        setTitle(title);
        setArtist(artist);
        setAlbumArtPath(albumArtPath);
        setMediaPlayTime(mediaPlayTime);
    }
}

void MusicPlayControl::onCurrentTrackNumberChanged(const uint32_t &currentTrackNumber)
{
    int curTrckNumber = currentTrackNumber;
    Q_UNUSED(curTrckNumber)
}

void MusicPlayControl::onTotalTrackNumberChanged(const uint32_t &totalTrackNumber)
{
    Q_UNUSED(totalTrackNumber)
}

void MusicPlayControl::onTimePositionChanged(const MediaManagerTypes::TimePositionInfo &timePositionInfo)
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




void MusicPlayControl::requestPlay()
{
}

void MusicPlayControl::requestPlayPause(bool checked)
{
    m_playState=checked;

    if(!checked)        
        mPlaybackProxy->requestActionAsync(MediaManagerTypes::Action::PAUSE, 0);
    else
        mPlaybackProxy->requestActionAsync(MediaManagerTypes::Action::PLAY, 0);
}

void MusicPlayControl::requestNext()
{
    setCurPlayTime(0);
    mPlaybackProxy->requestActionAsync(MediaManagerTypes::Action::NEXT_TRACK, 0);
}

void MusicPlayControl::requestPrev()
{
    setCurPlayTime(0);
    mPlaybackProxy->requestActionAsync(MediaManagerTypes::Action::PREV_TRACK, 0);
}

void MusicPlayControl::progressbarPress(int value)
{
    mPlaybackProxy->requestSetTimePositionAsync(value, 0);
}

void MusicPlayControl::setMediaType(int mediaType)
{
    m_mediaType = mediaType;
}

void MusicPlayControl::progressbarPressState(bool state)
{
    m_progressbarState = state;
}
