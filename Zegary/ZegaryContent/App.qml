// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import Zegary

Window {
    width: 1920
    height: 550

    visible: true
    title: "Zegary"
    color: "#151414"

    property int speed: 145
    property int rpm: 96

    ZegarLeft {
        x: 0
        y: 0
        rotate: speed
    }
    MidScreen {
        x: 560
        y: 0
    }
    ZegarRight {
        x: 1920 - 550
        y: 0
        rotate: rpm
    }


}

