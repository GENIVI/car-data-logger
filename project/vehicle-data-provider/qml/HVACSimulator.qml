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
 * \file HVACSimulator.qml
*/

import QtQuick 2.5
import define.CommonEnum 1.0
import "../image"

Item {
    id: hvacDataSimulatorLayout
    objectName: "hvacDataSimulator"

    width: 800-150
    height: 480

    property int fanDirectionFocusIndex: 0
    property bool hvacSystemState: true

    property bool syncValue: false
    property bool airIntake: false
    property bool frontMode: false
    property int fanSpeedLevel: 1
    property int driverTempC: 200
    property int passengerTempC: 200
    property int fanDirectionIndex: CommonEnum.Air_D_FRONT_PANEL    

    property variant fanDirectionImage: [
        "../image/Air Direction_1.png", //Air_D_FRONT_PANEL
        "../image/Air Direction_4.png", //Air_D_FLOOR_DUCT
        "../image/Air Direction_3.png", //Air_D_FRONT_AND_FLOOR
        "../image/Air Direction_2.png", //Air_D_DEFROSTER_AND_FLOOR
        "../image/Air Direction_5.png", //Air_D_DEFROSTER
    ]

    Component.onCompleted: {
        HVAC_Data_Simulator.setSyncMode(syncValue)
        HVAC_Data_Simulator.setAirIntakeMode(airIntake)
        HVAC_Data_Simulator.setFanSpeedLevel(fanSpeedLevel)
        HVAC_Data_Simulator.setFanDirectionMode(fanDirectionIndex)
        HVAC_Data_Simulator.setDriverTempC(driverTempC)
        HVAC_Data_Simulator.setPassengerTempC(passengerTempC)
    }

    onDriverTempCChanged: {
        if(syncValue)
        {
            passengerTempC = driverTempC
            HVAC_Data_Simulator.setPassengerTempC(passengerTempC)
        }
    }

//    onFanDirectionFocusIndexChanged: {
//        if(frontMode)
//        {
//            frontMode = !frontMode
//            HVAC_Data_Simulator.setDefrostWindshiledMode(frontMode)
//        }
//    }



    /* Fan Direction Layout */
    Item{
        id: fanDirectionLayout

        width: 404
        height: 80

        y: 50
        anchors.horizontalCenter: hvacDataSimulatorLayout.horizontalCenter

        Row{
            id: directionButtonRow
            spacing: 1
            Repeater{
                model: 4

                Item{
                    id: fanDirectionBtnLayout
                    width: 80
                    height: 80

                    SampleButton{
                        buttonWidth: 80
                        buttonHeight: 80

                        anchors.centerIn: fanDirectionBtnLayout

                        Image{
                            anchors.centerIn: parent
                            source: fanDirectionImage[index]
                            opacity: {
                                if(hvacSystemState)
                                {
                                    if(frontMode)   0.2
                                    else            (fanDirectionFocusIndex==index) ? 1 : 0.2
                                }
                                else
                                {
                                    0.2
                                }

                            }
                        }

                        onTouchPressed: {

                        }

                        onTouchReleased: {
                            if(!hvacSystemState)
                            {
                                hvacSystemState=true
                            }
                            else
                            {
                                fanDirectionFocusIndex=index
                                fanDirectionIndex = index+1

                                HVAC_Data_Simulator.setFanDirectionMode(fanDirectionIndex)
                                if(frontMode)
                                {
                                    frontMode = !frontMode
                                    HVAC_Data_Simulator.setDefrostWindshiledMode(frontMode)
                                }
                            }

                        }
                    }
                }
            }
        }
    }

    Text{
        id: fanDirectionText
        width: 100
        height: 20
        text: "< Fan Direction >"
        font.pixelSize: 15
        font.bold: true
        font.italic: true
        horizontalAlignment: Text.AlignHCenter
        color: hvacSystemState ? "white" : "#333333"

        anchors.horizontalCenter: fanDirectionLayout.horizontalCenter
        anchors.bottom: fanDirectionLayout.top
    }

    /* Front Mode Layout */
    Item{
        id: frontModeLayout

        width: 80
        height: 80

        anchors.right: fanDirectionLayout.right
        anchors.baseline: fanDirectionLayout.top

        SampleButton{
            id: frontButton

            buttonWidth: frontModeLayout.width
            buttonHeight: frontModeLayout.height

            Image{
                id: frontModeImage

                width: 60
                height: 40
                y: 15
                anchors.horizontalCenter: parent.horizontalCenter

                opacity: hvacSystemState ? 1 : 0.2

                source: "../image/Front.png"
            }

            onTouchPressed: {

            }

            onTouchReleased: {
                if(!hvacSystemState)
                {
                    hvacSystemState=true
                }
                else
                {
                    frontMode = !frontMode;
                    HVAC_Data_Simulator.setDefrostWindshiledMode(frontMode)
                    if(frontMode)
                        HVAC_Data_Simulator.setFanDirectionMode(CommonEnum.Air_D_DEFROSTER)
                    else
                        HVAC_Data_Simulator.setFanDirectionMode(fanDirectionIndex)
                }
            }
        }

        Rectangle{
            id: frontButtonActive

            width: 40
            height: 10
            x: 20
            y: 60
            radius: 10
            color: {
                if(hvacSystemState)
                       frontMode ? "#226699" : "gray"
                   else
                       "gray"
            }
        }
    }

    /* Fan Speed Layout */
    Item{
        id: fanSpeedLayout

        width: 200
        height: 80

        anchors.horizontalCenter: hvacDataSimulatorLayout.horizontalCenter
        anchors.top : fanDirectionLayout.bottom
        anchors.topMargin: 30

        Row{
            id: speedButtonRow
            spacing: 1
            Repeater{
                model: 2

                Item{
                    id: fanSpeedBtnLayout
                    width: fanSpeedLayout.width/2
                    height: fanSpeedLayout.height

                    SampleButton{
                        buttonWidth: fanSpeedLayout.width/2
                        buttonHeight: fanSpeedLayout.height
                        buttonText: (index==0) ? "<" : ">"
                        buttonTextColor: hvacSystemState ? "white" : "#333333"
                        buttonTextSize: 24

                        anchors.centerIn: fanSpeedBtnLayout

                        onTouchPressed: {

                        }

                        onTouchReleased: {
                            if(!hvacSystemState)
                            {
                                hvacSystemState=true
                            }
                            else
                            {
                                if(index==0)
                                {
                                    if(fanSpeedLevel>1)
                                    {
                                        fanSpeedLevel -= 1
                                        HVAC_Data_Simulator.setFanSpeedLevel(fanSpeedLevel)
                                    }
                                }
                                else
                                {
                                    if(fanSpeedLevel<7)
                                    {
                                        fanSpeedLevel += 1
                                        HVAC_Data_Simulator.setFanSpeedLevel(fanSpeedLevel)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Text{
        id: fanSpeedText
        width: 100
        height: 20
        text: "< Fan Speed >"
        font.pixelSize: 15
        font.bold: true
        font.italic: true
        horizontalAlignment: Text.AlignHCenter
        color: hvacSystemState ? "white" : "#333333"

        anchors.horizontalCenter: fanSpeedLayout.horizontalCenter
        anchors.bottom: fanSpeedLayout.top
    }

    /* Sync Button Layout */
    Item{
        id: syncLayout

        width: 80
        height: 80

        anchors.right: fanSpeedLayout.left
        anchors.baseline: fanSpeedLayout.top
        anchors.rightMargin: 20

        SampleButton{
            id: syncButton

            buttonWidth: syncLayout.width
            buttonHeight: syncLayout.height
            buttonText: "SYNC"
            buttonTextColor: hvacSystemState ? "white" : "#333333"
            buttonTextSize: 24

            onTouchPressed: {

            }

            onTouchReleased: {
                if(!hvacSystemState)
                {
//                    hvacSystemState=true
                }
                else
                {
                    syncValue = !syncValue;
                    HVAC_Data_Simulator.setSyncMode(syncValue)
                }
            }

            Rectangle{
                id: syncButtonActive

                width: 40
                height: 10
                x: 20
                y: 60
                radius: 10
                color: {
                    if(hvacSystemState) syncValue ? "#226699" : "gray"
                    else                "gray"
                }
            }
        }
    }

    /* Air Circulator Button Layout */
    Item{
        id: airIntakeLayout

        width: 80
        height: 80

        anchors.left: fanSpeedLayout.right
        anchors.baseline: fanSpeedLayout.top
        anchors.leftMargin:  20

        SampleButton{
            id: airIntakeButton

            buttonWidth: airIntakeLayout.width
            buttonHeight: airIntakeLayout.height

            Image{
                id: airIntakeImage

                width: 60
                height: 40
                y: 15
                anchors.horizontalCenter: parent.horizontalCenter

                opacity: airIntake ? 1 : 0.2

                source: "../image/Air Circulation.png"
            }

            onTouchPressed: {

            }

            onTouchReleased: {
//                if(!hvacSystemState)
//                {
//                    hvacSystemState=true
//                }
//                else
//                {
                    airIntake = !airIntake
                    HVAC_Data_Simulator.setAirIntakeMode(airIntake)
//                }
            }

            Rectangle{
                id: airIntakeButtonActive

                width: 40
                height: 10
                x: 20
                y: 60
                radius: 10
                color: {
//                    if(hvacSystemState) airIntake ? "#226699" : "gray"
//                    else                "gray"
                    airIntake ? "#226699" : "gray"
                }
            }
        }
    }

    /* OFF Button Layout */
    Item{
        id: offButtonLayout

        width: 100
        height: 80

        anchors.top: fanSpeedLayout.bottom
        anchors.horizontalCenter: hvacDataSimulatorLayout.horizontalCenter
        anchors.topMargin: 30

        SampleButton{
            id: offButton

            buttonWidth: offButtonLayout.width
            buttonHeight: offButtonLayout.height
            buttonText: "OFF"
//            buttonTextColor: hvacSystemState ? "white" : "#333333"
            buttonTextColor: "#333333"
            buttonTextSize: 24

//            onTouchPressed: {

//            }

//            onTouchReleased: {
//                if(hvacSystemState)
//                {
//                    hvacSystemState=false
//                }
//                else
//                {
//                    print("HVAC System is Already OFF")
//                }
//            }
        }
    }

    Text{
        id: systemStateText
        width: 100
        height: 80
        text: "< SysTem State >\n"+(hvacSystemState?"ON":"OFF")
        font.pixelSize: 18
        font.bold: true
        font.italic: true
        horizontalAlignment: Text.AlignHCenter
        color: hvacSystemState ? "white" : "#333333"

        anchors.topMargin: 30
        anchors.horizontalCenter: offButtonLayout.horizontalCenter
        anchors.top: offButtonLayout.bottom
    }

    /* Driver Temperature Layout */
    Item{
        id: driverTempLayout

        width: 80
        height: 160

        anchors.right: offButtonLayout.left
        anchors.rightMargin: 70
        anchors.top: airIntakeLayout.bottom
        anchors.topMargin: 30

        Column{
            id: driverTempCol
            spacing: 1
            Repeater{
                model: 2

                Item{
                    id: driverTempBtnLayout
                    width: driverTempLayout.width
                    height: driverTempLayout.height/2

                    SampleButton{
                        buttonWidth: driverTempLayout.width
                        buttonHeight: driverTempLayout.height/2
                        buttonText: (index==0) ? "+" : "-"
                        buttonTextColor: hvacSystemState ? "white" : "#333333"
                        buttonTextSize: 24

                        anchors.centerIn: driverTempBtnLayout

                        onTouchPressed: {

                        }

                        onTouchReleased: {
                            if(!hvacSystemState)
                            {
                                hvacSystemState=true
                            }
                            else
                            {
                                if(index==0)
                                {
                                    if(driverTempC < 320 )
                                    {
                                        driverTempC += 5
                                        HVAC_Data_Simulator.setDriverTempC(driverTempC)
                                    }
                                }
                                else
                                {
                                    if(driverTempC > 150)
                                    {
                                        driverTempC -= 5
                                        HVAC_Data_Simulator.setDriverTempC(driverTempC)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Text{
        id: driverTempText
        width: 100
        height: 20
        text: "< Driver Temp >"
        font.pixelSize: 15
        font.bold: true
        font.italic: true
        horizontalAlignment: Text.AlignHCenter
        color: hvacSystemState ? "white" : "#333333"

        anchors.horizontalCenter: driverTempLayout.horizontalCenter
        anchors.bottom: driverTempLayout.top
    }

    /* Passenger Temperature Layout */
    Item{
        id: passengerTempLayout

        width: 80
        height: 160

        anchors.left: offButtonLayout.right
        anchors.leftMargin: 70
        anchors.top: airIntakeLayout.bottom
        anchors.topMargin: 30

        Column{
            id: passengerTempCol
            spacing: 1
            Repeater{
                model: 2

                Item{
                    id: passengerTempBtnLayout
                    width: passengerTempLayout.width
                    height: passengerTempLayout.height/2

                    SampleButton{
                        buttonWidth: passengerTempLayout.width
                        buttonHeight: passengerTempLayout.height/2
                        buttonText: (index==0) ? "+" : "-"
                        buttonTextColor: hvacSystemState ? "white" : "#333333"
                        buttonTextSize: 24

                        anchors.centerIn: passengerTempBtnLayout

                        onTouchPressed: {

                        }

                        onTouchReleased: {
                            if(!hvacSystemState)
                            {
                                hvacSystemState=true
                            }
                            else
                            {
                                if(index==0)
                                {
                                    if(passengerTempC < 320 )
                                    {
                                        passengerTempC += 5
                                        HVAC_Data_Simulator.setPassengerTempC(passengerTempC)
                                    }
                                }
                                else
                                {
                                    if(passengerTempC > 150)
                                    {
                                        passengerTempC -= 5
                                        HVAC_Data_Simulator.setPassengerTempC(passengerTempC)
                                    }
                                }

                                if(syncValue)
                                {
                                    syncValue = !syncValue
                                    HVAC_Data_Simulator.setSyncMode(syncValue)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Text{
        id: passengerTempText
        width: 100
        height: 20
        text: "< Passenger Temp >"
        font.pixelSize: 15
        font.bold: true
        font.italic: true
        horizontalAlignment: Text.AlignHCenter
        color: hvacSystemState ? "white" : "#333333"

        anchors.horizontalCenter: passengerTempLayout.horizontalCenter
        anchors.bottom: passengerTempLayout.top
    }

}

