// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#include "MainWindow.h"

#include <QApplication>
#include <QMediaCaptureSession>
#include <QPermissions>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) :
    QWidget(parent),
    m_video_widget(new QVideoWidget),
    m_camera(new QCamera(QCameraDevice::BackFace)),
    m_control_layout(new QHBoxLayout)
{
  auto* layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(m_video_widget, 1);
  layout->addLayout(m_control_layout);

  setLayout(layout);

  connectCamera();
  addButtons();
}

void MainWindow::connectCamera()
{
#if QT_CONFIG(permissions)
  QCameraPermission cameraPermission;
  switch (qApp->checkPermission(cameraPermission))
  {
    case Qt::PermissionStatus::Undetermined:
      qApp->requestPermission(QCameraPermission{}, this, &MainWindow::connectCamera);
      return;
    case Qt::PermissionStatus::Denied:
      return;
    case Qt::PermissionStatus::Granted:
      break;
  }
#endif

  auto* media_capture_session = new QMediaCaptureSession;
  media_capture_session->setCamera(m_camera);
  media_capture_session->setVideoOutput(m_video_widget);
  m_camera->start();
}

void MainWindow::addButtons()
{
  m_control_layout->setContentsMargins(0, 0, 0, 0);

  constexpr int num_buttons = 3;
  for (int i = 0; i < num_buttons; ++i)
  {
    auto* zoom_button = new QPushButton("X");
    m_control_layout->addWidget(zoom_button, 1);
  }

  auto* torch_button = new QPushButton("T");
  m_control_layout->addWidget(torch_button, 1);
}
