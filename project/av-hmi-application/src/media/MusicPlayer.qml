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
 * \file MusicPlayer.qml
*/

import QtQuick 2.5

import "qrc:/component"

Item{
    id: musicPlayerWindow
    objectName: "musicPlayer"

    width: 800
    height: 420
    y: 60

    property int min: 0
    property int sec: 0
    property int curPlayMusicIndex: 0

    property int curMin: 0
    property int curSec: 0
    property bool mediaModeChangePlayOff: false
    property bool sliderPressState: false

    property int currentPlayTime: MusicControl.curPlayTime
    property int musicPlayTime: MusicControl.mediaPlayTime
    property string musicTitle: MusicControl.title
    property string musicArtist: MusicControl.artist
    property bool musicPlayState: MusicControl.playState


    function calMusicPlayTime(musicPlayTime)
    {
        min = musicPlayTime/60
        sec = musicPlayTime%60
    }

    function calCurrentPlayTime(curPlayTime)
    {
        curMin = curPlayTime/60
        curSec = curPlayTime%60
    }


    Component.onCompleted: {
        MusicControl.requestPlayPause(true)
        calCurrentPlayTime(currentPlayTime)
        calMusicPlayTime(musicPlayTime)
    }

    Connections{
        target: MusicControl

        onCurPlayTimeChanged: {
            calCurrentPlayTime(currentPlayTime)
            musicPlaySlider.value = currentPlayTime
        }

        onMediaPlayTimeChanged: {
            calMusicPlayTime(musicPlayTime)
        }

        onCurMediaIndexChanged: {
            musicPlaySlider.value = currentPlayTime
        }

        onPlayStateChanged: {
            musicPlayState = MusicControl.playState
        }

    }

    Rectangle{
        anchors.fill: parent
        color:"#222222"
    }

    MouseArea{
        anchors.fill: parent

    }

    /* Music CoverArt Layout */
    Item{
        id: musicThumbnailImageLayout

        width: 800
        height: 420

        opacity: 0.3
        Image{
            id: musicThumbnailImage

            anchors.fill: parent
            anchors.centerIn: musicThumbnailImageLayout

            source: "file:///"+MusicControl.albumArtPath
        }
    }

    Text{
        id: musicTitleText

        width: 800
        height: 35

        y: 100

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: musicTitle
        font.pixelSize:50
        font.bold: true
        font.family: "SpoqaHanSans"
        color: "white"
    }

    Text{
        id: musicArtistText

        width: 800
        height: 25

        anchors.top: musicTitleText.bottom
        anchors.topMargin: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: musicArtist
        font.pixelSize: 20
        font.family: "SpoqaHanSans"
        color: "white"
    }

    /* Music SliderBar Layout */
    Item{
        id: musicSliderBarLayout

        width: musicPlayerWindow.width
        height: 30

        y:290

        Slider{
            id: musicPlaySlider            

            sliderWidth: 600
            sliderHeight: 10
            sliderColor: "#333333"

            sliderProgressState: true

            sliderPointerWidth: 20
            sliderPointerHeight: 20
            sliderPointerColor: "skyblue"

            maximum: MusicControl.mediaPlayTime
            minimum: 0

            anchors.centerIn: parent

            onSignalPressed: {
                sliderPressState=true
                MusicControl.progressbarPressState(sliderPressState)
            }

            onSignalPressedLong: {

            }
            onSignalReleased: {
                sliderPressState=false
                MusicControl.progressbarPress(value)
                MusicControl.progressbarPressState(sliderPressState)
            }

            onValueChanged: {
                if(sliderPressState)
                    calCurrentPlayTime(value)
            }

        }

        Text{
            id: maxPlayTimeText

            width: 30
            height: 30
            anchors.left: musicPlaySlider.right

            text:{
                if(min<10)
                {
                    if(sec<10)                          "0"+min+":"+"0"+sec
                    else if(sec>10 || sec<60)           "0"+min+":"+sec
                }
                else
                {
                    if(sec<10)                          min+":"+"0"+sec
                    else if(sec>10 || sec<60)           min+":"+sec
                }
            }
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 15
        }

        Text{
            id: currentPlayTimeText

            width: 30
            height: 30
            anchors.right: musicPlaySlider.left

            text:{
                if(curMin<10)
                {
                    if(curSec<10)                           "0"+curMin+":"+"0"+curSec
                    else if(curSec>10 || curSec<60)         "0"+curMin+":"+curSec
                }
                else
                {
                    if(curSec<10)                           curMin+":"+"0"+curSec
                    else if(curSec>10 || curSec<60)         curMin+":"+curSec
                }
            }
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 15
        }
    }


    /* Music Control Button ( Play, Prev, Next ) Layout */
    Item{
        width: musicPlayerWindow.width
        height: 90

        anchors.top: musicSliderBarLayout.bottom


        Item{
            id: musicControlButtonLayout
            width: 600
            height: 90

            anchors.centerIn: parent

            /* Previous Button */
            Item{
                id: prevButtonLayout

                width: 200
                height: 90

                anchors.left: musicControlButtonLayout.left

                Image{
                    id: prevButtonImage

                    width: 100
                    height: 80

                    anchors.centerIn: prevButtonLayout

                    source: prevBtnImageMouseArea.pressed ? "qrc:/media/image/Media_Player_Previous_Pressed.png"
                                                          : "qrc:/media/image/Media_Player_Previous.png"
                    MouseArea{
                        id: prevBtnImageMouseArea
                        anchors.fill: parent

                        onClicked: {
                            MusicControl.requestPrev()
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
                        if(musicPlayState)
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

                        onReleased: {
                            musicPlayState = !musicPlayState
                            MusicControl.requestPlayPause(musicPlayState)
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

                    source: nextBtnImageMouseArea.pressed ? "qrc:/media/image/Media_Player_Next_Pressed.png"
                                                          : "qrc:/media/image/Media_Player_Next.png"
                    MouseArea{
                        id: nextBtnImageMouseArea
                        anchors.fill: parent

                        onClicked: {
                            MusicControl.requestNext()
                        }
                    }
                }
            }
        }
    }
}
