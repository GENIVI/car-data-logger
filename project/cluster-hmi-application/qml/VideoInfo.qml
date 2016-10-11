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
 * \file VideoInfo.qml
*/

import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: control

    width: 270
    height: 270

    property string fileName: AVDataManager.fileName //'AOA - 사뿐사뿐(Like a Cat) Music Video.mp4'

    Image {
        id: background
        anchors.centerIn: parent
        source: '../image/bg/Center_bg.png'
    }

    MarqueeLabel {
        id: text_title
        width: 149
        height: 40
        fontFamily: "SpoqaHanSans"
        scrollingTextMargin: 20
        fontSize: 26
        fontStyle: Text.Outline
        fontBold: true
        baselineOffset: -12
        anchors.bottom: parent.top
        anchors.bottomMargin: -156
        anchors.horizontalCenter: parent.horizontalCenter
        text: fileName
        color: "white"
        running: control.visible
    }
}
