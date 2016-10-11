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
 * \file RadioInfo.qml
*/

import QtQuick 2.0

Item {
    id: control

    width: 164
    height: 164

    property string presetNumber: AVDataManager.presetIndex //23
    property string frequency: AVDataManager.frequency //'99.9'
    property string source: AVDataManager.psName //'FM'

    Image {
        id: background
        x: -0.5
        y: -0.5
        source: '../image/bg/Center_bg.png'
    }

    Text {
        id: text_preset
        width: id_preset_baseline.width
        anchors.baseline: id_preset_baseline.top
        anchors.horizontalCenter: id_preset_baseline.horizontalCenter
        color: 'white'
        text: presetNumber === '' ? '' : 'Preset ' + presetNumber
        font.family: 'SpoqaHanSans'
        font.bold: false
        font.pixelSize: 15
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_preset_baseline
        x: 325-318
        y: 204-157
        width: 149
        height: 1
        visible: false
    }

    Text {
        id: text_frequency
        width: id_frequency_baseline.width
        anchors.baseline: id_frequency_baseline.top
        anchors.horizontalCenter: id_frequency_baseline.horizontalCenter
        color: 'white'
        text: frequency
        font.family: 'SpoqaHanSans'
        font.bold: true
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_frequency_baseline
        x: 325-318
        y: 249-157
        width: 149
        height: 1
        visible: false
    }

    Text {
        id: text_source
        width: id_source_baseline.width
        anchors.baseline: id_source_baseline.top
        anchors.horizontalCenter: id_source_baseline.horizontalCenter
        color: 'white'
        text: source
        font.family: 'SpoqaHanSans'
        font.bold: false
        font.pixelSize: 15
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_source_baseline
        x: 325-318
        y: 281-157
        width: 149
        height: 1
        visible: false
    }
}
