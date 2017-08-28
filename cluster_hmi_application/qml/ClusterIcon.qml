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

import QtQuick 2.0

Item {
    id: control

    width: 52
    height: 52

    property string normalImage
    property string activeImage
    property bool actived: false

    Image {
        id: normal
        source: normalImage
        opacity: !actived ? 1 : 0
        visible: opacity !== 0

        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }

    Image {
        id: active
        source: activeImage
        opacity: actived ? 1 : 0
        visible: opacity !== 0

        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }
}

