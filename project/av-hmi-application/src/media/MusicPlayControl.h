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
 * \file MusicPlayControl.h
*/

#ifndef MUSICPLAYCONTROL_H
#define MUSICPLAYCONTROL_H

#include <QObject>
#include <com/ivis/ModeManager/ModeManagerProxy.hpp>
#include <com/ivis/MediaManager/PlaybackControlProxy.hpp>

using namespace v1::com::ivis::MediaManager;
using namespace v1::com::ivis::ModeManager;

class MusicPlayControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool playState READ playState NOTIFY playStateChanged)
    Q_PROPERTY(int mediaPlayTime READ mediaPlayTime WRITE setMediaPlayTime NOTIFY mediaPlayTimeChanged)
    Q_PROPERTY(int curPlayTime READ curPlayTime WRITE setCurPlayTime NOTIFY curPlayTimeChanged)
    Q_PROPERTY(int curMediaIndex READ curMediaIndex WRITE setcurMediaIndex NOTIFY curMediaIndexChanged)
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString albumArtPath READ albumArtPath WRITE setAlbumArtPath NOTIFY albumArtPathChanged)

public:
    static QSharedPointer<MusicPlayControl> instance (QObject *parent = Q_NULLPTR);
    ~MusicPlayControl();

private:
    explicit MusicPlayControl(QObject *parent = Q_NULLPTR);
    void init();

public:
    Q_INVOKABLE void requestPlayPause(bool checked);
    Q_INVOKABLE void requestPlay();
    Q_INVOKABLE void requestNext();
    Q_INVOKABLE void requestPrev();
    Q_INVOKABLE void progressbarPress(int value);
    Q_INVOKABLE void setMediaType(int mediaType);
    Q_INVOKABLE void progressbarPressState(bool state);

    bool playState() const;
    int curPlayTime() const;
    int curMediaIndex() const;
    int mediaPlayTime() const;
    QString artist() const;
    QString title() const;
    QString albumArtPath() const;

public slots:
    void setPlayState(bool playState);
    void setCurPlayTime(int curPlayTime);
    void setMediaPlayTime(int mediaPlayTime);
    void setcurMediaIndex(int curMediaIndex);
    void setTitle(QString title);
    void setArtist(QString artist);
    void setAlbumArtPath(QString albumArtPath);

signals:
    void playStateChanged(bool playState);
    void curPlayTimeChanged(int curPlayTime);
    void mediaPlayTimeChanged(int mediaPlayTime);
    void curMediaIndexChanged(int curMediaIndex);
    void titleChanged(QString title);
    void artistChanged(QString artist);
    void albumArtPathChanged(QString albumArtPath);

public:
    void onTotalTrackNumberChanged(const uint32_t & totalTrackNumber);
    void onCurrentTrackNumberChanged(const uint32_t & currentTrackNumber);
    void onTrackInfoChanged(const MediaManagerTypes::TrackInfo & trackInfo);
    void onTimePositionChanged(const MediaManagerTypes::TimePositionInfo & timePositionInfo);

private:
    std::shared_ptr<ModeManagerProxy<>> mModeManagerProxy;
    std::shared_ptr<PlaybackControlProxy<>> mPlaybackProxy;

private:
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

#endif // MUSICPLAYCONTROL_H
