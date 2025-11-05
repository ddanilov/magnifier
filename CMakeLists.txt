# SPDX-FileCopyrightText: 2025 Denis Danilov
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.16)

set(ORG_NAME "org.codeberg.danilov")
set(APP_NAME "magnifier")

project(${APP_NAME} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS
  Core
  Gui
  Multimedia
  MultimediaWidgets
  Widgets
)
message(STATUS "Using Qt ${Qt6_VERSION} from ${Qt6_DIR}")

qt_standard_project_setup()

qt_add_executable(${APP_NAME}
  MANUAL_FINALIZATION
  Main.cpp
  MainWindow.h MainWindow.cpp
  MetaData.h
)

configure_file(MetaData.h.in ${CMAKE_CURRENT_BINARY_DIR}/MetaData.h)
target_include_directories(${APP_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${APP_NAME} PUBLIC
  Qt::Core
  Qt::Gui
  Qt::Multimedia
  Qt::MultimediaWidgets
  Qt::Widgets
)

set_property(TARGET ${APP_NAME} PROPERTY QT_ANDROID_PACKAGE_NAME ${ORG_NAME}.${APP_NAME})
set_property(TARGET ${APP_NAME} PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

qt_finalize_executable(${APP_NAME})
