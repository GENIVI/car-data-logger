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
 * \file VideoPlayControl.h
*/

#ifndef VIDEOPLAYCONTROL_H
#define VIDEOPLAYCONTROL_H

#include <QObject>
#include <com/ivis/MediaManager/PlaybackControlProxy.hpp>

#define MAX_MEDIA_COUNT 5

using namespace v1::com::ivis::MediaManager;

typedef struct MEDIA_INFO{
    QString title;
    QString albumArtPath;
    int mediaPlayTime;
}VIDEO_TYPE_INFO;


class VideoPlayControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool playState READ playState  NOTIFY playStateChanged)
    Q_PROPERTY(int mediaPlayTime READ mediaPlayTime WRITE setMediaPlayTime NOTIFY mediaPlayTimeChanged)
    Q_PROPERTY(int curPlayTime READ curPlayTime WRITE setCurPlayTime NOTIFY curPlayTimeChanged)
    Q_PROPERTY(int curMediaIndex READ curMediaIndex WRITE setcurMediaIndex NOTIFY curMediaIndexChanged)
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString albumArtPath READ albumArtPath WRITE setAlbumArtPath NOTIFY albumArtPathChanged)
    Q_PROPERTY(bool driveRestrict READ driveRestrict WRITE setDriveRestrict NOTIFY driveRestrictChanged)

public:
    static QSharedPointer<VideoPlayControl> instance (QObject *parent = Q_NULLPTR);
    ~VideoPlayControl();

private:
    explicit VideoPlayControl(QObject *parent = Q_NULLPTR);
    void init();
public:



public:
    Q_INVOKABLE void requestPlayPause(bool checked);
    Q_INVOKABLE void requestNext();
    Q_INVOKABLE void requestPrev();
    Q_INVOKABLE void progressbarPress(int value);
    Q_INVOKABLE void setMediaType(int mediaType);
    Q_INVOKABLE void progressbarPressState(bool state);

    bool playState() const;
    bool driveRestrict() const;
    int curPlayTime() const;
    int curMediaIndex() const;
    int mediaPlayTime() const;
    QString artist() const;
    QString title() const;
    QString albumArtPath() const;

public slots:
    void setDriveRestrict(bool driveRestrict);
    void setPlayState(bool playState);
    void setCurPlayTime(int curPlayTime);
    void setcurMediaIndex(int curMediaIndex);
    void setMediaPlayTime(int mediaPlayTime);
    void setArtist(QString artist);
    void setTitle(QString title);
    void setAlbumArtPath(QString albumArtPath);

signals:
    void driveRestrictChanged(bool driveRestrict);
    void playStateChanged(bool playState);
    void curPlayTimeChanged(int curPlayTime);
    void curMediaIndexChanged(int curMediaIndex);
    void mediaPlayTimeChanged(int mediaPlayTime);
    void artistChanged(QString artist);
    void titleChanged(QString title);
    void albumArtPathChanged(QString albumArtPath);

public:
    void onTrackInfoChanged(const MediaManagerTypes::TrackInfo & trackInfo);
    void onTimePositionChanged(const MediaManagerTypes::TimePositionInfo & timePositionInfo);

private:
    std::shared_ptr<PlaybackControlProxy<>> mPlayBackProxy;

private:    
    bool m_driveRestrict;
    bool m_playState;
    bool m_progressbarState;

    int m_curPlayTime;
    int m_mediaPlayTime;
    int m_curPlayIndex;
    int m_curMediaIndex;
    int m_mediaType;

    QString m_title;
    QString m_artist;
    QString m_albumArtPath;
};

#endif // VIDEOPLAYCONTROL_H
