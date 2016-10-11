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
 * \file simulator.qml
*/

import QtQuick 2.5

import define.CommonEnum 1.0

Item {
    id: simulatorMainWindow
    objectName: "simulatorMainWindow"

    width: 800
    height: 480

    property int focusIndex: 0

    function loadChildPage(index)
    {
        switch(index)
        {
        case CommonEnum.VEHICLE_SIMULATOR_TYPE:
            vehicleSimulatorViewLoader.source="VehicleDataSimulator.qml"
            vehicleSimulatorViewLoader.visible=true
            hvacSimulatorViewLoader.visible=false
            break

        case CommonEnum.HVAC_SIMULATOR_TYPE:
            hvacSimulatorViewLoader.source="HVACSimulator.qml"
            vehicleSimulatorViewLoader.visible=false
            hvacSimulatorViewLoader.visible=true
            break
        default:
            break
        }
    }

    Component.onCompleted: {
        loadChildPage(focusIndex)
    }

    Rectangle{
        id: mainWindow
        anchors.fill: parent
        color: "#444444"

        Item{
            id: tabViewLayout
            width: 150
            height: 480

            anchors.left: mainWindow.left

            Column{
                id: buttonColumn
                Repeater{
                    model: 2

                    Item{
                        id: buttonLayout
                        width: tabViewLayout.width
                        height: tabViewLayout.height/3

                        SampleButton{
                            buttonWidth: tabViewLayout.width-4
                            buttonHeight: tabViewLayout.height/3-4
                            buttonText: (index==0) ? "Running Status":(index==1) ? "Climates" : ""
                            buttonTextSize: 20
                            buttonTextColor: (focusIndex==index) ? "black" : "white"
                            buttonColor: (focusIndex==index) ? "skyblue" : "#222222"

                            anchors.centerIn: buttonLayout

                            onTouchPressed: {
                                focusIndex=index
                            }
                            onTouchReleased: {
                                loadChildPage(index)
                            }
                        }
                    }
                }
            }
        }   //tabView Layout

        Item{
            id: simulatorLayout
            x: tabViewLayout.width
            y: 0
            width: mainWindow.width-tabViewLayout.width
            height: mainWindow.height

            Loader{
                id: vehicleSimulatorViewLoader
                source: ""
                focus: true
                visible: true

            }

            Loader{
                id: hvacSimulatorViewLoader
                source: ""
                focus: true
                visible: true

            }
        }   //simulatorView Layout
    }

}
