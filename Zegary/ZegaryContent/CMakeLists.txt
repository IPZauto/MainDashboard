qt_add_library(ZegaryContent STATIC)
qt_add_qml_module(ZegaryContent
    URI "ZegaryContent"
    VERSION 1.0
    QML_FILES
        "ZegarRight.qml"
        "ZegarLeft.qml"
        "App.qml"
        "ResearchSettingsDialog.qml"
        "MidScreen.qml"
        "PulsatingBox.qml"
        "GaugeArc.qml"
        "GradientRectangle.qml"

    RESOURCES
        "images/long.svg"
        "images/LeftSignal.svg"
        "images/CruiseControl.svg"
        "images/HandBrake.svg"
        "images/lights.svg"
        "images/batteryWarning.svg"
        "images/WheatherWarning.svg"
        "images/Fuel.svg"
)

target_link_libraries(ZegaryContent PRIVATE Qt6::Quick)
