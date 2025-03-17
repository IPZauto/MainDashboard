

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
    property string messageTextSrc: "Bad wheather\n slow down"
    //property string messageTextSrc: ""
    //property string messageIconSrc: "images/WheatherWarning.svg"
    property string messageIconSrc: ""
    property int m_duration: 250
    id: root
    color: styl.color
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
        Binding on opacity {
            when: !backend.blinkerLeftActive
            value: 0.2
        }
        SequentialAnimation on opacity {
            id: leftBlink
            running: backend.blinkerLeftActive
            loops: Animation.Infinite
            NumberAnimation {
                to: 1
                duration: root.m_duration
            }
            NumberAnimation {
                to: 0.2
                duration: root.m_duration
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
        Binding on opacity {
            when: !backend.blinkerRightActive
            value: 0.2
        }
        SequentialAnimation on opacity {
            id: rightBlink
            running: backend.blinkerRightActive
            loops: Animation.Infinite
            NumberAnimation {
                to: 1
                duration: root.m_duration
            }
            NumberAnimation {
                to: 0.2
                duration: root.m_duration
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
        visible: backend.parkBrakeOn;
    }

    Image {
        id: fuel
        x: handBrake.x - handBrake.width - 50
        y: 456
        width: 64
        height: 64
        source: "images/Fuel.svg"
        fillMode: Image.PreserveAspectFit
        visible: backend.fuelWarningOn;
    }

    Image {
        id: _long
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 32 + 25
        anchors.top: parent.top
        anchors.topMargin: 30
        width: 64
        height: 64
        source: "images/long.svg"
        fillMode: Image.PreserveAspectFit
        visible: backend.highBeamOn
    }
    Image {
        id: lights
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -32 - 25
        anchors.top: parent.top
        anchors.topMargin: 30
        width: 64
        height: 64
        source: "images/lights.svg"
        fillMode: Image.PreserveAspectFit
        visible: backend.lightsOn
    }

    Rectangle {
        id: messageScreen
        color: "#000000"
        width: 600
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

    Image {
        id: lowBatteryWarning
        x: handBrake.x + handBrake.width + 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        width: 64
        height: 64
        visible: battteryWarning
        source: "images/batteryWarning.svg"
        fillMode: Image.PreserveAspectFit
    }
}
