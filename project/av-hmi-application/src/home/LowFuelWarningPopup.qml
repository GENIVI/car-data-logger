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
 * \file LowFuelWarningPopup.qml
*/

import QtQuick 2.5


Item {
    id: lowFuelWarningLayout
    objectName: "LowFuelWarning"
    y: 40
    width: 800
    height: 440

    MouseArea{
        anchors.fill: parent
    }

    Image{
        id: lowfuelWarningBackGround

        anchors.fill: parent
        source: "qrc:/home/image/Popup_BackView.png"
        opacity: 0.5
    }

    Item{
        id: lowFuelWarningPopUpLayout

        width: 450
        height: 230

        anchors.centerIn: parent

        Image{
            id: lowFuelWarningPopupBg
            anchors.fill: parent

            source: "qrc:/home/image/Popup_BG_Normal.png"
        }

        Image{
            id: lowFuelWarningIamge
            width: 40
            height: 40
            x: 70
            y: lowFuelWarningPopUpLayout.height/3

            source: "qrc:/media/image/Media_Icon_Warning.png"
        }

        Text{
            id: lowFuelWarningMessage

            width: 200
            height: 30
            x:130

            anchors.verticalCenter: lowFuelWarningIamge.verticalCenter
            text: "Low Fuel Warning!!!"
            font.pixelSize:25
            font.bold: true
            font.family: "SpoqaHanSans"
            color: "white"
        }

        Item {
            id: okButton

            width: 150
            height: 30

            anchors.horizontalCenter: lowFuelWarningPopUpLayout.horizontalCenter
            anchors.bottom: lowFuelWarningPopUpLayout.bottom
            anchors.bottomMargin: 30
            opacity: okButtonMouseArea.pressed? 0.5 : 1

            Image {
                id: okButtonBg
                anchors.fill: parent
                source: "qrc:/home/image/Popup_Button_Normal.png"
            }

            Text{
                id: okButtonText
                width: okButton.width
                height: okButton.height

                text: "OK"
                font.pixelSize:25
                font.bold: true
                font.family: "SpoqaHanSans"
                color: "white"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea{
                id: okButtonMouseArea
                anchors.fill: parent

                onClicked: {
                    ModeManager.setLowFuelWarningState(false)
                }
            }
        }
    }

    Component.onCompleted: {

    }
}
