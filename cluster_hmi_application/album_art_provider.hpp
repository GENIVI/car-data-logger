/*
* Copyright (C) 2017, IVIS
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
* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
*
* \copyright Copyright (c) 2017, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#ifndef ALBUMARTPROVIDER_H
#define ALBUMARTPROVIDER_H

#include <QQuickImageProvider>
#include <QSharedPointer>
#include <QLoggingCategory>
#include <QObject>

Q_DECLARE_LOGGING_CATEGORY(albumArtProvider)

class AlbumArtProvider : public QQuickImageProvider//,public QObject
{
//    Q_OBJECT
public:
    static QSharedPointer<AlbumArtProvider> instance();
    ~AlbumArtProvider();

private :
    explicit AlbumArtProvider(QQuickImageProvider::ImageType type = QQuickImageProvider::ImageType::Pixmap);
    void init();

public:
    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

    QImage albumArt() const;
    QPixmap albumArt2() const;
    void setAlbumArt(QImage albumArt);
    void setAlbumArt2(QPixmap albumArt2);

private:
    QImage m_albumArt;
    QPixmap m_albumArt2;
};

#endif // ALBUMARTPROVIDER_H
