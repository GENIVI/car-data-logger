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
 * \file AVDataManager.h
*/

#ifndef AVDATAMANAGER_H
#define AVDATAMANAGER_H

#include <QObject>

class AVDataManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32  source             READ source             WRITE setSource             NOTIFY sourceChanged)
    Q_PROPERTY(QString title              READ title              WRITE setTitle              NOTIFY titleChanged)
    Q_PROPERTY(QString album              READ album              WRITE setAlbum              NOTIFY albumChanged)
    Q_PROPERTY(QString artist             READ artist             WRITE setArtist             NOTIFY artistChanged)
    Q_PROPERTY(QString fileName           READ fileName           WRITE setFileName           NOTIFY fileNameChanged)
    Q_PROPERTY(QString frequency          READ frequency          WRITE setFrequency          NOTIFY frequencyChanged)
    Q_PROPERTY(QString psName             READ psName             WRITE setPsName             NOTIFY psNameChanged)
    Q_PROPERTY(QString presetIndex        READ presetIndex        WRITE setPresetIndex        NOTIFY presetIndexChanged)
    Q_PROPERTY(quint32 totalTrackNumber   READ totalTrackNumber   WRITE setTotalTrackNumber   NOTIFY totalTrackNumberChanged)
    Q_PROPERTY(quint32 currentTrackNumber READ currentTrackNumber WRITE setCurrentTrackNumber NOTIFY currentTrackNumberChanged)
    Q_PROPERTY(quint32 currentPosition    READ currentPosition    WRITE setCurrentPosition    NOTIFY currentPositionChanged)
    Q_PROPERTY(quint32 duration           READ duration           WRITE setDuration           NOTIFY durationChanged)
    Q_PROPERTY(qint32  playStatus         READ playStatus         WRITE setPlayStatus         NOTIFY playStatusChanged)

public:
    static AVDataManager * instance();
    static void finalize();

    void init();

private:
    // Q_PROPERTY
    qint32 m_source;
    QString m_title;
    QString m_album;
    QString m_artist;
    QString m_fileName;
    QString m_frequency;
    QString m_psName;
    QString m_presetIndex;
    quint32 m_totalTrackNumber;
    quint32 m_currentTrackNumber;
    quint32 m_currentPosition;
    quint32 m_duration;
    qint32 m_playStatus;

public:
    // Q_PROPERTY getter setter
    qint32 source() const;
    void setSource(const qint32 &source);

    QString title() const;
    void setTitle(const QString &title);

    QString album() const;
    void setAlbum(const QString &album);

    QString artist() const;
    void setArtist(const QString &artist);

    QString fileName() const;
    void setFileName(const QString &fileName);

    QString frequency() const;
    void setFrequency(const QString &frequency);

    QString psName() const;
    void setPsName(const QString &psName);

    QString presetIndex() const;
    void setPresetIndex(const QString &presetIndex);

    quint32 totalTrackNumber() const;
    void setTotalTrackNumber(const quint32 &totalTrackNumber);

    quint32 currentTrackNumber() const;
    void setCurrentTrackNumber(const quint32 &currentTrackNumber);

    quint32 currentPosition() const;
    void setCurrentPosition(const quint32 &currentPosition);

    quint32 duration() const;
    void setDuration(const quint32 &duration);

    qint32 playStatus() const;
    void setPlayStatus(const qint32 &playStatus);

signals:
    // Q_PROPERTY signal
    void sourceChanged(qint32 source);
    void titleChanged(QString title);
    void albumChanged(QString album);
    void artistChanged(QString artist);
    void fileNameChanged(QString fileName);
    void frequencyChanged(QString frequency);
    void psNameChanged(QString psName);
    void presetIndexChanged(QString presetIndex);
    void totalTrackNumberChanged(quint32 totalTrackNumber);
    void currentTrackNumberChanged(quint32 currentTrackNumber);
    void currentPositionChanged(quint32 currentPosition);
    void durationChanged(quint32 duration);
    void playStatusChanged(qint32 playStatus);
    void albumArtChanged();
private:
    explicit AVDataManager(QObject *parent = Q_NULLPTR);

};

#endif // AVDATAMANAGER_H
