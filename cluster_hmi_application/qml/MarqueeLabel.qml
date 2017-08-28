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

import QtQuick 2.3

Item {
    id: control
    objectName: "MarqueeLabel"
    clip: true
    width: 100
    height: 50

    property string text: "Input text"
    property string fontFamily: "SpoqaHanSans Bold"
    property bool fontBold: false
    property int fontSize : 16
    property int fontStyle: Text.Normal
    property color color: "#ffffff"
    property bool running: true
    property real scrollingTextMargin: fontSize

    property int horizontalAlignment: Text.AlignHCenter
    property real baselineOffset: -control.height/3

    Component.onCompleted: setScroll()

    onRunningChanged: setScroll()
    onVisibleChanged: setScroll()
    onTextChanged: {
        originText.text = text
        scrollText.text = text
        setScroll()
    }
    onFontFamilyChanged: setScroll()

    function setScroll()
    {
        scrollStartAni.running = false

        originText.anchors.leftMargin = 0

        if(control.running && control.visible) {
            originText.elide = Text.ElideNone
            originText.width = scrollText.width

            if(originText.width > control.width) {
                scrollStartAni.running = true
            }
            else {
                originText.width = control.width
            }

        } else {
            originText.elide = Text.ElideNone
            originText.width = control.width
            if(originText.paintedWidth > control.width) {
                scrollStartAni.running = false
                originText.elide = Text.ElideRight
            }
        }
    }

    //![Label]
    Text {
        id: originText
        font.pixelSize: control.fontSize
        font.family: control.fontFamily
        font.bold: control.fontBold
//        style: fontStyle
        horizontalAlignment: control.horizontalAlignment
        color: control.color
        anchors.baseline: parent.bottom
        anchors.baselineOffset: control.baselineOffset
        anchors.left: control.left
        anchors.right: undefined
        clip: false
    }

    Text {
        id: scrollText
        font.pixelSize: control.fontSize
        font.family: control.fontFamily
        font.bold: control.fontBold
//        style: fontStyle
        horizontalAlignment: control.horizontalAlignment
        color: control.color
        visible: scrollStartAni.running
        anchors.baseline: control.bottom
        anchors.baselineOffset: control.baselineOffset
        anchors.left: originText.left
        anchors.right: undefined
        anchors.leftMargin: originText.paintedWidth + control.scrollingTextMargin
        anchors.rightMargin: undefined
        clip: false
    }

    //![Animation]
    SequentialAnimation {
        id: scrollStartAni
        running: false
        loops: Animation.Infinite
        PauseAnimation { duration: 2000 }
        PropertyAnimation {
            target: originText
            property: "anchors.leftMargin"
            to: -(originText.paintedWidth + scrollingTextMargin)
            duration: Math.floor( Math.abs(originText.paintedWidth + scrollingTextMargin) * 30)
            easing.type: Easing.InOutQuad
        }
        PropertyAction { target: originText; property: "anchors.leftMargin"; value: 0 }
    }
}
