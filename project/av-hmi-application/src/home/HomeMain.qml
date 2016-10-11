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
 * \file homeMain.qml
*/

import QtQuick 2.5

import "qrc:/component"

Item{
    id: homeMainWindow

    width : 800
    height : 480
    objectName: "homeMain"

    property bool backButtonStatus: false
    property variant homeModeImage:[
        "image/Home_Music.png",
        "image/Home_Video.png",
        "image/Home_Setup.png"
    ]

    function loadChildPage(index)
    {
        switch(index)
        {
        case 0: //musicPlayer
            musicPlayerLoader.source="qrc:/media/MusicPlayer.qml"
            musicPlayerLoader.visible=true
            videoPlayerLoader.visible=false
            hvacControlLoader.visible=false
            break

        case 1: //videoPlayer
            videoPlayerLoader.source="qrc:/media/VideoPlayer.qml"
            musicPlayerLoader.visible=false
            videoPlayerLoader.visible=true
            hvacControlLoader.visible=false
            break

        case 2: //HVAC View
            hvacControlLoader.source="qrc:/setup/SetupClimate.qml"
            musicPlayerLoader.visible=false
            videoPlayerLoader.visible=false
            hvacControlLoader.visible=true
            break
        default:
            break
        }
    }

    function backModeChange()
    {
        if(musicPlayerLoader.visible)       musicPlayerLoader.visible=false
        else if(videoPlayerLoader.visible)  videoPlayerLoader.visible=false
        else                                hvacControlLoader.visible=false
    }

    Component.onCompleted: {
        print("HomeMain View Init()")
    }

    Connections{
        target: ModeManager

        onLowFuelWarningStateChanged:{
            if(ModeManager.lowFuelWarningState)
            {
                lowFuelWarningLoader.visible=true
            }
            else
            {
                lowFuelWarningLoader.visible=false
            }
        }
    }

    Rectangle{
        id: homeMainLayout

        width : parent.width
        height : parent.height

        color: "#222222"
    }

    SampleButton{
        id: backButton

        buttonWidth: 100
        buttonHeight: 40
        z:1
        anchors.top: parent.top
        anchors.right: parent.right

        customButtonColor: "#111111"

        buttonText: "Back"
        buttonTextSize: 20

        onTouchPressed: {

        }
        onTouchReleased: {
            backModeChange()
        }
    }

    Item{
        id: modeEntryLayout

        width: homeMainWindow.width
        height: homeMainWindow.height/3

        anchors.verticalCenter: homeMainWindow.verticalCenter

        Row{
            id: modeEntryButtonRow
            Repeater{
                model: 3

                Item{
                    id: modeEntryButtonLayout

                    width: modeEntryLayout.width/3
                    height: 100

                    SampleButton{
                        id: modeButton
                        buttonWidth: 150
                        buttonHeight: 150

                        anchors.centerIn: parent
                        Image{
                            anchors.centerIn: parent
                            source: homeModeImage[index]
                        }

                        Text{
                            id: modeTitle

                            width: 150
                            height: 30

                            text: (index==0) ? "Music" : (index==1) ? "Video" : "Climate"
                            font.pixelSize: 20
                            font.bold: true
                            font.family: "SpoqaHanSans"
                            color: "white"

                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.bottom: modeButton.bottom
                            anchors.horizontalCenter: modeButton.horizontalCenter
                        }

                        onTouchReleased: {
                            if(index==3)
                                loadChildPage(index)
                            else
                            {
                                ModeManager.requestGoMedia(index)
                                loadChildPage(index)
                            }
                        }

                    }
                }
            }
        }
    }

    Loader{
        id: musicPlayerLoader
        source: ""
        visible: false
    }

    Loader{
        id: videoPlayerLoader
        source: ""
        visible: false
    }

    Loader{
        id: hvacControlLoader
        source: ""
        visible: false
    }

    Loader{
        id: lowFuelWarningLoader
        source: "LowFuelWarningPopup.qml"
        visible: false

        onVisibleChanged: {
            if(lowFuelWarningLoader.visible)
                backButton.enabled=false
            else
                backButton.enabled=true
        }
    }
}
