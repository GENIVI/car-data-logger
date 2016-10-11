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
 * \file main.qml
*/

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id : rootQML
    visible: true
    width: 800
    height: 480

//    property bool fixBottom


//    Button{
//        x: 17
//        y: 0
//        width: 103
//        height: 20
//        text: "Auto Scroll"
//        opacity: fixBottom ? 0.8 : 1
//        style: ButtonStyle {
//          label: Text {
//            renderType: Text.NativeRendering
//            verticalAlignment: Text.AlignVCenter
//            horizontalAlignment: Text.AlignHCenter
//            font.family: "Helvetica"
//            font.pixelSize: 13
//            color: "blue"
//            text: control.text
//          }
//        }
//        onClicked: {
////            fixBottom = !fixBottom
//            CDLDataModel.addListItem()
//        }
//    }

    TableView{
        x: 0
        y: 20
        width: 800
        height: 480
        anchors.bottomMargin: 0
        anchors.bottom : rootQML.bottom
        id : tableV

        TableViewColumn{ title: "time";         role: "time";       width: 175; }
//        TableViewColumn{ title: "requester";    role: "requester";  width: 160; }
        TableViewColumn{ title: "domain";       role: "domain";     width: 130; }
        TableViewColumn{ title: "subDomain";    role: "subDomain";  width: 165; }
        TableViewColumn{ title: "dataID";       role: "dataID";     width: 165; }
        TableViewColumn{ title: "dataType";     role: "dataType";   width: 80; }
        TableViewColumn{ title: "dataValue";    role: "dataValue";  width: 65; }

        headerDelegate: Rectangle{
            border.color: "black"
            border.width: 1
            height: 20
            Text{
                anchors.left: parent.left
                anchors.leftMargin: 3
                text : styleData.value
                color : "black"
                font.pixelSize: 11
                font.bold: true
            }
        }


        itemDelegate: Rectangle{
            id : itemItem
            border.color: "lightgray"
            border.width: 1
            color: (styleData.row % 2) ? "lightblue" : "steelblue"
            Text {
                anchors.left: parent.left
                anchors.leftMargin: 3
                id: textItem
                width: parent.width
                text: styleData.value
                color : "black"
                font.pixelSize: 10
                wrapMode: Text.Wrap
                anchors.verticalCenter: parent.verticalCenter
            }
            height: 20
        }
        rowDelegate: Rectangle{ height: 20 }

        Connections {
            target: CDLDataModel
            onShowLastRow: {
                tableV.positionViewAtRow( tableV.rowCount, ListView.End)
            }
        }

//        onRowCountChanged: {
////            if(fixBottom)
////            {
//            console.log("row count = ", rowCount)
////                positionViewAtRow( rowCount-1, ListView.End)
////            selection.clear()
////            selection.select(rowCount-1)
////            }
//        }


        model : CDLDataModel
        selectionMode: 0
    }
}

