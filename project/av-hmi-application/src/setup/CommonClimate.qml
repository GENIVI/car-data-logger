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
 * \file CommonClimate.qml
*/

import QtQuick 2.5

Item{
    id: setupClimateCommonWindow
    objectName: "setupClimateCommonComponent"

    property string climateDataTitle: "dafault"
    property int titleTextSize: 0

    property bool textTypeDataState: false
    property bool levelTypeImageDataState: false
    property bool boolTypeImageDataState: false

    property string imageDataPath: ""
    property string textData: ""
    property int textDataSize: 0

    property int levelTypeImageData: 0
    property bool boolTypeImageData: false

    width: 156
    height: 118

    Image{
        id: climateDateBox

        width: parent.width
        height: parent.height

        opacity: 0.6
        source: "image/DATC/Climate_bg.png"
    }

    Text{
        id: climateDataType

        width: setupClimateCommonWindow.width
        height: setupClimateCommonWindow.height/2

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: climateDataTitle
        font.pixelSize: titleTextSize
        font.family: "SpoqaHanSans"
        color: "white"
    }

    Item{
        id: dataDisplayLayout
        width: setupClimateCommonWindow.width
        height: setupClimateCommonWindow.height/2

        anchors.top: climateDataType.bottom

        Image{
            id: levelTypeImageDataDisplay

            visible: levelTypeImageDataState
            anchors.horizontalCenter: dataDisplayLayout.horizontalCenter

            source: imageDataPath
        }

        Image{
            id: boolTypeImageDataDisplay

            visible: boolTypeImageDataState
            anchors.horizontalCenter: dataDisplayLayout.horizontalCenter

            source: imageDataPath

            opacity: boolTypeImageData ? 1 : 0.3

            Behavior on opacity {
                NumberAnimation { duration: 150 }
            }
        }

        Text{
            id: climateTextDataDisplay

            visible: textTypeDataState

            anchors.centerIn: dataDisplayLayout

            text: textData + " ºc"
            font.pixelSize: textDataSize
            font.family: "SpoqaHanSans"
            color: "white"

        }
    }

}

