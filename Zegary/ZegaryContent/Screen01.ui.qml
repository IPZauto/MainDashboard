

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import Zegary
import QtGraphs
import QtQuick.Studio.Components

Rectangle {
    id: tlo
    width: Constants.width
    height: Constants.height
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#000000"
        }

        GradientStop {
            position: 0.5
            color: "#595959"
        }

        GradientStop {
            position: 1
            color: "#000000"
        }

        orientation: Gradient.Vertical
    }

    RectangleItem {
        id: obramowka
        x: 360
        y: 90
        width: 1200
        height: 600
        radius: 0
        topRightBevel: false
        topLeftBevel: false
        strokeWidth: 30
        strokeColor: "#797979"
        fillColor: "#000000"
        adjustBorderRadius: true

        RectangleItem {
            id: ekran
            x: 350
            y: 125
            width: 500
            height: 400
            radius: 30
            fillColor: "#1a1a1a"
            strokeColor: "#000000"
            strokeWidth: 0
            adjustBorderRadius: true
        }
    }

    TriangleItem {
        id: dolnaObramowka
        x: 360
        y: 675
        width: 1200
        height: 298
        radius: 0
        antialiasing: false
        strokeWidth: 30
        strokeColor: "#797979"
        fillColor: "#000000"
        rotation: 180
        arcRadius: 1
        layer.textureMirroring: ShaderEffectSource.MirrorVertically
        smooth: true
    }

    EllipseItem {
        id: zegar1
        x: 60
        y: 90
        width: 600
        height: 600
        property real value: 23.7
        strokeColor: "#797979"
        strokeWidth: 30
        fillColor: "#000000"

        GroupItem {
            id: tloZegara1
            x: 99
            y: 100

            EllipseItem {
                id: ellipse3
                x: 0
                y: 0
                width: 400
                height: 400
                fillColor: "#1a1a1a"
                strokeColor: "#000000"
                strokeWidth: 0
            }

            EllipseItem {
                id: ellipse4
                x: 101
                y: 100
                height: 200
                fillColor: "#333333"
                strokeColor: "#000000"
                strokeWidth: 0
            }
        }

        GroupItem {
            id: znaczniki1
            x: 44
            y: 29

            TriangleItem {
                id: triangle
                x: 241
                y: 482
                width: 30
                height: 60
                visible: false
                radius: 0
                fillColor: "#797979"
                strokeWidth: -1
            }

            TriangleItem {
                id: triangle1
                x: 241
                y: 0
                width: 30
                height: 60
                radius: 0
                rotation: 180
                strokeWidth: -1
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle2
                x: 0
                y: 241
                width: 30
                height: 60
                radius: 0
                rotation: 90
                strokeWidth: -1
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle3
                x: 482
                y: 241
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 270
                fillColor: "#797979"
            }
        }

        GroupItem {
            id: znacznikiDiag1
            x: 44
            y: 29
            rotation: -45

            TriangleItem {
                id: triangle4
                x: 241
                y: 482
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle5
                x: 241
                y: 0
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 180
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle6
                x: 0
                y: 241
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 90
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle7
                x: 482
                y: 241
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 270
                fillColor: "#797979"
            }
        }

        GroupItem {
            id: wskaznik1
            x: 0
            y: 0
            width: 600
            height: 600
            rotation: zegar1.value - 135

            EllipseItem {
                id: ellipse
                x: 270
                y: 270
                width: 60
                height: 60
                strokeColor: "#000000"
                fillColor: "#797979"
                strokeWidth: 0
            }

            TriangleItem {
                id: triangle16
                x: 270
                y: 120
                width: 60
                height: 180
                radius: 0
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#797979"
            }
        }
    }

    EllipseItem {
        id: zegar2
        x: 1260
        y: 90
        width: 600
        height: 600
        property real value: 168
        strokeColor: "#797979"
        strokeWidth: 30
        fillColor: "#000000"

        GroupItem {
            id: tloZegara2
            x: 99
            y: 100
            EllipseItem {
                id: ellipse5
                x: 0
                y: 0
                width: 400
                height: 400
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#1a1a1a"
            }

            EllipseItem {
                id: ellipse6
                x: 101
                y: 100
                height: 200
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#333333"
            }
        }

        GroupItem {
            id: znaczniki2
            x: 44
            y: 29
            TriangleItem {
                id: triangle12
                x: 241
                y: 482
                width: 30
                height: 60
                visible: false
                radius: 0
                strokeWidth: -1
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle13
                x: 241
                y: 0
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 180
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle14
                x: 0
                y: 241
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 90
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle15
                x: 482
                y: 241
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 270
                fillColor: "#797979"
            }
        }

        GroupItem {
            id: znacznikiDiag2
            x: 44
            y: 29
            rotation: -45
            TriangleItem {
                id: triangle8
                x: 241
                y: 482
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle9
                x: 241
                y: 0
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 180
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle10
                x: 0
                y: 241
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 90
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle11
                x: 482
                y: 241
                width: 30
                height: 60
                radius: 0
                strokeWidth: -1
                rotation: 270
                fillColor: "#797979"
            }
        }

        GroupItem {
            id: wskaznik2
            x: 0
            y: 0
            width: 600
            height: 600
            rotation: zegar2.value - 135
            EllipseItem {
                id: ellipse1
                x: 270
                y: 270
                width: 60
                height: 60
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle17
                x: 270
                y: 120
                width: 60
                height: 180
                radius: 0
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#797979"
            }
        }
    }

    states: [
        State {
            name: "clicked"
        }
    ]

    EllipseItem {
        id: paliwo
        x: 810
        y: 660
        width: 300
        height: 300
        property real value: 0
        transformOrigin: Item.Center
        strokeWidth: 30
        strokeColor: "#797979"
        fillColor: "#000000"

        GroupItem {
            id: tloZegara3
            x: 25
            y: 25

            EllipseItem {
                id: ellipse7
                x: 35
                y: 35
                width: 180
                height: 180
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#1a1a1a"
            }

            EllipseItem {
                id: ellipse8
                x: 75
                y: 75
                width: 100
                height: 100
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#333333"
            }
        }

        GroupItem {
            id: wskaznik3
            x: -50
            y: -50
            width: 400
            height: 400
            rotation: paliwo.value - 135
            EllipseItem {
                id: ellipse2
                x: 185
                y: 185
                width: 30
                height: 30
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle18
                x: 185
                y: 110
                width: 30
                height: 90
                radius: 0
                strokeWidth: 0
                strokeColor: "#000000"
                fillColor: "#797979"
            }
        }

        GroupItem {
            id: znaczniki3
            x: 24
            y: 14

            TriangleItem {
                id: triangle20
                x: 115
                y: 232
                width: 20
                height: 40
                visible: false
                radius: 0
                strokeWidth: -1
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle21
                x: 115
                y: 0
                width: 20
                height: 40
                radius: 0
                strokeWidth: -1
                rotation: 180
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle22
                x: 0
                y: 116
                width: 20
                height: 40
                radius: 0
                strokeWidth: -1
                rotation: 90
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle23
                x: 232
                y: 116
                width: 20
                height: 40
                radius: 0
                strokeWidth: -1
                rotation: 270
                fillColor: "#797979"
            }
        }

        GroupItem {
            id: znacznikiDiag3
            x: 24
            y: 14
            rotation: -45
            TriangleItem {
                id: triangle24
                x: 115
                y: 232
                width: 20
                height: 40
                visible: true
                radius: 0
                strokeWidth: -1
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle25
                x: 115
                y: 0
                width: 20
                height: 40
                radius: 0
                strokeWidth: -1
                rotation: 180
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle26
                x: 0
                y: 116
                width: 20
                height: 40
                radius: 0
                strokeWidth: -1
                rotation: 90
                fillColor: "#797979"
            }

            TriangleItem {
                id: triangle27
                x: 232
                y: 116
                width: 20
                height: 40
                radius: 0
                strokeWidth: -1
                rotation: 270
                fillColor: "#797979"
            }
        }
    }
}
