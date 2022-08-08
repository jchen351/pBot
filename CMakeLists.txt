cmake_minimum_required(VERSION 3.5)

project(pBot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(GUI_SOURCES
        apps/gui.cpp
        gui/mainwindow.h
        gui/mainwindow.cpp
        gui/mainwindow.ui
)
include_directories(gui include)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pBot
        MANUAL_FINALIZATION
        ${GUI_SOURCES}
    )
else()
    add_executable(pBot
        ${GUI_SOURCES}
    )
endif()

target_link_libraries(pBot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(pBot PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS pBot
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pBot)
endif()
