import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property real minOpacity: 0
    property real maxOpacity: 0.5
    property int pulseDuration: 1500
    property int stopDuration: 2000
    color: styl.color
    opacity: minOpacity

    // Opacity animation
    SequentialAnimation on opacity {
        id: leftBlink
        running: styl.pulseActive
        loops: Animation.Infinite
        NumberAnimation{
            to: root.minOpacity
            duration: root.stopDuration
        }
        NumberAnimation {
            to: root.minOpacity
            duration: root.pulseDuration
        }
        NumberAnimation {
            to: root.maxOpacity
            duration: root.pulseDuration
        }
    }

    // Start/stop control
    function startPulse() { isPulsing = true; }
    function stopPulse() { isPulsing = false; opacity = minOpacity; }
}
