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

import QtQuick 2.5
import AVInformationTypes 1.0

Item {
    id: main
    objectName: "MainItem"

    property int rpmValue: 3000
    property int speedValue: 120
    property int gearValue: 0

    /* test */
    property bool drivingMode: true

    width: 1280
    height: 720

    Component.onCompleted: {
        setAVSource(AVDataManager.source)
        main.state = "music"
    }

    Timer {
        id: sideLightsTimer

        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if( leftLight.visible )
            {
                leftLight.visible = false
                rightLight.visible = false
            }
            else
            {
                leftLight.visible = true
                rightLight.visible = true
            }
        }
    }

    Image {
        id: bg
        objectName: "BgImage"
        anchors.fill: parent
        source: "../image/genivi_16th_amm/cluster_bg.png"
    }

    Image {
        id: leftLight

        x: 340
        anchors.verticalCenter: textTime.verticalCenter

        source: "../image/genivi_16th_amm/cluster/L_Light.png"
    }

    Image {
        id: rightLight

        x: 909
        anchors.verticalCenter: textTime.verticalCenter

        source: "../image/genivi_16th_amm/cluster/R_Light.png"
    }

    /* Speed Cluster */
    Image {
        id: speedBg

        x: 21
        y: 131

        width: 459
        height: 455

        source: "../image/genivi_16th_amm/cluster/Speed_bg.png"
    }

    Gauge {
        id: gaugeSpeed

        x: 21
        y: 131

        type: 'speed'
        needleImageURL: "../image/genivi_16th_amm/cluster/Needle.png"
        activeImage: "../image/genivi_16th_amm/cluster/gauge_effect.png"
        value: speedValue
    }

    Item {
        id: textSpeedArea

        x: 159
        y: 272
        z: 1

        width: 172
        height: 172

        Text {
            id: textSpeed
            anchors.fill: parent
            color: "white"
            text: speedValue
            font.family: "Digital-7 Mono, Italic"
//            font.family: "SpoqaHanSans"
            font.bold: false
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: 101
        }

    }

    Image {
        id: speedClusterCenterForward
        source: "../image/genivi_16th_amm/cluster/center_bg_forward.png"

        anchors.left: textSpeedArea.left
        anchors.leftMargin: -4
        anchors.top: textSpeedArea.top
        anchors.topMargin: -7
    }

    Image {
        x: 21
        y: 131

        anchors.left: speedBg.left
        anchors.leftMargin: 19
        anchors.top: speedBg.top
        anchors.topMargin: 20
        source: "../image/genivi_16th_amm/cluster/Metal border.png"

    }









    /* RPM Cluster */
    Image {
        id: rpmBg
        x: 800
        y: 131
        width: 459
        height: 455

        source: "../image/genivi_16th_amm/cluster/Rpm_bg.png"
    }

    Image {
        x: 800
        y: 131

        anchors.left: rpmBg.left
        anchors.leftMargin: 25
        anchors.top: rpmBg.top
        anchors.topMargin: 20
        source: "../image/genivi_16th_amm/cluster/Metal border.png"

    }

    Gauge {
        id: gaugeRPM

        x: 800
        y: 131

        type: 'rpm'
        needleImageURL: "../image/genivi_16th_amm/cluster/Needle.png"
        activeImage: "../image/genivi_16th_amm/cluster/gauge_effect.png"
        value: rpmValue
    }

    Item {
        id: gearArea

        x: 944
        y: 272
        z: 1

        width: 172
        height: 172

        Text {
            id: textRpm
            anchors.fill: parent
            color: "white"
            text: "D"
            font.family: "SpoqaHanSans"
            font.bold: false
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 87
        }
    }

    Image {
        id: rpmClusterCenterForward
        source: "../image/genivi_16th_amm/cluster/center_bg_forward.png"

        anchors.left: gearArea.left
        anchors.leftMargin: -10
        anchors.top: gearArea.top
        anchors.topMargin: -7
    }


    Text {
        id: textTotalDistance
        x: 437
        color: "white"
        anchors.verticalCenter: textTime.verticalCenter
        text: Cluster.totalDistance
//        font.family: "NanumBarunGothic, Bold"
        font.family: "SpoqaHanSans Bold"
        font.bold: true
        font.pixelSize: 18
    }

    Text {
        id: textExternalDegree
        x: 770
        anchors.verticalCenter: textTime.verticalCenter
        color: "white"
        text: "26.5 ℃"
//        font.family: "NanumBarunGothic, Bold"
        font.family: "SpoqaHanSans Bold"
        font.bold: true
        font.pixelSize: 18
    }

    Text {
        id: textTime
        x: 579
        y: 34
        width: 126
        height: 21
        color: "white"
        text: AVDataManager.currentTime
//        font.family: "NanumBarunGothic, Bold"
        font.family: "SpoqaHanSans Bold"
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 25
    }


    ClusterIcon {
        id: icon_music
        x: 479
        y: 147
        normalImage: "../image/genivi_16th_amm/mode_icon/Disable_media_Assistor.png"
        activeImage: "../image/genivi_16th_amm/mode_icon/Active_media_Assistor.png"
        actived: main.state === "music"
    }

    ClusterIcon {
        id: icon_radio
        x: 576
        y: 146
        normalImage: "../image/genivi_16th_amm/mode_icon/Disable_radio_Assistor.png"
        activeImage: "../image/genivi_16th_amm/mode_icon/Active_radio_Assistor.png"
        actived: main.state === "radio"
    }

    ClusterIcon {
        id: icon_video
        x: 674
        y: 146
        normalImage: "../image/genivi_16th_amm/mode_icon/video_disable.png"
        activeImage: "../image/genivi_16th_amm/mode_icon/video_normal.png"
        actived: main.state === "video"
    }

    ClusterIcon {
        id: icon_setting
        x: 772
        y: 146
        normalImage: "../image/genivi_16th_amm/mode_icon/Disable_setting_Assistor.png"
        activeImage: "../image/genivi_16th_amm/mode_icon/Active_setting_Assistor.png"
        actived: main.state === "setting"
    }



    AlbumArt {
        id: albumArt
        visible: opacity !== 0
        x: 468
        y: 250
        opacity: main.state === "music" ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 300 }
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

        Timer {
            id: timer
            interval: 3000
            repeat: true
            onTriggered: {
                console.log(albumArt.imageList[albumArt.index])
                console.log(albumArt.index)
                albumArt.imagePath = "image://AlbumArtProvider/" + albumArt.index

                if (albumArt.index === (albumArt.imageList.length - 1) )
                    albumArt.index = 0
                else
                    albumArt.index++;
            }
        }
    }



    RadioInfo {
        id: radioInfo
        x: 508
        y: 232
        width: 265
        height: 233

        visible: opacity !== 0
        opacity: main.state === "radio" ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }


    }

    VideoInfo {
        id: videoInfo
        anchors.centerIn: parent
        visible: opacity !== 0
        opacity: main.state === "video" ? 1 : 0

    }

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
}
