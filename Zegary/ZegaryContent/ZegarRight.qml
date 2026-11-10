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
        strokeColor: research.foreground
        capStyle: ShapePath.RoundCap
        strokeWidth: 15
        end: 150
        fillColor: "#00000000"

    }

    GaugeArc {
        id: zegarArc2
        x: 75
        y: 75
        width: 400
        height: 400
        strokeWidth: 10
        strokeColor: "#80797979"
        fillColor: "#00000000"
        end: 150
        capStyle: ShapePath.RoundCap
    }

    GaugeArc {
        id: zegarArc3
        x: 95
        y: 95
        width: 360
        height: 360
        strokeWidth: 5
        strokeColor: "#40797979"
        fillColor: "#00000000"
        end: 150
        capStyle: ShapePath.RoundCap
    }

    Text {
        id: licznik
        x: 205
        y: 215
        width: 140
        height: 120
        color: research.foreground
        text: (backend.engineRPM / 100).toString()
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
        text: "RPM"
        font.pixelSize: 50
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false

    }

    Text {
        id: licznik2
        x: 205
        y: 320
        width: 140
        height: 120
        color: research.foreground
        text: "100x"
        font.pixelSize: 20
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
        rotation: 60 - backend.engineRPM * 15 / 1000
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

    Text {
        id: gear
        x: 75
        y: 241
        width: 100
        height: 80
        text: backend.gear
        color: research.foreground
        font.pixelSize: 60
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false

    }

    Text {
        id: gearText
        anchors.top: gear.bottom
        anchors.left: gear.left
        width: 100
        height: 50
        color: research.foreground
        text: "gear"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false

    }
}
