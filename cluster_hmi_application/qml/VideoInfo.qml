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

import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: control

    width: 300
    height: 270

    property string fileName: AVDataManager.fileName //'AOA - 사뿐사뿐(Like a Cat) Music Video.mp4'
    property string curPosition
    property int hour
    property int min
    property int sec

    Connections{
        target: AVDataManager

        onCurrentPositionChanged: {
            curPosition = calTimePosition(currentPosition)
        }
    }

    function calTimePosition(curPos)
    {
        var tmp
        hour = curPos / 3600
        tmp = curPos % 3600
        min = tmp / 60
        sec = curPos % 60


        if( hour < 10 )
        {
            if( min < 10 )
            {
                if( sec < 10 )  curPosition = "0"+hour+" : "+"0"+min.toString()+" : "+"0"+sec.toString()
                else            curPosition = "0"+hour+" : "+"0"+min.toString()+" : "+sec.toString()
            }
            else
            {
                if( sec < 10 )  curPosition = "0"+hour+" : "+min.toString()+" : "+"0"+sec.toString()
                else            curPosition = "0"+hour+" : "+min.toString()+" : "+sec.toString()
            }
        }
        else
        {
            if( min < 10 )
            {
                if( sec < 10 )  curPosition = hour+"0"+" : "+min.toString()+" : "+"0"+sec.toString()
                else            curPosition = hour+"0"+" : "+min.toString()+" : "+sec.toString()
            }
            else
            {
                if( sec < 10 )  curPosition = hour+" : "+min.toString()+" : "+"0"+sec.toString()
                else            curPosition = hour+" : "+min.toString()+" : "+sec.toString()
            }
        }

        return curPosition
    }

    MarqueeLabel {
        id: text_title
        y: control.height/3
        width: control.width/5*4
        height: 50

        fontFamily: "SpoqaHanSans"
        scrollingTextMargin: 20
        fontSize: 26
        fontStyle: Text.Outline
        fontBold: true
        baselineOffset: -12
        anchors.bottom: parent.top
        anchors.bottomMargin: -156
        anchors.horizontalCenter: parent.horizontalCenter
        text: fileName
        color: "white"
        running: control.visible
    }

    Text {
        id: playTime

        y: control.height/3*2
        width: control.width

        opacity: main.state === "video" ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }

        color: "white"
        text: curPosition
        font.family: "SpoqaHanSans"
        font.bold: true
        font.pixelSize: 21

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
