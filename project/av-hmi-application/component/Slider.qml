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

    property bool sliderProgressState: false

    property int currentMouseX: 0
    property int value: 10
    property int maximum: 20
    property int minimum: 0
    property int interval:maximum-minimum

    signal signalClicked
    signal signalPressed
    signal signalReleased
    signal signalPressedLong

    Rectangle{
        id:sliderBar
        width: sliderWidth
        height: sliderHeight
        anchors.horizontalCenter: mainSlider.horizontalCenter
        anchors.verticalCenter: mainSlider.verticalCenter
        color : sliderColor
        radius: 8

        Component.onCompleted: {

        }
        MouseArea{
            id : mouseArea

            anchors.centerIn: sliderBar
            width: sliderBar.width
            height: sliderBar.height * 3
            onClicked: {
                signalClicked()
            }
            onPressed: {
                signalPressed()
                sliderPointer.opacity=0.3
            }
            onReleased: {
                signalReleased()
                sliderPointer.opacity=0.9
            }
            onPressAndHold: {
                signalPressedLong()
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
    }

    Item{
        id:sliderPointer
        width: sliderPointerWidth
        height: sliderPointerHeight
        x :  (sliderBar.x + ( (sliderBar.width / interval) * value)) - sliderPointer.width/2
        anchors.verticalCenter: sliderBar.verticalCenter
        opacity: 0.9
        Rectangle{
            id: sliderPointerRect
            width: sliderPointer.width
            height: sliderPointer.height
            color: sliderPointerColor
            radius  : 12
        }
    }

    Rectangle{
        id: sliderProgressLayout

        width: sliderPointer.x-10
        height: sliderBar.height
        visible: sliderProgressState

        anchors.verticalCenter: sliderBar.verticalCenter
        anchors.left: sliderBar.left


        radius: 8
        color: "skyblue"
    }
}

