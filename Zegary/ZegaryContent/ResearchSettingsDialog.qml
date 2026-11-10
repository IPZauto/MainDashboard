import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: dialog
    title: qsTr("Research settings")
    modal: true
    parent: Overlay.overlay
    width: Math.min(720, parent.width - 32)
    height: Math.min(510, parent.height - 24)
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    property var draft: JSON.parse(JSON.stringify(research.settings))
    property string status: ""
    function submit(persist) {
        try { draft.demoSteps = JSON.parse(steps.text) }
        catch (error) { status = qsTr("Demo steps must be a valid JSON array."); return }
        const ok = persist ? research.save(draft) : research.apply(draft)
        status = ok ? (persist ? qsTr("Saved and applied.") : qsTr("Applied. Not saved yet.")) : research.error
    }
    contentItem: ScrollView {
        clip: true
        contentWidth: availableWidth
        ColumnLayout {
            width: parent.width
            spacing: 8
            Label {
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                text: research.remote ? qsTr("WebSocket controls colors until its URL is cleared.") : qsTr("Both side panels share colors. The center stays unchanged.")
            }
            RowLayout {
                Label { text: qsTr("Local mode") }
                ComboBox {
                    model: ["manual", "demo"]
                    currentIndex: dialog.draft.mode === "demo" ? 1 : 0
                    onActivated: dialog.draft.mode = currentText
                }
                Label { text: qsTr("Effect") }
                ComboBox {
                    model: ["steady", "fade", "flash"]
                    currentIndex: model.indexOf(dialog.draft.flash)
                    onActivated: dialog.draft.flash = currentText
                }
            }
            Repeater {
                model: [
                    {key: "background", label: qsTr("Target background"), numeric: false},
                    {key: "foreground", label: qsTr("Target text and gauges"), numeric: false},
                    {key: "baseBackground", label: qsTr("Pause background"), numeric: false},
                    {key: "baseForeground", label: qsTr("Pause text and gauges"), numeric: false},
                    {key: "fadeInMs", label: qsTr("Fade in (ms)"), numeric: true},
                    {key: "holdMs", label: qsTr("Hold / flash on (ms)"), numeric: true},
                    {key: "fadeOutMs", label: qsTr("Fade out (ms)"), numeric: true},
                    {key: "pauseMs", label: qsTr("Pause / flash off (ms)"), numeric: true},
                    {key: "websocketUrl", label: qsTr("WebSocket URL (optional)"), numeric: false}
                ]
                RowLayout {
                    id: fieldRow
                    required property var modelData
                    Layout.fillWidth: true
                    Label { text: fieldRow.modelData.label; Layout.preferredWidth: 220 }
                    TextField {
                        Layout.fillWidth: true
                        text: dialog.draft[fieldRow.modelData.key]
                        onTextEdited: dialog.draft[fieldRow.modelData.key] = fieldRow.modelData.numeric ? Number(text) : text.trim()
                    }
                }
            }
            CheckBox {
                text: qsTr("Release flag")
                checked: dialog.draft.release
                onToggled: dialog.draft.release = checked
            }
            CheckBox {
                text: qsTr("Repeat demo")
                checked: dialog.draft.demoLoop
                onToggled: dialog.draft.demoLoop = checked
            }
            Label { text: qsTr("Demo steps: background, foreground, durationMs") }
            TextArea {
                id: steps
                Layout.fillWidth: true
                Layout.preferredHeight: 160
                text: JSON.stringify(dialog.draft.demoSteps, null, 2)
                font.family: "monospace"
                wrapMode: TextEdit.Wrap
            }
        }
    }
    footer: ColumnLayout {
        Label {
            Layout.fillWidth: true
            Layout.leftMargin: 12
            Layout.rightMargin: 12
            text: dialog.status
            wrapMode: Text.WordWrap
        }
        DialogButtonBox {
            Layout.fillWidth: true
            Button { text: qsTr("Apply"); onClicked: dialog.submit(false) }
            Button { text: qsTr("Save"); onClicked: dialog.submit(true) }
            Button { text: qsTr("Close"); onClicked: dialog.close() }
        }
    }
}
