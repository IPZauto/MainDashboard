// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Controls
import Zegary

Window {
    id: mainWindow
    width: 1920
    height: 550

    visible: true
    title: "Zegary"


    property bool batteryLow: true
    color: "#151414"

    property string serverUrl: ""

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
        }

        onAccepted: {
            serverUrl=serverUrlInput.text;
            network.url = serverUrl;
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

    PulsatingBox{
        anchors.fill: parent
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


}

