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
 * \file setupClimate.qml
*/

import QtQuick 2.5

Item{
    id: setupClimateWindow
    objectName: "setupClimate"

    width: 800
    height: 420

    property bool sync: DatcControl.sync
    property bool frontDefrost: DatcControl.frontDefrost
    property bool airCirculation: DatcControl.airCirculation

    property int airDirection: DatcControl.airDirection
    property int airVolume: DatcControl.airVolume
    property var driverTemp: DatcControl.driverSeat
    property var passengerTemp: DatcControl.passengerSeat

    property variant airDirectionImage: [
        "image/DATC/Air Direction_1.png",
        "image/DATC/Air Direction_3.png",
        "image/DATC/Air Direction_4.png",
        "image/DATC/Air Direction_2.png",
        "image/DATC/Air Direction_5.png",
    ]

    property variant airVolumeImage: [
        "",
        "image/DATC/Air Volume_1.png",
        "image/DATC/Air Volume_2.png",
        "image/DATC/Air Volume_3.png",
        "image/DATC/Air Volume_4.png",
        "image/DATC/Air Volume_5.png",
        "image/DATC/Air Volume_6.png",
        "image/DATC/Air Volume_max.png"
    ]

    Component.onCompleted: {
        print("Enter Climate Player View")
    }

    Rectangle{
        id: setupClimateBg

        anchors.fill: parent
        color: "#222222"
    }

    Image {
        id: bgClimate

        z:0
        width: 800
        height: 480
        source: "image/DATC/Climate_car.png"

        Item{
            id: syncDisplayBox

            width: 156
            height: 118
            x: 86
            y: 54

            CommonClimate{
                id: syncData

                anchors.fill: parent

                boolTypeImageDataState: true
                climateDataTitle: "SYNC"
                titleTextSize: 20

                imageDataPath:"image/DATC/SYNC.png"

                boolTypeImageData: sync
            }
        }


        Item{
            id: passengerTempDisplayBox

            width: 156
            height: 118
            x: 268
            y: 54

            CommonClimate{
                anchors.fill: parent

                textTypeDataState: true
                climateDataTitle: "Passenger Seat"
                titleTextSize: 20

                textData: passengerTemp
                textDataSize: 28
            }
        }

        Item{
            id: airDrectionDisplayBox

            width: 156
            height: 118
            x: 450
            y: 54

            CommonClimate{
                anchors.fill: parent

                levelTypeImageDataState: true
                climateDataTitle: "Air Direction"
                titleTextSize: 20

                imageDataPath: airDirectionImage[airDirection]

                levelTypeImageData: airDirection
            }
        }

        Item{
            id: airCirculationDisplayBox

            width: 156
            height: 118
            x: 620
            y: 182

            CommonClimate{
                anchors.fill: parent

                boolTypeImageDataState: true
                climateDataTitle: "Air Circulation"
                titleTextSize: 20

                imageDataPath:"image/DATC/Air Circulation.png"

                boolTypeImageData: airCirculation
            }
        }

        Item{
            id: frontDisplayBox

            width: 156
            height: 118
            x: 86
            y: 182

            CommonClimate{
                id: frontData

                anchors.fill: parent

                boolTypeImageDataState: true
                climateDataTitle: "Front"
                titleTextSize: 20

                imageDataPath:"image/DATC/Front.png"

                boolTypeImageData: frontDefrost
            }
        }

        Item{
            id: driverTempDisplayBox

            width: 156
            height: 118
            x: 268
            y: 340

            CommonClimate{
                id: driverTempData

                anchors.fill: parent

                textTypeDataState: true
                climateDataTitle: "Driver Seat"
                titleTextSize: 20

                textData: driverTemp
                textDataSize: 28
            }
        }

        Item{
            id: airVolumeDisplayBox

            width: 156
            height: 118
            x: 450
            y: 340

            CommonClimate{
                id: airVolumeData

                anchors.fill: parent

                levelTypeImageDataState: true
                climateDataTitle: "Air Volume"
                titleTextSize: 20

                imageDataPath: airVolumeImage[airVolume]

                levelTypeImageData: airVolume
            }
        }


    }

    Text{
        text: "setupClimate"
        anchors.centerIn: parent
        font.pixelSize: 30
    }

    MouseArea{
        anchors.fill: parent

    }
}
