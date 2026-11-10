import QtQuick
import QtQuick.Shapes

Shape {
    id: root
    property alias gradient: path.fillGradient

    ShapePath {
        id: path
        strokeWidth: -1
        PathLine { x: root.width; y: 0 }
        PathLine { x: root.width; y: root.height }
        PathLine { x: 0; y: root.height }
        PathLine { x: 0; y: 0 }
    }
}
