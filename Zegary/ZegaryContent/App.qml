// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Controls.Basic

Window {
    id: mainWindow
    width: 1920
    height: 550

    visible: true
    title: "Zegary"

    property bool batteryLow: true
    color: "#151414"

    property string serverUrl: ""
    property string webSocketUrl: ""

    Dialog {
        id: serverIdPopUp
        title: "Wprowadź URL serwera z aplikacji ETS2 telemetry server"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        Column{
            spacing: 10
            Text {
                text: "URL serwera telemetrycznego"
            }

            TextField {
                id: serverUrlInput
                width: parent.width-20
                placeholderText: "e.g., http://127.0.0.1:25555"
            }

            Text {
                text: "addres websocket"
            }
            TextField {
                id: webSocketUrlInput
                text: research.settings.websocketUrl
                width: parent.width-20
                placeholderText: "e.g., ws://127.0.0.1:8080"
            }
        }

        onAccepted: {
            serverUrl=serverUrlInput.text;
            network.url = serverUrl;
            webSocketUrl = webSocketUrlInput.text;
            if (!research.setWebsocketUrl(webSocketUrl)) return;
            mainWindow.visibility = Window.FullScreen
            mainWindow.flags = Qt.Window | Qt.FramelessWindowHint // Remove frame
        }

        onRejected: {
            console.log("Server Url input cancelled");
        }
    }

    Component.onCompleted:{
        serverIdPopUp.open();
    }

    ZegarLeft {
        x: 0
        y: 0
    }
    MidScreen {
        x: 560
        y: 0
    }
    ZegarRight {
        x: 1920 - 550
        y: 0
    }

    ToolButton {
        id: settingsButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 12
        text: qsTr("Settings")
        Accessible.name: qsTr("Research settings")
        visible: research.debug
        enabled: research.debug
        contentItem: Text {
            text: settingsButton.text
            color: "#d0d0d0"
            font: settingsButton.font
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: settingsButton.hovered || settingsButton.activeFocus ? "#353535" : "#222222"
            border.color: settingsButton.activeFocus ? "#d0d0d0" : "#555555"
            radius: 4
        }
        ToolTip.visible: hovered
        ToolTip.text: qsTr("Research settings (Ctrl+,)")
        onClicked: settingsLoader.active = true
    }
    Shortcut {
        sequence: "Ctrl+,"
        enabled: research.debug
        onActivated: settingsLoader.active = true
    }
    Loader {
        id: settingsLoader
        active: false
        sourceComponent: ResearchSettingsDialog {
            onClosed: settingsLoader.active = false
            Component.onCompleted: open()
        }
    }
}
