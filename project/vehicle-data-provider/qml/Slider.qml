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
 * \file Slider.qml
*/

import QtQuick 2.5
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0

Item{
    id:mainSlider
    width : 640
    height: 40

    property int sliderWidth: 100
    property int sliderHeight: 20
    property color sliderColor: "gray"

    property int sliderPointerWidth: 20
    property int sliderPointerHeight: 20
    property color sliderPointerColor: "skyblue"

    property int currentMouseX: 0
    property int value: 10
    property int maximum: 20
    property int minimum: 0
    property int interval:maximum-minimum
    signal signalClicked

    MouseArea{
            id : mouseArea
            anchors.fill:  sliderBar
            anchors.centerIn: sliderBar
            width: sliderBar.width+40
            height: sliderBar.height * 10
            onClicked: {
                signalClicked()
            }

            onMouseXChanged: {
                var absValue

                currentMouseX=mouseX
                absValue = currentMouseX / (sliderBar.width/interval)

                if( absValue>=minimum && absValue<=maximum)
                {
                    value=absValue
                }
            }
        }

    Rectangle{
        id:sliderBar
        width: sliderWidth
        height: sliderHeight
        anchors.horizontalCenter: mainSlider.horizontalCenter
        anchors.verticalCenter: mainSlider.verticalCenter
        color : sliderColor
        radius: 8

    }

    Item{
        id:sliderPointer
        width: sliderPointerWidth
        height: sliderPointerHeight
        x :  (sliderBar.x + ( (sliderBar.width / interval) * value)) - sliderPointer.width/2
        anchors.verticalCenter: sliderBar.verticalCenter

        Rectangle{
            width: sliderPointer.width
            height: sliderPointer.height
            color: sliderPointerColor

            radius  : 12
        }
    }
}

