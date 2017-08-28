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
import QtGraphicalEffects 1.0


Item {
    id: control

    width: 345
    height: 320
    //    source: "../image/bg/Center_Line_bg.png"

    property string imagePath: "../image/cover/1.jpg"
    property string titleText: AVDataManager.title //'IU - 스물셋 Title Text'
    property string artist: AVDataManager.artist
    property string curPosition
    property int min
    property int sec

    Connections{
        target: AVDataManager

        onCurrentPositionChanged: {
            curPosition = calTimePosition(currentPosition)
        }

        onArtistChanged: {
            print(artist)
        }
    }

    function calTimePosition(curPos)
    {
        min=curPos/60
        sec=curPos%60

        if( min < 10 )
        {
            if( sec < 10 )
            {
                curPosition = "0"+min.toString()+" : "+"0"+sec.toString()
            }
            else
            {
                curPosition = "0"+min.toString()+" : "+sec.toString()
            }
        }
        else
        {
            if( sec < 10 )
            {
                curPosition = min.toString()+" : "+"0"+sec.toString()
            }
            else
            {
                curPosition = min.toString()+" : "+sec.toString()
            }
        }

        return curPosition
    }

    Component.onCompleted: {
        privateObject.imagePath.connect(privateObject.moveItem.updateImage)
    }


    onImagePathChanged: {
        privateObject.imagePath(control.imagePath)
        run()
    }

    QtObject {
        id: privateObject
        property Item moveItem: item2
        property Item currentItem: item1

        signal imagePath(string path)
    }

    Item {
        width: 265
        height: 300
        anchors.horizontalCenter: control.horizontalCenter
        anchors.top: control.top
        anchors.topMargin: 10
        clip: true

        Item {
            id: item1
            width: parent.width
            height: parent.height

            function updateImage(path) {
                image1.source = path
                image1.visible = true
                image1Mirror.visible = true
                image2.visible=false
                image2Mirror.visible=false
            }

            Image {
                id: image1
                width: parent.width/5*4
                height: parent.width/5*4
                anchors.horizontalCenter: item1.horizontalCenter
                opacity: 1
                z: 1
                source: "../image/cover/1.jpg"
                visible: false
            }

            Item {
                id: image1Mirror
                width: image1.width; height: image1.height
                anchors.horizontalCenter: image1.horizontalCenter
                visible: false
                // transform this item (the image and rectangle) to create the
                // mirror image using the values from the Path
                transform : [
                    Rotation {
                        angle: 180; origin.y: image1.height
                        axis.x: 1; axis.y: 0; axis.z: 0
                    },

                    Scale {
                        xScale: 1; yScale: 1
                        origin.x: image1.width/2; origin.y: image1.height/2
                    }
                ]

                // mirror image
                Image {
                    width: image1.width
                    height: image1.height

                    source: image1.source
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: image1.width; height: image1.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        gradient: Gradient {
                            // TODO: no clue how to get the RGB component of the container rectangle color
                            GradientStop { position: 0; color: "black" }
                            GradientStop { position: 0.8; color: "black" }
                            GradientStop { position: 1.0; color: "white" }
                        }
                        opacity: 1
                    }

                    opacity: 0.5
                }
            }
        }

        Item {
            id: item2
            width: parent.width
            height: parent.height

            function updateImage(path) {
                image2.source = path
                image2.visible = true
                image2Mirror.visible = true
                image1.visible=false
                image1Mirror.visible=false
            }

            Image {
                id: image2
                width: parent.width/5*4
                height: parent.width/5*4
                anchors.horizontalCenter: item2.horizontalCenter
                opacity: 1
                z: 1
                source: "../image/cover/2.jpg"
                visible: false
            }

            Item {
                id: image2Mirror
                width: image2.width; height: image2.height
                anchors.horizontalCenter: image2.horizontalCenter
                visible: false
                // transform this item (the image and rectangle) to create the
                // mirror image using the values from the Path
                transform : [
                    Rotation {
                        angle: 180; origin.y: image2.height
                        axis.x: 1; axis.y: 0; axis.z: 0
                    },

                    Scale {
                        xScale: 1; yScale: 1
                        origin.x: image2.width/2; origin.y: image2.height/2
                    }
                ]

                // mirror image
                Image {
                    width: image2.width
                    height: image2.height

                    source: image2.source
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: image2.width; height: image2.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        gradient: Gradient {
                            // TODO: no clue how to get the RGB component of the container rectangle color
                            GradientStop { position: 0; color: "black" }
                            GradientStop { position: 0.8; color: "black" }
                            GradientStop { position: 1.0; color: "white" }
                        }
                        opacity: 1
                    }

                    opacity: 0.5
                }
            }
        }
    }

    Text {
        id: artistName

        y: 465-232
        width: 345
        height: 18

        opacity: main.state === "music" ? 1 : 0

        color: "white"
        text: artist
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 21

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }


    Text {
        id: playTime

        y: 534-232
        width: 345
        height: 18

        opacity: main.state === "music" ? 1 : 0

        color: "white"
        text: curPosition
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 21

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MarqueeLabel {
        id: text_song_title
        y: 490-232
        width: 345
        height: 25
        fontFamily: "SpoqaHanSans"
        scrollingTextMargin: 20
        fontSize: 21
//        fontStyle: Text.Outline
        fontBold: true
//        baselineOffset: -12
//        anchors.bottom: parent.top
//        anchors.bottomMargin: -156
//        anchors.horizontalCenter: parent.horizontalCenter
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
        PropertyAction { target: privateObject.currentItem; property: "x"; value: 150/3 }
//        PropertyAction { target: privateObject.currentItem; property: "x"; value: -150/3 }

        ScriptAction { script: swapObject() }
    }
}
