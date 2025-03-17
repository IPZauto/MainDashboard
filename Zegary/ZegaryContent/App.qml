// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import Zegary

Window {
    width: 1920
    height: 550

    visible: true
    title: "Zegary"

    property bool batteryLow: true
    color: styl.color

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

