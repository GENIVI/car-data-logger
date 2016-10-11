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
 * \file Gauge.qml
*/

import QtQuick 2.2
import QtGraphicalEffects 1.0
import GaugeArea 1.0

Item {
    id: gauge
    objectName: 'Gauge'
    width: 67
    height: 279
    property url normalImage
    property url activeImage
    property string type: '' // ['rpm', 'fuel']
    property real value: 1 // rpm: 0-8000~, fuel: 0~100
    property real realAngle
    property bool animationEnable: false

    Behavior on realAngle {
        enabled: animationEnable
        SmoothedAnimation { easing.type: Easing.InOutBack; velocity: 1000 }
//        NumberAnimation { easing.type:Easing.InOutBack; duration: 100 }
    }

    onValueChanged: {
        if (type === 'rpm')
        {
            realAngle = -120 + 0.007*value
        }
        else if (type === 'fuel')
        {
            realAngle = 120 - 0.56*value
        }
        else
        {

        }
    }

    Image {
        id: normal
        source: normalImage//'../image/gauge_image/gauge_normal.left.png'
    }

    Image {
        id: gaugeArrow
        width: 11
        height: 142
        source: '../image/gauge_image/gauge_arrow.png'

        transform: Rotation {
            id: gaugeArrowAnglePoint
            angle: realAngle
            origin.x: 5.5
            origin.y: 240+71
        }
    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            console.log(parent.objectName, mouseY)
//            activeArea.height = parent.height - mouseY
//        }
//    }

    GaugeArea {
        id: gaugeArea
        width: 622
        height: 622
        endAngle: realAngle
        myUrl: activeImage//'../image/gauge_image/gauge_color.left.png'
    }

    Timer {
        id: timer
        interval: 600
        repeat: true
        onTriggered: {
            if (type === 'rpm')
            {
                value = Math.random()*8500
            }
            else if (type === 'fuel')
            {
                value = Math.random()*100
            }
            else
            {

            }
        }
    }

    function setType()
    {
        if (type === 'rpm')
        {
            gaugeArrow.x = -89+394.5
            gaugeArrow.y = -103-71

            gaugeArea.x = 0
            gaugeArea.y = -71-103
            gaugeArea.startAngle = -120
            gaugeArea.type = GaugeArea.GT_RPM
        }
        else if (type == 'fuel')
        {
            gaugeArrow.x = -645+394.5
            gaugeArrow.y = -103-71

            gaugeArea.x = -645+89
            gaugeArea.y = -71-103
            gaugeArea.startAngle = 120
            gaugeArea.type = GaugeArea.GT_FUEL
        }
        else
        {

        }
    }

    Component.onCompleted: {
        setType()
        animationEnable = true

        // FIXME. test code.
//        timer.start()
    }
}
