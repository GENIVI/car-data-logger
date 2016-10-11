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
 * \file VideoPlayer.qml
*/

import QtQuick 2.5

import "qrc:/component"

Item{
    id: videoPlayerWindow
    objectName: "videoPlayer"

    width: 800
    height: 420

    y: 60

    property bool videoControllerState: true

    property int hour: 0
    property int min: 0
    property int sec: 0
    property int curPlayVideoIndex: 0

    property int curHour: 0
    property int curMin: 0
    property int curSec: 0
    property bool mediaModeChangePlayOff: false
    property bool sliderPressState: false

    property int currentPlayTime: VideoControl.curPlayTime
    property int videoPlayTime: VideoControl.mediaPlayTime
    property string videoTitle: VideoControl.title
    property string videoArtist: VideoControl.artist
    property bool videoPlayState: VideoControl.playState


    function calVideoPlayTime(videoPlayTime)
    {
        var temp

        hour = videoPlayTime/3600
        temp = videoPlayTime%3600

        min = temp/60
        sec = temp%60
    }

    function calCurrentPlayTime(curPlayTime)
    {
        var temp

        curHour = curPlayTime/3600
        temp = curPlayTime%3600

        curMin = temp/60
        curSec = temp%60
    }

    Component.onCompleted: {
        VideoControl.requestPlayPause(true)
        calCurrentPlayTime(currentPlayTime)
        calVideoPlayTime(videoPlayTime)
    }

    Connections{
        target: VideoControl

        onCurPlayTimeChanged: {
            calCurrentPlayTime(currentPlayTime)
            videoPlaySlider.value = currentPlayTime
        }

        onMediaPlayTimeChanged:{
            calVideoPlayTime(videoPlayTime)
        }

        onCurMediaIndexChanged: {
            videoPlaySlider.value = currentPlayTime
        }

        onPlayStateChanged: {
            videoPlayState = VideoControl.playState
        }

        onDriveRestrictChanged: {
            print("drive Restrict Changed")
            if(VideoControl.driveRestrict)
                drivingRestrictionLoader.visible=true
            else
                drivingRestrictionLoader.visible=false
        }

    }

    onVideoControllerStateChanged: {
        if(!videoControllerState){
            videoSliderBarLayout.enabled=false
            videoControlButtonLayout.enabled=false
            videoContorlBtnFadeOutAnimation.start()
            sliderFadeOutAnimation.start()
            videocontrollerFadeOutTimer.stop()
        }
        else{
            videoSliderBarLayout.enabled=true
            videoControlButtonLayout.enabled=true
            videoContorlBtnFadeInAnimation.start()
            sliderFadeInAnimation.start()
            videocontrollerFadeOutTimer.start()
        }
    }

    Rectangle{
        id: videoPlayerBg

        anchors.fill: parent
        color: "#222222"
    }

    MouseArea{
        anchors.fill: parent

    }

    /* Video Thumbnail Layout */
    Item{
        id: videoThumbnailInageLayout

        width: videoPlayerWindow.width
        height: 420

        Image{
            id: videoThumbnailImage

            anchors.fill: parent
            anchors.centerIn: videoThumbnailInageLayout

            source:"file:///"+VideoControl.albumArtPath
        }

        MouseArea{
            anchors.fill: parent
            onReleased: {
                if(videoControllerState)
                    videoControllerState=false
                else
                    videoControllerState=true
            }
        }

        /* driving Restriction Loader */
        Loader{
            id: drivingRestrictionLoader

            visible: false
            source: "DrivingRestriction.qml"
        }
    }



    /* Video SliderBar Layout */
    Item{
        id: videoSliderBarLayout

        width: videoPlayerWindow.width
        height: 30

        y:290

        Slider{
            id: videoPlaySlider

            sliderWidth: 600
            sliderHeight: 10
            sliderColor: "#333333"

            sliderProgressState: true

            sliderPointerWidth: 20
            sliderPointerHeight: 20
            sliderPointerColor: "skyblue"

            maximum: VideoControl.mediaPlayTime
            minimum: 0

            anchors.centerIn: parent

            onSignalPressed: {
                sliderPressState=true
                videocontrollerFadeOutTimer.stop()
                VideoControl.progressbarPressState(sliderPressState)
            }

            onSignalPressedLong: {

            }
            onSignalReleased: {
                sliderPressState=false
                videocontrollerFadeOutTimer.restart()
                MusicControl.progressbarPress(value)
                VideoControl.progressbarPressState(sliderPressState)
            }

            onValueChanged: {
                if(sliderPressState)
                    calCurrentPlayTime(value)
            }

            NumberAnimation{
                id: sliderFadeOutAnimation
                target: videoSliderBarLayout
                properties: "opacity"
                from: 1
                to: 0
                duration: 200
            }

            NumberAnimation{
                id: sliderFadeInAnimation
                target: videoSliderBarLayout
                properties: "opacity"
                from: 0
                to: 1
                duration: 200
            }

        }

        Text{
            id: maxPlayTimeText

            width: 30
            height: 30
            anchors.left: videoPlaySlider.right

            text:{
                if(hour<10)
                {
                    if(min<10)
                    {
                        if(sec<10)                          "0"+hour+":"+"0"+min+":"+"0"+sec
                        else if(sec>10 || sec<60)           "0"+hour+":"+"0"+min+":"+sec
                    }
                    else
                    {
                        if(sec<10)                          "0"+hour+":"+min+":"+"0"+sec
                        else if(sec>10 || sec<60)           "0"+hour+":"+min+":"+sec
                    }
                }

                else
                {
                    if(min<10)
                    {
                        if(sec<10)                          hour+":"+"0"+min+":"+"0"+sec
                        else if(sec>10 || sec<60)           hour+":"+"0"+min+":"+sec
                    }
                    else
                    {
                        if(sec<10)                          hour+":"+min+":"+"0"+sec
                        else if(sec>10 || sec<60)           hour+":"+min+":"+sec
                    }
                }
            }
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 15
        }

        Text{
            id: currentPlayTimeText

            width: 100
            height: 30
            anchors.right: videoPlaySlider.left

            text:{
                if(curHour<10)
                {
                    if(curMin<10)
                    {
                        if(curSec<10)                             "0"+curHour+":"+"0"+curMin+":"+"0"+curSec
                        else if(curSec>10 || curSec<60)           "0"+curHour+":"+"0"+curMin+":"+curSec
                    }
                    else
                    {
                        if(curSec<10)                             "0"+curHour+":"+curMin+":"+"0"+curSec
                        else if(curSec>10 || curSec<60)           "0"+curHour+":"+curMin+":"+curSec
                    }
                }

                else
                {
                    if(curMin<10)
                    {
                        if(curSec<10)                             curHour+":"+"0"+curMin+":"+"0"+curSec
                        else if(curSec>10 || curSec<60)           curHour+":"+"0"+curMin+":"+curSec
                    }
                    else
                    {
                        if(curSec<10)                             curHour+":"+curMin+":"+"0"+curSec
                        else if(curSec>10 || curSec<60)           curHour+":"+curMin+":"+curSec
                    }
                }
            }
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 15
        }
    }

    /* Video Control Button ( Play, Prev, Next ) Layout */
    Item{
        id: videoControlButtonLayout

        width: videoPlayerWindow.width
        height: 90

        anchors.top: videoSliderBarLayout.bottom

        NumberAnimation{
            id: videoContorlBtnFadeOutAnimation
            target: videoControlButtonLayout
            properties: "opacity"
            from: 1
            to: 0
            duration: 200
        }

        NumberAnimation{
            id: videoContorlBtnFadeInAnimation
            target: videoControlButtonLayout
            properties: "opacity"
            from: 0
            to: 1
            duration: 200
        }

        Item{
            width: 600
            height: 90

            anchors.centerIn: parent

            /* Previous Button */
            Item{
                id: prevButtonLayout

                width: 200
                height: 90

                Image{
                    id: prevButtonImage

                    width: 100
                    height: 80

                    anchors.centerIn: prevButtonLayout

                    source: prevBtnImageMouseArea.pressed ? "qrc:/media/image/Media_Player_Previous_Pressed.png" : "qrc:/media/image/Media_Player_Previous.png"
                    MouseArea{
                        id: prevBtnImageMouseArea
                        anchors.fill: parent

                        onPressed: {
                            videocontrollerFadeOutTimer.stop()
                        }

                        onReleased: {
                            VideoControl.requestPrev()
                            videocontrollerFadeOutTimer.restart()
                        }
                    }
                }
            }

            /* Play, Pause Button */
            Item{
                id: playButtonLayout

                width: 200
                height: 90

                anchors.left: prevButtonLayout.right

                Image{
                    id: playButtonImage

                    width: 100
                    height: 80

                    anchors.centerIn: playButtonLayout

                    source: {
                        if(videoPlayState)
                        {
                            playBtnImageMouseArea.pressed ? "qrc:/media/image/Media_Player_Pause_Pressed.png"
                                                          : "qrc:/media/image/Media_Player_Pause.png"
                        }
                        else
                        {
                            playBtnImageMouseArea.pressed ? "qrc:/media/image/Media_Player_Play_Pressed.png"
                                                          : "qrc:/media/image/Media_Player_Play.png"
                        }
                    }

                    MouseArea{
                        id: playBtnImageMouseArea
                        anchors.fill: parent

                        onPressed: {
                            videocontrollerFadeOutTimer.stop()
                        }

                        onReleased: {
                            videoPlayState = !videoPlayState
                            VideoControl.requestPlayPause(videoPlayState)
                            videocontrollerFadeOutTimer.restart()
                        }
                    }
                }
            }

            /* Next Button */
            Item{
                id: nextButtonLayout

                width: 200
                height: 90

                anchors.left: playButtonLayout.right

                Image{
                    id: nextButtonImage

                    width: 100
                    height: 80

                    anchors.centerIn: nextButtonLayout

                    source: nextBtnImageMouseArea.pressed ? "qrc:/media/image/Media_Player_Next_Pressed.png" : "qrc:/media/image/Media_Player_Next.png"
                    MouseArea{
                        id: nextBtnImageMouseArea
                        anchors.fill: parent

                        onPressed: {
                            videocontrollerFadeOutTimer.stop()
                        }

                        onReleased: {
                            VideoControl.requestNext()
                            videocontrollerFadeOutTimer.restart()
                        }
                    }
                }
            }
        }
    }

    Item{
        Timer{
            id: videocontrollerFadeOutTimer
            interval: 3500
            running: true

            onTriggered:{
                videoControllerState=false
            }

        }
    }
}
