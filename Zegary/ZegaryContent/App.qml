// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Controls
import Zegary

Window {
    width: 1920
    height: 550

    visible: true
    title: "Zegary"

    property bool batteryLow: true
    //color: styl.color

    property bool pulsating: false
    property int pulseDuration: 250

    Binding on color {
        when: !pulsating
        value: "#797979"
    }
    SequentialAnimation on color {
        id: pulseBackground
        running: pulsating
        loops: Animation.Infinite
        NumberAnimation {
            to: "#550088"
            duration: pulseDuration
        }
        NumberAnimation {
            to: "#797979"
            duration: pulseDuration
        }
    }

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


}

