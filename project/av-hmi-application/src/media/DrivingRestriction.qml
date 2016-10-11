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
 * \file DrivingRestriction.qml
*/

import QtQuick 2.5


Item {
    id: drivingRestrictionLayout
    objectName: "DrivingRestriction"

    width: 800
    height: 420

    Image{
        id: restrictionBg

        anchors.fill: parent
        source: "qrc:/media/image/warning_bg.png"
    }

    Image{
        width: 70
        height: 70
        y: 100

        anchors.horizontalCenter: restrictionBg.horizontalCenter

        source: "image/Media_Icon_Warning.png"
    }

    Text{
        width: 800
        height: 200

        y: 140

        text: "Video has been stopped for safety.\nThe video can be watched while in Park."

        font.pixelSize:25
        font.bold: true
        font.family: "SpoqaHanSans"
        color: "white"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Component.onCompleted: {

    }
}
