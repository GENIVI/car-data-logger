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
 * \file AlbumArt.qml
*/

import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: control

    width: 270
    height: 270
    //    source: "../image/bg/Center_Line_bg.png"

    property string imagePath: "../image/cover/1.jpg"
    property string titleText: AVDataManager.title //'IU - 스물셋 Title Text'

    Component.onCompleted: {
        privateObject.imagePath.connect(privateObject.moveItem.updateImage)
    }

    onImagePathChanged: {
        privateObject.imagePath(control.imagePath)
//        if (animation.running)
//        {
//            console.log(control.imagePath)
//            animation.complete()
//        }

//        animation.running = true
        run()
    }

    QtObject {
        id: privateObject
        property Item moveItem: item2
        property Item currentItem: item1

        signal imagePath(string path)
    }

    Item {
        width: 160
        height: 160
        anchors.centerIn: parent
        clip: true


        //        MouseArea {
        //            anchors.fill: parent

        //            onClicked: {
        //                if (animation.running)
        //                    animation.complete()

        //                animation.running = true

        //            }

        //        }




        Image {
            id: mask
            width: parent.width
            height: parent.height

            anchors.centerIn: parent
            source: "../image/bg/Center_bg.png"
            visible: false
        }

        Item {
            id: item1
            width: parent.width
            height: parent.height

            function updateImage(path) {
                image1.source = path
            }

            Image {
                id: image1
                anchors.fill: parent
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                opacity: 1
                z: 1
                source: "../image/cover/1.jpg"
                visible: false
            }

            OpacityMask {
                anchors.fill: image1
                source: image1
                maskSource: mask
                smooth: true
                antialiasing: true
            }

        }

        Item {
            id: item2
            x: -parent.width/3
            width: parent.width
            height: parent.height
            opacity: 0

            function updateImage(path) {
                image2.source = path
            }

            Image {
                id: image2
                anchors.fill: parent
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                opacity: 1
                z: 1
                source: "../image/cover/2.jpg"
                visible: false
            }

            OpacityMask {
                anchors.fill: image2
                source: image2
                maskSource: mask
                smooth: true
                antialiasing: true
            }
        }
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
        text: titleText
        color: "white"
        running: control.visible
    }

    function run()
    {
        if(animation.running)
        {
            animation.complete()
            swapObject()
        }

        animation.restart()
    }

    function swapObject () {
        var temp = privateObject.currentItem
        privateObject.currentItem = privateObject.moveItem
        privateObject.moveItem = temp
        privateObject.imagePath.disconnect(privateObject.currentItem.updateImage)
        privateObject.imagePath.connect(privateObject.moveItem.updateImage)
        console.log("dd", control.imagePath)
    }

    SequentialAnimation {
        id: animation
        PropertyAction { target: privateObject.currentItem; property: "z"; value: 0 }
        PropertyAction { target: privateObject.moveItem; property: "z"; value: 1 }

        ParallelAnimation {
            NumberAnimation { target: privateObject.moveItem; property: "x"; to: 0; duration: 300 }
            NumberAnimation { target: privateObject.moveItem; property: "opacity"; to: 1; duration: 300 }
        }

        PropertyAction { target: privateObject.currentItem; property: "opacity"; value: 0 }
        PropertyAction { target: privateObject.currentItem; property: "x"; value: -150/3 }

        ScriptAction { script: swapObject() }
    }
}
