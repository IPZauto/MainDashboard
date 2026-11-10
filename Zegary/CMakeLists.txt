cmake_minimum_required(VERSION 3.21.1)
project(ZegaryApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml")
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 WebSockets)
qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(ZegaryApp
    App/main.cpp
    networkdata.h networkdata.cpp
    game.h game.cpp
    style.h style.cpp
    researchsettings.h researchsettings.cpp
    messagewindow.h messagewindow.cpp
    platformserver.h platformserver.cpp
)
target_include_directories(ZegaryApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(ZegaryApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::WebSockets
)
qt_add_resources(ZegaryApp "configuration"
    PREFIX "/"
    FILES qtquickcontrols2.conf config/config.json
)
add_subdirectory(ZegaryContent)
target_link_libraries(ZegaryApp PRIVATE ZegaryContentplugin)

install(TARGETS ZegaryApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

option(ZEGARY_DEPLOY "Install Qt runtime and QML dependencies for distribution" OFF)
if(ZEGARY_DEPLOY)
    qt_generate_deploy_qml_app_script(
        TARGET ZegaryApp
        OUTPUT_SCRIPT deploy_script
    )
    install(SCRIPT ${deploy_script})
endif()
