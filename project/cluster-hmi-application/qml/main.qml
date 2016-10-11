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
 * \file main.qml
*/

import QtQuick 2.5
import AVInformationTypes 1.0

Item {
    id: main
    objectName: "MainItem"

    width: 800
    height: 480

    Image {
        id: bg
        objectName: "BgImage"
        source: "../image/bg/background.png"
    }



    Text {
        id: text_km
        width: id_km.width
        anchors.baseline: id_km.top
        anchors.horizontalCenter: id_km.horizontalCenter
        color: "white"
        text: "km/h"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_km
        x: 325
        y: 469
        width: 149
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_x1000
        width: id_rpm_x1000.width
        anchors.baseline: id_rpm_x1000.top
        anchors.horizontalCenter: id_rpm_x1000.horizontalCenter
        color: "white"
        text: "x1000"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_x1000
        x: 181
        y: 385
        width: 46
        height: 1
        visible: false
    }

    Text {
        id: text_fuel_f
        width: id_fuel_f.width
        anchors.baseline: id_fuel_f.top
        anchors.horizontalCenter: id_fuel_f.horizontalCenter
        color: "white"
        text: "F"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_fuel_f
        x: 624
        y: 144
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_fuel_e
        width: id_fuel_e.width
        anchors.baseline: id_fuel_e.top
        anchors.horizontalCenter: id_fuel_e.horizontalCenter
        color: "white"
        text: "E"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_fuel_e
        x: 620
        y: 363
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm
        width: id_rpm.width
        anchors.baseline: id_rpm.top
        anchors.right: id_rpm.right
        color: "white"
        text: "RPM"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm
        x: 188
        y: 429
        width: 47
        height: 1
        visible: false
    }

    Text {
        id: text_fuel
        width: id_fuel.width
        anchors.baseline: id_fuel.top
        anchors.left: id_fuel.left
        color: "white"
        text: "FUEL"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_fuel
        x: 565
        y: 429
        width: 47
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_1
        width: id_rpm_1.width
        anchors.baseline: id_rpm_1.top
        anchors.horizontalCenter: id_rpm_1.horizontalCenter
        color: "white"
        text: "1"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_1
        x: 162
        y: 362
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_2
        width: id_rpm_2.width
        anchors.baseline: id_rpm_2.top
        anchors.horizontalCenter: id_rpm_2.horizontalCenter
        color: "white"
        text: "2"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_2
        x: 154
        y: 331
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_3
        width: id_rpm_3.width
        anchors.baseline: id_rpm_3.top
        anchors.horizontalCenter: id_rpm_3.horizontalCenter
        color: "white"
        text: "3"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_3
        x: 144
        y: 300
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_4
        width: id_rpm_4.width
        anchors.baseline: id_rpm_4.top
        anchors.horizontalCenter: id_rpm_4.horizontalCenter
        color: "white"
        text: "4"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_4
        x: 141
        y: 269
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_5
        width: id_rpm_5.width
        anchors.baseline: id_rpm_5.top
        anchors.horizontalCenter: id_rpm_5.horizontalCenter
        color: "white"
        text: "5"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_5
        x: 139
        y: 238
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_6
        width: id_rpm_6.width
        anchors.baseline: id_rpm_6.top
        anchors.horizontalCenter: id_rpm_6.horizontalCenter
        color: "white"
        text: "6"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_6
        x: 143
        y: 207
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_7
        width: id_rpm_7.width
        anchors.baseline: id_rpm_7.top
        anchors.horizontalCenter: id_rpm_7.horizontalCenter
        color: "white"
        text: "7"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_7
        x: 148
        y: 176
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_rpm_8
        width: id_rpm_8.width
        anchors.baseline: id_rpm_8.top
        anchors.horizontalCenter: id_rpm_8.horizontalCenter
        color: "white"
        text: "8"
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_rpm_8
        x: 159
        y: 144
        width: 18
        height: 1
        visible: false
    }

    Text {
        id: text_title
        width: id_title.width
        anchors.baseline: id_title.top
        anchors.horizontalCenter: id_title.horizontalCenter
        color: "white"
        text: "Music"
        font.family: "SpoqaHanSans"
        font.bold: false
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_title
        x: 326
        y: 128
        width: 149
        height: 1
        visible: false
    }

    Text {
        id: text_total_distance
        width: id_total_distance.width
        anchors.baseline: id_total_distance.top
        anchors.horizontalCenter: id_total_distance.horizontalCenter
        color: "white"
        text: Cluster.totalDistance
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 18
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_total_distance
        x: 325
        y: 363
        width: 149
        height: 1
        visible: false
    }

    Text {
        id: text_speed
        width: id_speed.width
        anchors.baseline: id_speed.top
        anchors.horizontalCenter: id_speed.horizontalCenter
        color: "white"
        text: Cluster.speed
        font.family: "Digital-7"
        font.bold: false
        font.pixelSize: 60
        horizontalAlignment: Text.AlignHCenter
    }
    Item {
        id: id_speed
        x: 325
        y: 447
        width: 149
        height: 1
        visible: false
    }

    ClusterIcon {
        id: icon_music
        x: 267
        y: 105
        normalImage: "../image/icon/Music_icon_normal.png"
        activeImage: "../image/icon/Music_icon_Activate.png"
        actived: main.state === "music"

//        MouseArea {
//            anchors.fill: parent
//            onClicked: main.state = "music"
//        }
    }

    ClusterIcon {
        id: icon_radio
        x: 482
        y: 105
        normalImage: "../image/icon/Radio_icon_normal.png"
        activeImage: "../image/icon/radio_icon_Activate.png"
        actived: main.state === "radio"

//        MouseArea {
//            anchors.fill: parent
//            onClicked: main.state = "radio"
//        }
    }

    ClusterIcon {
        id: icon_video
        x: 482
        y: 322
        normalImage: "../image/icon/video_icon_normal.png"
        activeImage: "../image/icon/video_icon_Activate.png"
        actived: main.state === "video"

//        MouseArea {
//            anchors.fill: parent
//            onClicked: main.state = "video"
//        }
    }

    Image {
        id: icon_phone
        source: "../image/icon/Phone_icon_normal.png"
        x: 267
        y: 322
    }

//    Image {
//        id: icon_setting
//        source: "../image/icon/setting_icon_normal.png"
//        x: 482
//        y: 322
//    }

    AlbumArt {
        id: albumArt
        anchors.centerIn: parent
        visible: opacity !== 0
        opacity: main.state === "music" ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }

        property int index: 1

        property var imageList: ["../image/cover/1.jpg",
        "../image/cover/2.jpg",
        "../image/cover/3.jpg",
        "../image/cover/4.jpg",
        "../image/cover/5.jpg",
        "../image/cover/6.jpg",
        "../image/cover/7.jpg"]
        Connections{
            target : AVDataManager
            onAlbumArtChanged: albumArt.imagePath = "image://AlbumArtProvider/" + AVDataManager.title
        }

        //imagePath: "image://AlbumArtProvider/" + AVDataManager.title

        Timer {
            id: timer
            interval: 3000
            repeat: true
            onTriggered: {
                console.log(albumArt.imageList[albumArt.index])
                console.log(albumArt.index)
//                albumArt.imagePath = encodeURIComponent(albumArt.imageList[albumArt.index])
                //albumArt.imagePath = "image://AlbumArtProvider/albumArt"
                albumArt.imagePath = "image://AlbumArtProvider/" + albumArt.index

                if (albumArt.index === (albumArt.imageList.length - 1) )
                    albumArt.index = 0
                else
                    albumArt.index++;
            }
        }

        Image {
            anchors.centerIn: parent
            source: "../image/bg/Center_Line_bg.png"
        }
    }

    RadioInfo {
        id: radioInfo
        x: 318
        y: 157
        visible: opacity !== 0
        opacity: main.state === "radio" ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }

        Image {
            x: -4
            y: -4
            width: 173
            height: 173
            source: "../image/bg/Center_Line_bg.png"
        }
    }

    VideoInfo {
        id: videoInfo
        anchors.centerIn: parent
        visible: opacity !== 0
        opacity: main.state === "video" ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }

        Image {
            anchors.centerIn: parent
            source: "../image/bg/Center_Line_bg.png"
        }
    }

    Gauge {
        id: gaugeRPM
        x: 89
        y: 103
        type: 'rpm'
        normalImage: "../image/gauge_image/gauge_normal.left.png"
        activeImage: "../image/gauge_image/gauge_color.left.png"
        value: Cluster.rpm
    }

    Gauge {
        id: gaugeFuel
        x: 645
        y: 103
        type: 'fuel'
        normalImage: "../image/gauge_image/gauge_normal.right.png"
        activeImage: "../image/gauge_image/gauge_color_right.png"
        value: Cluster.fuel
    }

    Image {
        id: line
        objectName: "LineImage"
        source: "../image/bg/Line_bg.png"
    }

    states: [
        State {
            name: "radio"
            PropertyChanges {
                target: text_title
                text: "Radio"
            }
        },
        State {
            name: "music"
            PropertyChanges {
                target: text_title
                text: "Music"
            }
        },
        State {
            name: "video"
            PropertyChanges {
                target: text_title
                text: "Video"
            }
        }
    ]

    function setAVSource(source)
    {
        switch(source)
        {
        case Source.FM:
        case Source.AM:
            main.state = "radio"
            break
        case Source.USB_MUSIC:
            main.state = "music"
            break
        case Source.USB_VIDEO:
            main.state = "video"
            break
        default:
            break
        }
    }

    Connections {
        target: AVDataManager

        onSourceChanged: {
            setAVSource(source)
        }
    }

    Component.onCompleted: {
        // FIXME. test timer
//        timer.running = true
        setAVSource(AVDataManager.source)
        //timer.running = true
        main.state = "music"
    }
}
