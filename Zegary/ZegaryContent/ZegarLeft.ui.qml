

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Studio.Components
import QtQuick.Shapes 1.0

Rectangle {
    id: tlo
    width: 550
    height: 550
    property int rotate: 200

    color: "#151414"
    states: [
        State {
            name: "clicked"
        }
    ]

    ArcItem {
        id: zegarArc1
        x: 50
        y: 50
        width: 450
        height: 450
        begin: -150
        strokeColor: "#797979"
        capStyle: 32
        strokeWidth: 15
        end: 0
        fillColor: "#00000000"
    }

    ArcItem {
        id: zegarArc2
        x: 75
        y: 75
        width: 400
        height: 400
        begin: -150
        strokeWidth: 10
        strokeColor: "#80797979"
        fillColor: "#00000000"
        end: 0
        capStyle: 32
    }

    ArcItem {
        id: zegarArc3
        x: 95
        y: 95
        width: 360
        height: 360
        begin: -150
        strokeWidth: 5
        strokeColor: "#40797979"
        fillColor: "#00000000"
        end: 0
        capStyle: 32
    }

    Text {
        id: licznik
        x: 205
        y: 215
        width: 140
        height: 120
        color: "#79797979"
        text: rotate.toString()
        font.pixelSize: 90
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false
    }

    Text {
        id: licznik1
        x: 205
        y: 280
        width: 140
        height: 120
        color: "#79797979"
        text: "km/h"
        font.pixelSize: 50
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false
    }

    GroupItem {
        id: rotator
        x: 276
        y: 235
        width: 250
        height: 80
        rotation: 120 + rotate / 1.5
        transformOrigin: Item.Left

        RectangleItem {
            id: suwak
            x: 150
            y: 35
            width: 100
            height: 10
            gradient: LinearGradient {
                y2: suwak.height * 1
                y1: suwak.height * 0
                x2: suwak.width * 1
                x1: suwak.width * 0
                GradientStop {
                    position: 0
                    color: "#4d797979"
                }

                GradientStop {
                    position: 1
                    color: "#797979"
                }
            }
            strokeWidth: 0
            strokeColor: "#00ff0000"
            adjustBorderRadius: true
        }
    }
}
