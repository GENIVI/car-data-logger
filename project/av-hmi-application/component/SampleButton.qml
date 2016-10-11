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
 * \file SampleButton.qml
*/

import QtQuick 2.5

Rectangle {
    id: sampleButtonComponent

    property int buttonWidth: 0
    property int buttonHeight: 0
    property string buttonText: ""
    property int isState: 0xFFFF // true(1) : tabButton / false(0) : backButton
    property color customButtonColor: "#222222"
    property color buttonColor: {
        if(buttonFocus==true)
        {
            if(buttonTouchArea.pressed) "skyblue"
            else                        customButtonColor
        }
        else
        {
            "#110000"
        }
    }

    property color buttonTextColor: {
        if(buttonFocus==true)
        {
            if(buttonTouchArea.pressed) "black"
            else                        "white"
        }
        else
        {
            "#666666"
        }
    }
    property int buttonTextSize: 0
    property bool buttonFocus: true

    signal touchPressed()
    signal touchReleased()
    signal touchLongPressed()

    width: buttonWidth
    height: buttonHeight
    radius: 5
    focus: buttonFocus

    color: buttonColor    

    Text{
        id: buttonTextArea
        text: buttonText
        font.pixelSize: buttonTextSize
        font.bold: true
        font.family: "SpoqaHanSans"
        color: buttonTextColor
        anchors.centerIn: parent
    }

    MouseArea{
        id: buttonTouchArea
        anchors.fill: parent
        onPressed: {
            sampleButtonComponent.touchPressed()
        }
        onReleased: {
            sampleButtonComponent.touchReleased()
        }
        onPressAndHold: {
            sampleButtonComponent.touchLongPressed()
        }
    }
}
