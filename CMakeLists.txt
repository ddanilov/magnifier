# SPDX-FileCopyrightText: 2025 Denis Danilov
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.16)

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
  Main.cpp
  MainWindow.h MainWindow.cpp
)

target_link_libraries(${APP_NAME} PUBLIC
  Qt::Core
  Qt::Gui
  Qt::Multimedia
  Qt::MultimediaWidgets
  Qt::Widgets
)
