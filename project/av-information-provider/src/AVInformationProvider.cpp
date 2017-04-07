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
 * \file AVInformationProvider.cpp
*/

#include "AVInformationProvider.h"
#include <CommonAPI/CommonAPI.hpp>
#include <QPixmap>
#include <QIODevice>
#include <QBuffer>
#include <QThread>
#include <QDebug>

AVInformationProvider::AVInformationProvider(QObject * parent)
    : QObject(parent)
    , m_source(AVInformationTypes::Source::FM)
{
    DLT_REGISTER_CONTEXT(mContext, "avis", "AV Information Service");

    mAVInformation = std::make_shared<AVInformationStubDefault>();
    auto runtime = CommonAPI::Runtime::get();

    mModeManager = runtime->buildProxy<ModeManagerProxy>("local", "com.ivis.ModeManager.ModeManager");
    mPlayback = runtime->buildProxy<PlaybackControlProxy>("local", "com.ivis.MediaManager.PlaybackControl");

    runtime->registerService("local", "com.ivis.AVInformationProvider.AVInformation.SomeIp", mAVInformation);

    mModeManager->getActiveApplicationAttribute().getChangedEvent().subscribe(
                std::bind(&AVInformationProvider::activeApplicationChanged, this, std::placeholders::_1));


    mPlayback->getCurrentTrackInfoAttribute().getChangedEvent().subscribe(
                std::bind(&AVInformationProvider::currentTrackInfoChanged, this, std::placeholders::_1));

    mPlayback->getCurrentTrackNumberAttribute().getChangedEvent().subscribe(
                std::bind(&AVInformationProvider::currentTrackNumberChanged, this, std::placeholders::_1));

    mPlayback->getTotalTrackNumberAttribute().getChangedEvent().subscribe(
                std::bind(&AVInformationProvider::totalTrackNumberChanged, this, std::placeholders::_1));

    mPlayback->getPlayStateInfoAttribute().getChangedEvent().subscribe(
                std::bind(&AVInformationProvider::playStateChanged, this, std::placeholders::_1));

    mPlayback->getNotifiyTimePositionInfoChangedEvent().subscribe(
                std::bind(&AVInformationProvider::timePositionInfoChanged, this, std::placeholders::_1));
}

AVInformationProvider::~AVInformationProvider()
{
    auto runtime = CommonAPI::Runtime::get();

    runtime->unregisterService("local", AVInformation::getInterface(), "com.ivis.AVInformationProvider.AVInformation.SomeIp");
    mAVInformation = nullptr;

    DLT_UNREGISTER_CONTEXT(mContext);
}

void AVInformationProvider::activeApplicationChanged(const ModeManagerTypes::ApplicationInfo & activeApplicationInfo)
{
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO) );

    switch(activeApplicationInfo.getApp())
    {
    case ModeManagerTypes::ApplicationType::APP_FM:
        m_source = AVInformationTypes::Source::FM;
        break;

    case ModeManagerTypes::ApplicationType::APP_AM:
        m_source = AVInformationTypes::Source::AM;
        break;

    case ModeManagerTypes::ApplicationType::APP_USB:
        if (activeApplicationInfo.getSubApp() == ModeManagerTypes::SubApplicationType::SUB_APP_VIDEO)
        {
            m_source = AVInformationTypes::Source::USB_VIDEO;
        }
        else
        {
            m_source = AVInformationTypes::Source::USB_MUSIC;
        }
        break;

    default:
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING(Q_FUNC_INFO), DLT_STRING("out of case active application !!") );
        return;
    }

    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO), DLT_INT32(m_source) );
    mAVInformation->setCurrentSourceAttribute(m_source);
}

void AVInformationProvider::currentTrackInfoChanged(const MediaManagerTypes::TrackInfo & trackInfo)
{
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO) );

    AVInformationTypes::MetaData metaData = mAVInformation->getMetaDataAttribute();

    if (m_source == AVInformationTypes::Source::USB_MUSIC)
    {
        metaData.setTitle(trackInfo.getTitle());
        metaData.setAlbum(trackInfo.getAlbum());
        metaData.setArtist(trackInfo.getArtist());

        mAVInformation->setMetaDataAttribute(metaData);

        QString coverArtPath = QString::fromStdString(trackInfo.getAlbumArtPath());

        load_image_resize(coverArtPath);

        send_image(mBuffer);
    }
    else if (m_source == AVInformationTypes::Source::USB_VIDEO)
    {
        metaData.setTitle(trackInfo.getTitle());
        metaData.setAlbum(trackInfo.getAlbum());
        metaData.setArtist(trackInfo.getArtist());

        mAVInformation->setMetaDataAttribute(metaData);
    }
    else
    {
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING(Q_FUNC_INFO), DLT_STRING("active app is not media !!") );
        return;
    }
}

