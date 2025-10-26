// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#include "MainWindow.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QMediaCaptureSession>
#include <QPermissions>

MainWindow::MainWindow(QWidget* parent) :
    QWidget(parent),
    m_video_widget(new QVideoWidget),
    m_camera(new QCamera(QCameraDevice::BackFace))
{
  auto* layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(m_video_widget, 1);

  setLayout(layout);
  resize(500,500);

  connectCamera();
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
