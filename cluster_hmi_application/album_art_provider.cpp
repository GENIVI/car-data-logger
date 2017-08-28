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

#include "album_art_provider.hpp"
#include <QImage>

Q_LOGGING_CATEGORY(albumArtProvider, "cluster.hmi.albumArtProvider")

static QSharedPointer<AlbumArtProvider> albumArtProviderInstance;


QSharedPointer<AlbumArtProvider> AlbumArtProvider::instance()
{
    if(albumArtProviderInstance.isNull())
    {
        albumArtProviderInstance = QSharedPointer<AlbumArtProvider> (new AlbumArtProvider(QQuickImageProvider::ImageType::Image));
        albumArtProviderInstance.data()->init();
    }
    return albumArtProviderInstance;
}

AlbumArtProvider::~AlbumArtProvider()
{

}

AlbumArtProvider::AlbumArtProvider(QQuickImageProvider::ImageType type)
    :QQuickImageProvider(type)
    ,m_albumArt()
    ,m_albumArt2()
{

}

void AlbumArtProvider::init()
{
}

QImage AlbumArtProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

    QString path("/home/minseok/Linux_Av/cluster-hmi-application/testimages.jpg");
//////temp ====

    QImage tempImage(path);

/////======

    if(albumArt().isNull())
    {
        qCDebug(albumArtProvider()) << "m_albumArt1 is empty return null";
        return tempImage;
    }
    else
    {
        qCDebug(albumArtProvider()) << "m_albumArt is" << m_albumArt;
        return m_albumArt;
    }


////    if avinformation providerhelper send QImage to m_albumArt
////    change scale
}

QPixmap AlbumArtProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
//    id = in qml image://AlbumArtProvider/id
//    requestedSize = in qml image size

    //    tempcode
//    QString path("/home/minseok/Linux_Av/cluster-hmi-application/testimages2.jpg");
//    QPixmap tempPixmap(path);
//    tempPixmap.scaledToHeight(requestedSize.height());
//    tempPixmap.scaledToWidth(requestedSize.width());


//    return tempPixmap;

    // if avinformation provider send QPixMap to m_albumArt2
     //change scale
     //return m_albumArt2;

}


QImage AlbumArtProvider::albumArt() const
{
    return m_albumArt;
}

QPixmap AlbumArtProvider::albumArt2() const
{
    return m_albumArt2;
}

void AlbumArtProvider::setAlbumArt(QImage albumArt)
{
    m_albumArt = albumArt;
}

void AlbumArtProvider::setAlbumArt2(QPixmap albumArt2)
{
    m_albumArt2 = albumArt2;
}
