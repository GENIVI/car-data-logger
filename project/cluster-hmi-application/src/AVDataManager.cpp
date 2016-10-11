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
 * \file avdatamanager.cpp
*/

#include "AVDataManager.h"
#include "AVInformationTypesEnum.h"

static AVDataManager * avDataManagerInstance = Q_NULLPTR;

AVDataManager *AVDataManager::instance()
{
    if ( avDataManagerInstance == Q_NULLPTR )
    {
        avDataManagerInstance = new AVDataManager;
    }

    return avDataManagerInstance;
}

void AVDataManager::finalize()
{
    if ( avDataManagerInstance != Q_NULLPTR )
    {
        delete avDataManagerInstance;
        avDataManagerInstance = Q_NULLPTR;
    }
}

void AVDataManager::init()
{
    setTitle("Title Text");
    setFileName("");
    setFrequency("99.9");
    setPsName("FM");
    setPresetIndex("23");
}

AVDataManager::AVDataManager(QObject *parent) : QObject(parent)
    , m_source(0)
    , m_title("")
    , m_album("")
    , m_artist("")
    , m_fileName("")
    , m_frequency("")
    , m_psName("")
    , m_presetIndex("")
    , m_totalTrackNumber(0)
    , m_currentTrackNumber(0)
    , m_currentPosition(0)
    , m_duration(0)
    , m_playStatus(AVInformationTypesEnum::PlayStatus::STOP)
{

}


/// Q_PROPERTY
qint32 AVDataManager::source() const
{
    return m_source;
}
void AVDataManager::setSource(const qint32 &source)
{
    m_source = source;
    emit sourceChanged(m_source);
}

QString AVDataManager::title() const
{
    return m_title;
}
void AVDataManager::setTitle(const QString &title)
{
    m_title = title;
    emit titleChanged(m_title);
}

QString AVDataManager::album() const
{
    return m_album;
}
void AVDataManager::setAlbum(const QString &album)
{
    m_album = album;
    emit albumChanged(m_album);
}

QString AVDataManager::artist() const
{
    return m_artist;
}
void AVDataManager::setArtist(const QString &artist)
{
    m_artist = artist;
    emit artistChanged(m_artist);
}

QString AVDataManager::fileName() const
{
    return m_fileName;
}
void AVDataManager::setFileName(const QString &fileName)
{
    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

QString AVDataManager::frequency() const
{
    return m_frequency;
}
void AVDataManager::setFrequency(const QString &frequency)
{
    m_frequency = frequency;
    emit frequencyChanged(m_frequency);
}

QString AVDataManager::psName() const
{
    return m_psName;
}
void AVDataManager::setPsName(const QString &psName)
{
    m_psName = psName;
    emit psNameChanged(m_psName);
}

QString AVDataManager::presetIndex() const
{
    return m_presetIndex;
}
void AVDataManager::setPresetIndex(const QString &presetIndex)
{
    m_presetIndex = presetIndex;
    emit presetIndexChanged(m_presetIndex);
}

quint32 AVDataManager::totalTrackNumber() const
{
    return m_totalTrackNumber;
}
void AVDataManager::setTotalTrackNumber(const quint32 &totalTrackNumber)
{
    m_totalTrackNumber = totalTrackNumber;
    emit totalTrackNumberChanged(m_totalTrackNumber);
}

quint32 AVDataManager::currentTrackNumber() const
{
    return m_currentTrackNumber;
}
void AVDataManager::setCurrentTrackNumber(const quint32 &currentTrackNumber)
{
    m_currentTrackNumber = currentTrackNumber;
    emit currentTrackNumberChanged(m_currentTrackNumber);
}

quint32 AVDataManager::currentPosition() const
{
    return m_currentPosition;
}
void AVDataManager::setCurrentPosition(const quint32 &currentPosition)
{
    m_currentPosition = currentPosition;
    emit currentPositionChanged(m_currentPosition);
}

quint32 AVDataManager::duration() const
{
    return m_duration;
}
void AVDataManager::setDuration(const quint32 &duration)
{
    m_duration = duration;
    emit durationChanged(m_duration);
}

qint32 AVDataManager::playStatus() const
{
    return m_playStatus;
}
void AVDataManager::setPlayStatus(const qint32 &playStatus)
{
    m_playStatus = playStatus;
    emit playStatusChanged(m_playStatus);
}
/// Q_PROPERTY
