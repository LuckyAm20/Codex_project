cmake_minimum_required(VERSION 3.5)

project(codex VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6)
find_package(Qt6 COMPONENTS Core PrintSupport Sql Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        arhivwindow.cpp
        arhivwindow.h
        arhivwindow.ui
        articleform.cpp
        articleform.h
        articleform.ui
        dialog_dez.cpp
        dialog_dez.h
        dialog_dez.ui
        dialogarhiv.cpp
        dialogarhiv.h
        dialogarhiv.ui
        form_dez.cpp
        form_dez.h
        form_dez.ui
        form.ui
        form_vvod.cpp
        form_vvod.h
        form_vvod.ui
        logindialog.cpp
        logindialog.h
        logindialog.ui
        tableprinter.cpp
        tableprinter.h
)

add_executable(codex ${PROJECT_SOURCES})

target_link_libraries(codex PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(codex PRIVATE Qt6::PrintSupport Qt6::Sql)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/database DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Codex)
endif()
set_target_properties(codex PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS codex
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(codex)
endif()
