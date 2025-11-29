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

target_link_libraries(${APP_NAME} PUBLIC
  Qt::Core
  Qt::Gui
  Qt::Multimedia
  Qt::MultimediaWidgets
  Qt::Widgets
)

find_package(Git)
if(Git_FOUND)
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE LAST_TAG)
endif()

if(ANDROID)
  if(LAST_TAG)
    execute_process(COMMAND ${GIT_EXECUTABLE} rev-list --count --first-parent ${LAST_TAG}..HEAD
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_STRIP_TRAILING_WHITESPACE
      OUTPUT_VARIABLE VERSION_COUNT)

    string(REPLACE "." ";" VERSION_LIST ${LAST_TAG})
    list(GET VERSION_LIST 0 VERSION_MAJOR)
    list(GET VERSION_LIST 1 VERSION_MINOR)

    math(EXPR VERSION_CODE "${VERSION_MAJOR} * 1000000 + ${VERSION_MINOR} * 1000 + ${VERSION_COUNT}")
  endif()

  if(NOT VERSION_CODE)
    set(VERSION_CODE "0")
  endif()

  set_property(TARGET ${APP_NAME} PROPERTY QT_ANDROID_PACKAGE_NAME ${ORG_NAME}.${APP_NAME})
  set_property(TARGET ${APP_NAME} PROPERTY QT_ANDROID_VERSION_NAME ${LAST_TAG})
  set_property(TARGET ${APP_NAME} PROPERTY QT_ANDROID_VERSION_CODE ${VERSION_CODE})
  set_property(TARGET ${APP_NAME} PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
endif()

if(NOT LAST_TAG)
  set(LAST_TAG "0.0")
endif()

configure_file(MetaData.h.in ${CMAKE_CURRENT_BINARY_DIR}/MetaData.h)
target_include_directories(${APP_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

qt_finalize_executable(${APP_NAME})
