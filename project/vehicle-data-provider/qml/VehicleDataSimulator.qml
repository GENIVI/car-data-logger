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
 * \file VehicleDataSimulator.qml
*/

import QtQuick 2.5

import define.CommonEnum 1.0

Item {
    id: vehicleDataSimulatorLayout
    objectName: "vehicleDataSimulator"

    width: 800-150
    height: 480

    property int fuelLevel: 50
    property int vehicleSpeed: 0
    property int engineSpeed: 0

    Component.onCompleted: {
        Vehicle_Data_Simulator.setFuelLevel(fuelLevel)
        Vehicle_Data_Simulator.setVehicleSpeedLevel(vehicleSpeed)
        Vehicle_Data_Simulator.setEngineSpeedLevel(engineSpeed)
    }

    onFuelLevelChanged: {
        Vehicle_Data_Simulator.setFuelLevel(fuelLevel)
    }

    onVehicleSpeedChanged: {
        Vehicle_Data_Simulator.setVehicleSpeedLevel(vehicleSpeed)
    }

    onEngineSpeedChanged: {
        Vehicle_Data_Simulator.setEngineSpeedLevel(engineSpeed)
    }

    /* Fuel Simulator */
    Item{
        id: fuelLayout
        width: vehicleDataSimulatorLayout.width
        height: vehicleDataSimulatorLayout.height/3

        Item{
            id: fuelSimulatorTitleLayout
            width: vehicleDataSimulatorLayout.width/4
            height: fuelLayout.height

            Text{
                id: fuelSimulatorTitle
                width: 100
                height: 80
                text: "Fuel Control\n(0~100)"
                font.pixelSize: 22
                font.bold: true
                font.italic: true
                color: "white"

                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: fuelSimulatorTitleLayout
            }
        }

        Item{
            id: fuelValueLayout
            width: vehicleDataSimulatorLayout.width-vehicleDataSimulatorLayout.width/4
            height: fuelLayout.height

            anchors.left: fuelSimulatorTitleLayout.right

            Slider{
                id: fuelLevelSlider

                sliderWidth: 400
                sliderHeight: 20
                sliderColor: "#333333"

                sliderPointerWidth: 20
                sliderPointerHeight: 20
                sliderPointerColor: "skyblue"

                value: fuelLevel

                maximum: 100
                minimum: 0
                anchors.centerIn: parent

                onValueChanged: {
                    fuelLevel=value
                }
            }

            Text{
                id: fuelLevelText
                width: 100
                height: 80
                text: fuelLevel
                font.pixelSize: 27
                font.bold: true
                font.italic: true
                color: "white"

                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                anchors.bottom: fuelLevelSlider.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }



    /* Speed Simulator */
    Item{
        id: speedLayout
        width: vehicleDataSimulatorLayout.width
        height: vehicleDataSimulatorLayout.height/3

        anchors.top: fuelLayout.bottom

        Item{
            id: speedSimulatorTitleLayout
            width: vehicleDataSimulatorLayout.width/4
            height: speedLayout.height

            Text{
                id: speedSimulatorTitle
                width: 100
                height: 80
                text: "Speed Control\n(0~230)"
                font.pixelSize: 22
                font.bold: true
                font.italic: true
                color: "white"

                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: speedSimulatorTitleLayout
            }
        }

        Item{
            id: speedValueLayout
            width: vehicleDataSimulatorLayout.width-vehicleDataSimulatorLayout.width/4
            height: speedLayout.height

            anchors.left: speedSimulatorTitleLayout.right

            Slider{
                id: speedValueSlider

                sliderWidth: 400
                sliderHeight: 20
                sliderColor: "#333333"

                sliderPointerWidth: 20
                sliderPointerHeight: 20
                sliderPointerColor: "skyblue"

                value: vehicleSpeed

                maximum: 230
                minimum: 0
                anchors.centerIn: parent

                onValueChanged: {
                    vehicleSpeed=value
                }
            }

            Text{
                id: speedDataText
                width: 100
                height: 80
                text: vehicleSpeed
                font.pixelSize: 27
                font.bold: true
                font.italic: true
                color: "white"

                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                anchors.bottom: speedValueSlider.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    /* EngineSpeed Simulator */
    Item{
        id: engineSpeedLayout
        width: vehicleDataSimulatorLayout.width
        height: vehicleDataSimulatorLayout.height/3

        anchors.top: speedLayout.bottom

        Item{
            id: engineSpeedSimulatorTitleLayout
            width:vehicleDataSimulatorLayout.width/4
            height: engineSpeedLayout.height
            Text{
                id: engineSpeedSimulatorTitle
                width: 100
                height: 80
                text: "RPM Control\n(0~8000)"
                font.pixelSize: 22
                font.bold: true
                font.italic: true
                color: "white"

                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: engineSpeedSimulatorTitleLayout
            }
        }

        Item{
            id: engineSpeedValueLayout
            width: vehicleDataSimulatorLayout.width-vehicleDataSimulatorLayout.width/4
            height: engineSpeedLayout.height

            anchors.left: engineSpeedSimulatorTitleLayout.right

            Slider{
                id: engineSpeedValueSlider

                sliderWidth: 400
                sliderHeight: 20
                sliderColor: "#333333"

                sliderPointerWidth: 20
                sliderPointerHeight: 20
                sliderPointerColor: "skyblue"

                value: engineSpeed

                maximum: 8000
                minimum: 0
                anchors.centerIn: parent

                onValueChanged: {
                    engineSpeed=value
                }
            }

            Text{
                id: engineSpeedDataText
                width: 100
                height: 80
                text: engineSpeed
                font.pixelSize: 27
                font.bold: true
                font.italic: true
                color: "white"

                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                anchors.bottom: engineSpeedValueSlider.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
