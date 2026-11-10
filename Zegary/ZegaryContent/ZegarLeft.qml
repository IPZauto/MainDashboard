import QtQuick
import QtQuick.Controls
import QtQuick.Shapes

Rectangle {
    id: tlo
    width: 550
    height: 550
    color: research.background

    states: [
        State {
            name: "clicked"
        }
    ]

    GaugeArc {
        id: zegarArc1
        x: 50
        y: 50
        width: 450
        height: 450
        begin: -150
        strokeColor: research.foreground
        capStyle: ShapePath.RoundCap
        strokeWidth: 15
        end: 0
        fillColor: "#00000000"

    }

    GaugeArc {
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
        capStyle: ShapePath.RoundCap
    }

    GaugeArc {
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
        capStyle: ShapePath.RoundCap
    }

    Text {
        id: licznik
        x: 205
        y: 215
        width: 140
        height: 120
        color: research.foreground
        text: backend.speed.toString()
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
        color: research.foreground
        text: "km/h"
        font.pixelSize: 50
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false

    }

    Item {
        implicitWidth: Math.max(16, childrenRect.width + childrenRect.x)
        implicitHeight: Math.max(16, childrenRect.height + childrenRect.y)
        id: rotator
        x: 276
        y: 235
        width: 250
        height: 80
        rotation: 120 + backend.speed / 1.5
        transformOrigin: Item.Left

        GradientRectangle {
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
                    color: "#e8e8e8"
                }
            }
        }
    }

    Item {
        implicitWidth: Math.max(16, childrenRect.width + childrenRect.x)
        implicitHeight: Math.max(16, childrenRect.height + childrenRect.y)
        id: tempomat
        x: 370
        y: 220

        Image {
            id: tempomatIcon
            x: 0
            y: 0
            width: 128
            height: 64
            visible: backend.csOn
            source: "images/CruiseControl.svg"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: tempomatVel
            x: 0
            y: 64
            width: 128
            height: 46
            visible: backend.csOn
            color: research.foreground
            text: backend.csSpeed.toString()
            font.pixelSize: 50
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Arial"
            font.bold: false

        }
    }
}
