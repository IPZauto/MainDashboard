import QtQuick
import QtQuick.Shapes

Shape {
    id: root
    property real begin: 0
    property real end: 90
    property alias strokeWidth: path.strokeWidth
    property alias strokeColor: path.strokeColor
    property alias fillColor: path.fillColor
    property alias capStyle: path.capStyle

    ShapePath {
        id: path
        fillColor: "transparent"
        PathAngleArc {
            centerX: root.width / 2
            centerY: root.height / 2
            radiusX: (root.width - path.strokeWidth) / 2
            radiusY: (root.height - path.strokeWidth) / 2
            startAngle: Math.min(root.begin, root.end) - 90
            sweepAngle: Math.abs(root.end - root.begin)
        }
    }
}
