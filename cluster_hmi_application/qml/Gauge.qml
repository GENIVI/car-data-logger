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

import QtQuick 2.2
import QtGraphicalEffects 1.0
import GaugeArea 1.0

Item {
    id: gauge
    objectName: 'Gauge'
    width: 459
    height: 455

    property url needleImageURL
    property url activeImage
    property string type: '' // ['rpm', 'fuel']
    property real value: 1 // rpm: 0-8000~, fuel: 0~100
    property real realAngle
    property bool animationEnable: false

    onValueChanged: {
        if (type === 'rpm')
        {
            realAngle = (value - 4000) * 0.03
        }
        else if (type === 'speed')
        {
            realAngle = (value - 120)
        }
        else
        {

        }
    }

    GaugeArea {
        id: gaugeArea
        width: 459
        height: 455

        endAngle: realAngle
        myUrl: activeImage
    }

    Image {
        id: clusterCenterBack
        source: "../image/genivi_16th_amm/cluster/center_bg_back.png"

        anchors.left: gaugeArea.left
        anchors.leftMargin: 100
        anchors.top: gaugeArea.top
        anchors.topMargin: 111
    }

    Image {
        id: speedClusterNumber
        source: "../image/genivi_16th_amm/cluster/Speed_number.png"

        visible: false
        anchors.left: gaugeArea.left
    }

    Image {
        id: rpmdClusterNumber
        source: "../image/genivi_16th_amm/cluster/Rpm_number.png"

        visible: false
        anchors.left: gaugeArea.left
    }

    Image {
        id: gaugeArrow
        source: needleImageURL

        x: parent.width/2
        y: parent.height/2

        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/2
        anchors.left: parent.left
        anchors.leftMargin: parent.width/2 - 10

        transform: Rotation {
            origin.x: gaugeArrow.width/2; origin.y: 455/2-gaugeArrow.y;
            angle:realAngle
        }
    }

    function setType()
    {
        if (type === 'rpm')
        {
            rpmdClusterNumber.visible=true
            gaugeArea.startAngle = -120
            gaugeArea.type = GaugeArea.GT_RPM
        }
        else if (type == 'speed')
        {
            speedClusterNumber.visible=true
            gaugeArea.startAngle = -120
            gaugeArea.type = GaugeArea.GT_SPEED
        }
        else
        {

        }
    }

    Component.onCompleted: {
        setType()
        animationEnable = false
    }
}
