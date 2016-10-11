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
 * \file AVInformationTypesEnum.h
*/

#ifndef AVINFORMATIONTYPESENUM
#define AVINFORMATIONTYPESENUM

#include <QObject>

namespace AVInformationTypesEnum {

class Source : public QObject
{
    Q_OBJECT
public:
    enum Literal : int32_t {
        FM = 0,
        AM = 1,
        USB_MUSIC = 2,
        USB_VIDEO = 3
    };
    Q_ENUM(Literal)
};

class PlayStatus : public QObject
{
    Q_OBJECT
public:
    enum Literal : int32_t {
        PLAY = 0,
        PAUSE = 1,
        STOP = 2
    };
    Q_ENUM(Literal)
};

}

#endif // AVINFORMATIONTYPESENUM

