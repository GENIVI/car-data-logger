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

    property string presetNumber: AVDataManager.presetIndex //23
    property string frequency: AVDataManager.frequency //'99.9'
    property string source: AVDataManager.psName //'FM'

    Text {
        id: text_radio_info

        y: control.height/3
        width: control.width/5*4
        height: 18

        anchors.horizontalCenter: control.horizontalCenter
    }

    Text {
        id: radio_frequency

        y: control.height/3+36

        width: control.width/5*3
        height: 50

        anchors.left: text_radio_info.left

        color: 'white'
        text: frequency
        font.family: 'SpoqaHanSans'
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
    }

    Text {
        id: radio_band

        width: text_radio_info.width-radio_frequency.width-4
        height: radio_frequency*5/3

        anchors.left: radio_frequency.right
        anchors.bottom: radio_frequency.bottom
        anchors.leftMargin: 4

        color: 'white'
        text: source
        font.family: 'SpoqaHanSans'
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 30
    }

    //    Text {
    //        id: text_preset
    //        width: id_preset_baseline.width
    //        anchors.baseline: id_preset_baseline.top
    //        anchors.horizontalCenter: id_preset_baseline.horizontalCenter
    //        color: 'white'
    //        text: presetNumber === '' ? '' : 'Preset ' + presetNumber
    //        font.family: 'SpoqaHanSans'
    //        font.bold: false
    //        font.pixelSize: 15
    //        horizontalAlignment: Text.AlignHCenter
    //    }
    //    Item {
    //        id: id_preset_baseline
    //        x: 325-318
    //        y: 204-157
    //        width: 149
    //        height: 1
    //        visible: false
    //    }
}
