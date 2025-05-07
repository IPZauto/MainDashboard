

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
    color: "#151414"
    property int pulseDuration: 1500
    property int stopDuration: 2000
    PulsatingBox{
        anchors.fill: parent
    }
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
        strokeColor: "#e8e8e8"
        capStyle: 32
        strokeWidth: 15
        end: 150
        fillColor: "#00000000"
        SequentialAnimation on strokeColor {
            running: styl.pulseActive
            loops: Animation.Infinite
            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.stopDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: styl.textColor
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

        }
    }

    ArcItem {
        id: zegarArc2
        x: 75
        y: 75
        width: 400
        height: 400
        strokeWidth: 10
        strokeColor: "#80797979"
        fillColor: "#00000000"
        end: 150
        capStyle: 32
    }

    ArcItem {
        id: zegarArc3
        x: 95
        y: 95
        width: 360
        height: 360
        strokeWidth: 5
        strokeColor: "#40797979"
        fillColor: "#00000000"
        end: 150
        capStyle: 32
    }

    Text {
        id: licznik
        x: 205
        y: 215
        width: 140
        height: 120
        color: "#e8e8e8"
        text: (backend.engineRPM / 100).toString()
        font.pixelSize: 90
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false
        SequentialAnimation on color {
            running: styl.pulseActive
            loops: Animation.Infinite
            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.stopDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: styl.textColor
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

        }
    }

    Text {
        id: licznik1
        x: 205
        y: 280
        width: 140
        height: 120
        color: "#e8e8e8"
        text: "RPM"
        font.pixelSize: 50
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false
        SequentialAnimation on color {
            running: styl.pulseActive
            loops: Animation.Infinite
            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.stopDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: styl.textColor
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

        }
    }

    Text {
        id: licznik2
        x: 205
        y: 320
        width: 140
        height: 120
        color: "#e8e8e8"
        text: "100x"
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false
        SequentialAnimation on color {
            running: styl.pulseActive
            loops: Animation.Infinite
            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.stopDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: styl.textColor
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

        }
    }

    GroupItem {
        id: rotator
        x: 276
        y: 235
        width: 250
        height: 80
        rotation: 60 - backend.engineRPM * 15 / 1000
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
                    color: "#e8e8e8"
                }
            }
            strokeWidth: 0
            strokeColor: "#00ff0000"
            adjustBorderRadius: true
        }
    }

    Text {
        id: gear
        x: 75
        y: 241
        width: 100
        height: 80
        text: backend.gear
        color: "#e8e8e8"
        font.pixelSize: 60
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false
        SequentialAnimation on color {
            running: styl.pulseActive
            loops: Animation.Infinite
            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.stopDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: styl.textColor
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

        }
    }

    Text {
        id: gearText
        anchors.top: gear.bottom
        anchors.left: gear.left
        width: 100
        height: 50
        color: "#e8e8e8"
        text: "gear"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.bold: false
        SequentialAnimation on color {
            running: styl.pulseActive
            loops: Animation.Infinite
            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.stopDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: "#e8e8e8"
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

            ColorAnimation {
                to: styl.textColor
                duration: tlo.pulseDuration
                easing.type: Easing.InOutQuad
            }

        }
    }
}

/*##^##
Designer {
    D{i:0}D{i:5;invisible:true}D{i:6;invisible:true}D{i:7;invisible:true}
}
##^##*/

