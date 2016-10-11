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
 * \file albumartprovider.cpp
*/

#include "AlbumArtProvider.h"
#include <QImage>

Q_LOGGING_CATEGORY(albumArtProvider, "cluster.hmi.albumArtProvider")

static AlbumArtProvider * albumArtProviderInstance = Q_NULLPTR;


AlbumArtProvider *AlbumArtProvider::instance()
{
    if( albumArtProviderInstance == Q_NULLPTR )
    {
        albumArtProviderInstance = new AlbumArtProvider(QQuickImageProvider::ImageType::Image);
        albumArtProviderInstance->init();
    }

    return albumArtProviderInstance;
}

void AlbumArtProvider::finalize()
{
    if ( albumArtProviderInstance != Q_NULLPTR )
    {
        delete albumArtProviderInstance;
        albumArtProviderInstance = Q_NULLPTR;
    }
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
    if(albumArt().isNull())
    {
        qCDebug(albumArtProvider()) << "m_albumArt1 is empty return null";
        return QImage();
    }
    else
    {
        qCDebug(albumArtProvider()) << "m_albumArt is" << m_albumArt;
        return m_albumArt;
    }
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
