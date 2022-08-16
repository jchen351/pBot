cmake_minimum_required(VERSION 3.5)
project(pBotGUI)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(../include)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH)


set(GUI_SOURCES
        gui.cpp
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        )

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pBotGUI
            MANUAL_FINALIZATION
            ${GUI_SOURCES}
            )
else ()
    add_executable(pBotGUI
            ${GUI_SOURCES}
            )
endif ()

target_link_libraries(pBotGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets pBot)


if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pBotGUI)
endif ()