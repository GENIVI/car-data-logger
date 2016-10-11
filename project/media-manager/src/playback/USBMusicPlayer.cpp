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
 * \file USBMusicPlayer.cpp
*/

#include "USBMusicPlayer.h"
#include <QDir>
#include <QDebug>

USBMusicPlayer::USBMusicPlayer()
{
    std::string currentPath = QDir::currentPath().toStdString() + "/..";
    currentPath += "/cover-art/";

    mPlaylist.push_back(MediaManagerTypes::TrackInfo(1,  1, 324, "Work",                    "Rihanna",              "", "", currentPath + "1.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(2,  1, 235, "Love Yourself",           "Justin Bieber",        "", "", currentPath + "2.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(3,  1, 215, "Stressed Out",            "Twenty One Pilots",    "", "", currentPath + "3.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(4,  1, 193, "My House",                "Flo Rida",             "", "", currentPath + "4.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(5,  1, 238, "7 Years",                 "Likas Graham",         "", "", currentPath + "5.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(6,  1, 205, "Pillowtalk",              "Zayn",                 "", "", currentPath + "6.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(7,  1, 254, "Me, Myself & I",          "G-Eazy x Bebe Rexha",  "", "", currentPath + "7.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(8,  1, 213, "Cake By The Ocean",       "DNCE",                 "", "", currentPath + "8.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(9,  1, 283, "I Took A Pill In Ibiza",  "Mike Posner",          "", "", currentPath + "9.jpg" , ""));
    mPlaylist.push_back(MediaManagerTypes::TrackInfo(10, 1, 221, "No",                      "Meghan Trainor",       "", "", currentPath + "10.jpg", ""));
}

USBMusicPlayer::~USBMusicPlayer()
{

}
