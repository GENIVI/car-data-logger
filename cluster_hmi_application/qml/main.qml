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
    property string gearValue: "P"

    property bool leftIndicatorActice: false
    property bool rightIndicatorActice: false

    property real ectPercentage: 0.0
    property int ectFullGauge: 0

    property real fuelPercentage: 0.0
    property int fuelFullGauge: 0

    width: 1280
    height: 720

    Component.onCompleted: {
        print( Cluster.engineCoolantTemperature , Cluster.fuel)
        setAVSource(AVDataManager.source)
        fuelFullGauge = fuelGaugeLine.width
        ectFullGauge = ectGaugeLine.width
        main.state = "music"
    }

    Timer {
        id: leftIndicatorTimer

        interval: 500
        repeat: true
        onTriggered: {
            leftIndicatorActice = !leftIndicatorActice
        }
    }

    Timer {
        id: rightIndicatorTimer

        interval: 500
        repeat: true
        onTriggered: {
            rightIndicatorActice = !rightIndicatorActice
        }
    }

    Timer {
        id: bothSideIndicatorTimer

        interval: 500
        repeat: true
        onTriggered: {
            leftIndicatorActice = !leftIndicatorActice
            rightIndicatorActice = !rightIndicatorActice
        }
    }

    Connections{
        target: Cluster

        onEngineCoolantTemperatureChanged: {
            ectPercentage = Cluster.engineCoolantTemperature/100.0
            ectGaugeLine.width = ectFullGauge*ectPercentage/2
            if( Cluster.engineCoolantTemperature > 120 )
            {
                ectHighGaugeLine.width = ectGaugeLine.width-180.6
            }
        }

        onFuelChanged: {
            fuelPercentage = Cluster.fuel/100.0
            fuelGaugeLine.width = fuelFullGauge*fuelPercentage
            if( Cluster.fuel < 20 )
            {
                fuelLowGaugeLine.width = fuelGaugeLine.width
            }
        }

        onSpeedChanged: {
            speedValue = Cluster.speed
        }

        onRpmChanged: {
            rpmValue = Cluster.rpm
        }

        onGearStateChanged: {
            switch( Cluster.gearState )
            {
            case 0:
                gearValue = "P";
                break;
            case 1:
                gearValue = "R";
                break;
            case 2:
                gearValue = "N";
                break;
            case 3:
                gearValue = "D";
                break;
            }
        }

        onLeftIndicatorChanged: {
            if( Cluster.leftIndicator )
            {
                if( !Cluster.rightIndicator )
                {
                    leftIndicatorActice = true
                    leftIndicatorTimer.start()
                }
                else
                {
                    leftIndicatorTimer.stop()
                    rightIndicatorTimer.stop()
                    leftIndicatorActice = false
                    rightIndicatorActice = false
                    bothSideIndicatorTimer.start()
                }

            }
            else
            {
                if( !Cluster.rightIndicator )
                {
                    leftIndicatorTimer.stop();
                    leftIndicatorActice = false;
                }
                else
                {
                    if( !bothSideIndicatorTimer.running )
                    {
                        leftIndicatorActice = false

                    }
                    else
                    {
                        bothSideIndicatorTimer.stop()
                        leftIndicatorActice = false
                        rightIndicatorActice = false
                    }
                }
            }
        }

        onRightIndicatorChanged: {
            if( Cluster.rightIndicator )
            {
                if( !Cluster.leftIndicator )
                {
                    rightIndicatorActice = true
                    rightIndicatorTimer.start()
                }
                else
                {
                    leftIndicatorTimer.stop()
                    rightIndicatorTimer.stop()
                    leftIndicatorActice = false
                    rightIndicatorActice = false
                    bothSideIndicatorTimer.start()
                    leftIndicatorActice = true
                    rightIndicatorActice = true
                }
            }
            else
            {
                if( !Cluster.leftIndicator )
                {
                    rightIndicatorTimer.stop();
                    rightIndicatorActice = false;
                }
                else
                {
                    if( !bothSideIndicatorTimer.running )
                    {
                        rightIndicatorActice = false

                    }
                    else
                    {
                        bothSideIndicatorTimer.stop()
                        leftIndicatorActice = false
                        rightIndicatorActice = false
                    }
                }
            }
        }
    }

    Image {
        id: bg
        objectName: "BgImage"
        anchors.fill: parent
        source: "../image/genivi_16th_amm/cluster_normal_bg.png"
    }

    Image {
        id: leftIndicatorImage

        x: 340
        anchors.verticalCenter: textTime.verticalCenter

        opacity: leftIndicatorActice ? 1 : 0.2

        source: "../image/genivi_16th_amm/cluster/L_Light.png"
    }

    Image {
        id: rightIndicatorImage

        x: 909
        anchors.verticalCenter: textTime.verticalCenter

        opacity: rightIndicatorActice ? 1 : 0.2

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

    /* Gear State */
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
            text: gearValue
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


    /* Total Distance */
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

    /* External Degree */
    Text {
        id: textExternalDegree
        x: 770
        anchors.verticalCenter: textTime.verticalCenter
        color: "white"
        text: "26.5 ℃"
        font.family: "SpoqaHanSans Bold"
        font.bold: true
        font.pixelSize: 18
    }

    /* Time */
    Text {
        id: textTime
        x: 579
        y: 34
        width: 126
        height: 21
        color: "white"
        text: AVDataManager.currentTime
        font.family: "SpoqaHanSans Bold"
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 25
    }

    /* Engine Coolant Temperature Gauge */
    Image {
        id: ectLevelLine

        source: "../image/genivi_17th_amm/Gauge_Line/ECT_Cool_Hot_Bg_Line.png"

        anchors.horizontalCenter: main.horizontalCenter
        anchors.bottom: fuelLevelLine.top
        anchors.bottomMargin: 10

        Image {
            id: ectGaugeLine

            source : "../image/genivi_17th_amm/Gauge_Line/ECT_Default_White_Gauge.png"

            opacity: 0.7

            anchors.bottom: ectLevelLine.bottom
            anchors.bottomMargin: 16
            anchors.left: ectLevelLine.left
            anchors.leftMargin: 16
        }

        Image {
            id: ectHighGaugeLine

            width: 120.4

            source : "../image/genivi_17th_amm/Gauge_Line/ECT_Warning_Red_Gauge.png"
            opacity: 0.7

            visible: Cluster.engineCoolantTemperature > 120 ? true : false

            anchors.bottom: ectGaugeLine.bottom
            anchors.left: ectGaugeLine.left
            anchors.leftMargin: 180.6
        }
    }

    /* Fuel Gauge */
    Image {
        id: fuelLevelLine

        y: 580

        source: "../image/genivi_17th_amm/Fuel_Level/Empty_Full_Bg_Line.png"
        anchors.horizontalCenter: main.horizontalCenter

        Image {
            id: fuelGaugeLine

            source : "../image/genivi_17th_amm/Fuel_Level/Default_White_Gauge.png"
            opacity: 0.8
            anchors.verticalCenter: fuelLevelLine.verticalCenter
            anchors.left: fuelLevelLine.left
            anchors.leftMargin: 40
        }

        Image {
            id: fuelLowGaugeLine

            source : "../image/genivi_17th_amm/Fuel_Level/Warning_Red_Gauge.png"
            opacity: 0.8
            visible: Cluster.fuel < 20 ? true : false
            anchors.verticalCenter: fuelLevelLine.verticalCenter
            anchors.left: fuelLevelLine.left
            anchors.leftMargin: 40
        }
    }

    /* Mode Icon */
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



    /* Lights Image */
    Image {
        id: highBeamImage

        anchors.top: textTime.bottom
        anchors.topMargin: 10
        anchors.right: headLightsImage.left
        anchors.rightMargin: 120

        scale: 0.8

        opacity: Cluster.highBeam ? true : 0.2

        source: "../image/genivi_17th_amm/Lights/High_Beam_Light.png"
    }

    Image {
        id: headLightsImage

        anchors.top: textTime.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: main.horizontalCenter

        opacity: Cluster.headLight ? true : 0.2

        source: "../image/genivi_17th_amm/Lights/Normal_Head_Lights.png"
    }

    Image {
        id: fogLightImage

        anchors.top: textTime.bottom
        anchors.topMargin: 10
        anchors.left: headLightsImage.right
        anchors.leftMargin: 120

        scale: 0.8

        opacity: Cluster.fogLight ? true : 0.2

        source: "../image/genivi_17th_amm/Lights/Fog_Light.png"
    }





    /* Warning Image */
    Image {
        id: engineCoolantTempWarningImage

        anchors.bottom: main.bottom
        anchors.bottomMargin: 7
        anchors.right: seatBeltWarningImage.left
        anchors.rightMargin: 37

        scale: 0.8

        opacity: Cluster.engineCoolantTemperature > 120 ? true : 0.2

        source: "../image/genivi_17th_amm/Warning_Icon/Engine_Coolant_Temp_Icon.png"
    }

    Image {
        id: airBagWarningImage

        anchors.bottom: main.bottom
        anchors.bottomMargin: 7
        anchors.right: parkingBrakeWarningImage.left
        anchors.rightMargin: 40

        scale: 0.8

        opacity: Cluster.airBagDeployed ? true : 0.2

        source: "../image/genivi_17th_amm/Warning_Icon/Air_Bag_Icon.png"
    }

    Image {
        id: seatBeltWarningImage

        anchors.bottom: main.bottom
        anchors.bottomMargin: 7
        anchors.right: airBagWarningImage.left
        anchors.rightMargin: 40

        scale: 0.8

        opacity: Cluster.seatBelt ? true : 0.2

        source: "../image/genivi_17th_amm/Warning_Icon/Seat_Belt_Icon.png"
    }

    Image {
        id: parkingBrakeWarningImage

        x: main.width/2 + 30
        anchors.bottom: main.bottom
        anchors.bottomMargin: 7

        opacity: Cluster.parkingBrakeEngaged ? true : 0.2

        source: "../image/genivi_17th_amm/Warning_Icon/Parking_Brake_Icon.png"
    }


    Image {
        id: lowFuelWarningImage

        anchors.bottom: main.bottom
        anchors.bottomMargin: 7
        anchors.left: parkingBrakeWarningImage.right
        anchors.leftMargin: 40

        scale: 0.8

        opacity: Cluster.fuel < 20 ? true : 0.2

        source: "../image/genivi_17th_amm/Warning_Icon/Low_Fuel_Icon.png"
    }

    Image {
        id: washerFluidLowWarningImage

        anchors.bottom: main.bottom
        anchors.bottomMargin: 7
        anchors.left: lowFuelWarningImage.right
        anchors.leftMargin: 40

        scale: 0.8

        opacity: Cluster.lowWasherFluid ? true : 0.2

        source: "../image/genivi_17th_amm/Warning_Icon/Washer_Fiuid_Low_Icon.png"
    }



    /* Info */
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

    function setAVSource( source )
    {
        switch( source )
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
