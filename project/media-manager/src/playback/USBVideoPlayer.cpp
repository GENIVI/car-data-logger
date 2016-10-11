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
 * \file USBVideoPlayer.cpp
*/

#include "USBVideoPlayer.h"
#include <QDir>

USBVideoPlayer::USBVideoPlayer()
{
    std::string currentPath = QDir::currentPath().toStdString() + "/..";
    currentPath += "/cover-art/";

    mPlaylist.push_back(MediaManagerTypes::TrackInfo(11,  1, 304, "Heart Attack - AOA",          "", "", "", currentPath + "11.JPG" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(12,  1, 255, "SHAKE IT - SISTAR",           "", "", "", currentPath + "15.JPG" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(13,  1, 235, "Kitties",                     "", "", "", currentPath + "14.JPG" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(14,  1, 293, "HELLO BUBBLE - GIRL'S DAY",   "", "", "", currentPath + "13.JPG" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(15,  1, 278, "Bloom - GAIN",                "", "", "", currentPath + "12.JPG" , ""));
}

USBVideoPlayer::~USBVideoPlayer()
{

}