void AVInformationProvider::currentTrackNumberChanged(uint32_t currentTrackNumber)
{
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO) );

    AVInformationTypes::MetaData metaData = mAVInformation->getMetaDataAttribute();

    metaData.setCurrentTrackNumber(currentTrackNumber);

    mAVInformation->setMetaDataAttribute(metaData);
}

void AVInformationProvider::totalTrackNumberChanged(uint32_t totalTrackNumber)
{
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO) );

    AVInformationTypes::MetaData metaData = mAVInformation->getMetaDataAttribute();

    metaData.setTotalTrackNumber(totalTrackNumber);

    mAVInformation->setMetaDataAttribute(metaData);
}

void AVInformationProvider::playStateChanged(const MediaManagerTypes::PlayStateInfo & playStateInfo)
{
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO) );

    AVInformationTypes::PlayStatus playStatus = AVInformationTypes::PlayStatus::PLAY;

    switch(playStateInfo.getState())
    {
    case MediaManagerTypes::Action::PLAY:
        playStatus = AVInformationTypes::PlayStatus::PLAY;
        break;

    case MediaManagerTypes::Action::PAUSE:
        playStatus = AVInformationTypes::PlayStatus::PAUSE;
        break;

    case MediaManagerTypes::Action::STOP:
        playStatus = AVInformationTypes::PlayStatus::STOP;
        break;

    default:
        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING(Q_FUNC_INFO), DLT_STRING("out of case play state !!") );
        return;
    }

    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO), DLT_INT32(playStatus) );
    mAVInformation->setPlayStatusAttribute(playStatus);
}

void AVInformationProvider::timePositionInfoChanged(const MediaManagerTypes::TimePositionInfo & timePositionInfo)
{
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO) );

    mAVInformation->setPlayPositionAttribute(AVInformationTypes::PlayPosition(timePositionInfo.getCurrentTimePosition(), timePositionInfo.getTotalTimeLength()));
}

void AVInformationProvider::load_image_resize(QString image_filename)
{
    QString _filename = image_filename;

    qDebug() << "image name = " << _filename;

    QPixmap image;
    image.load(_filename);

    if ( image.width() > 200 || image.height() > 200 )
    {
        image = image.scaled(200, 200, Qt::KeepAspectRatio);
    }

    QByteArray bytes;
    QBuffer buffer(&bytes);

    buffer.open(QIODevice::WriteOnly);
    bool val = image.save(&buffer, "jpg");

    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO), DLT_STRING("image resize success = "), DLT_BOOL(val) );
    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO), DLT_STRING("bytes size = "), DLT_INT(bytes.size()) );

    mBuffer.clear();
    for (int i = 0; i < bytes.size(); i++)
    {
        mBuffer.push_back( bytes.at(i) );
    }
}

void AVInformationProvider::send_image(std::vector<uint8_t> &data)
{
    QVector<int> tr_size;
    std::vector< std::vector<uint8_t> > part_list;
    int total_parts = 0;

    int size = data.size();
    total_parts = (size / 1024);

    tr_size.clear();

    for (int i = 0; i < total_parts; i++)
    {
        tr_size.push_back(1024);
    }

    if ( size % 1024 )
    {
        tr_size.push_back( size % 1024 );
    }

    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING(Q_FUNC_INFO), DLT_STRING("total part count = "), DLT_INT(tr_size.size()) );

    part_list.clear();

    for (int i = 0; i < tr_size.size(); i++)
    {
        int part_size = tr_size.at(i);

        part_list.push_back( std::vector<uint8_t>() );

        for (int j = 0 ; j < part_size; j++)
        {
            part_list.at(i).push_back( data.at((i * 1024) + j));
        }
    }

    for (int i = 0; i < tr_size.size(); i++)
    {
        mAVInformation->fireNotifyAlbumArtEvent(tr_size.size(), i + 1, part_list.at(i));

        QThread::currentThread()->msleep(1);
    }
}
