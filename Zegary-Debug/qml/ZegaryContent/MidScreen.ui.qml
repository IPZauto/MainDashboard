

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Shapes 1.0

Rectangle {
    readonly property color background_color: "#151414"
    property bool handbrake_visibilty: true
    property bool lights_visibilty: true //normal lights
    property bool long_visibilty: true //long lights
    property bool fuel_visibilty: true
    property bool left_signal: true
    property bool right_signal: true
    property bool emergency: true
    property string messageTextSrc: "Bad wheather\n slow down"
    //property string messageTextSrc: ""
    //property string messageIconSrc: "images/WheatherWarning.svg"
    property string messageIconSrc: ""

    id: root
    color: background_color
    width: 800
    height: 550

    Image {
        id: leftSignal
        anchors.left: parent.left
        anchors.leftMargin: 72
        anchors.top: parent.top
        anchors.topMargin: 30
        width: 64
        height: 64
        source: "images/LeftSignal.svg"
        fillMode: Image.PreserveAspectFit
        opacity: 0.2
        SequentialAnimation on opacity {
            id: leftBlink
            running: (left_signal || emergency)
            loops: Animation.Infinite
            NumberAnimation {
                to: 1
                duration: 500
            }
            NumberAnimation {
                to: 0.2
                duration: 500
            }
        }
    }

    Image {
        id: rightSignal
        anchors.right: parent.right
        anchors.rightMargin: 72
        anchors.top: parent.top
        anchors.topMargin: 30
        width: 64
        height: 64
        source: "images/LeftSignal.svg"
        rotation: 180
        fillMode: Image.PreserveAspectFit
        opacity: 0.2
        SequentialAnimation on opacity {
            id: rightBlink
            running: (right_signal || emergency)
            loops: Animation.Infinite
            NumberAnimation {
                to: 1
                duration: 500
            }
            NumberAnimation {
                to: 0.2
                duration: 500
            }
        }
    }
    Image {
        id: handBrake
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: 64
        height: 64
        source: "images/HandBrake.svg"
        fillMode: Image.PreserveAspectFit
        visible: handbrake_visibilty
    }

    Image {
        id: fuel
        x: handBrake.x - fuel.width - 50
        y: 456
        width: 64
        height: 64
        source: "images/Fuel.svg"
        fillMode: Image.PreserveAspectFit
        visible: fuel_visibilty
    }

    Image {
        id: _long
        x: handBrake.x + handBrake.width + 50
        y: 456
        width: 64
        height: 64
        source: "images/long.svg"
        fillMode: Image.PreserveAspectFit
        visible: long_visibilty
    }
    Image {
        id: lights
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
        width: 64
        height: 64
        source: "images/lights.svg"
        fillMode: Image.PreserveAspectFit
        visible: lights_visibilty
    }

    Rectangle {
        id: messageScreen
        color: "#000000"
        width: 300
        height: 350
        anchors.centerIn: parent
        Column {
            anchors.centerIn: parent
            spacing: 15
            Image {
                id: messageIcon
                source: messageIconSrc // later backend contorl
                width: messageIconSrc !== "" ? 64 : 0
                height: messageIconSrc !== "" ? 64 : 0
                visible: messageIconSrc !== ""
                fillMode: Image.PreserveAspectFit
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: messageText
                text: messageTextSrc //later backend
                color: "white"
                font.pixelSize: 22
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
