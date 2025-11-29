// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#include "MainWindow.h"

#include "MetaData.h"

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QMediaCaptureSession>
#include <QPermissions>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) :
    QWidget(parent),
    m_info_widget(new QTextEdit),
    m_video_widget(new QVideoWidget),
    m_camera(new QCamera(QCameraDevice::BackFace)),
    m_control_layout(new QHBoxLayout)
{
  auto* layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(m_info_widget, 1);
  layout->addWidget(m_video_widget, 1);
  layout->addLayout(m_control_layout);

  m_info_widget->hide();

  setLayout(layout);

  connectCamera();
  addButtons();
  setInfo();

  connect(this, &MainWindow::fontPixelSizeChanged, this, &MainWindow::setFontPixelSize);
  connect(this, &MainWindow::switchView, this, &MainWindow::switchBetweenVideoAndInfo);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Back || event->key() == Qt::Key_Backspace)
  {
    emit switchView();
    event->ignore();
  }
  event->accept();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
  auto pixel_size = static_cast<int>(0.4 * width() / (3 + 1));
  emit fontPixelSizeChanged(pixel_size);
  QWidget::resizeEvent(event);
}

void MainWindow::setFontPixelSize(int pixel_size)
{
  auto widgets = findChildren<QWidget*>();
  if (!widgets.empty())
  {
    QFont font(widgets.front()->font());
    font.setPixelSize(pixel_size);
    for (auto* widget : std::as_const(widgets))
    {
      widget->setFont(font);
    }
  }
}

void MainWindow::switchTorch()
{
  if (m_camera->torchMode() != QCamera::TorchOff)
  {
    m_camera->setTorchMode(QCamera::TorchOff);
  }
  else
  {
    m_camera->setTorchMode(QCamera::TorchOn);
  }
}

void MainWindow::switchBetweenVideoAndInfo()
{
  if (m_video_widget->isHidden())
  {
    m_info_widget->hide();
    m_video_widget->show();
  }
  else
  {
    m_video_widget->hide();
    m_info_widget->show();
  }
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
    const auto factor = static_cast<float>(i + 2);
    auto* zoom_button = new QPushButton;
    zoom_button->setText(QString("%1X").arg(factor, 0, 'f', 0));
    connect(zoom_button, &QPushButton::pressed, this, [this, factor]() { setZoom(factor); });
    m_control_layout->addWidget(zoom_button, 1);
  }

  auto* torch_button = new QPushButton("T");
  connect(torch_button, &QPushButton::pressed, this, &MainWindow::switchTorch);
  m_control_layout->addWidget(torch_button, 1);
}

void MainWindow::setInfo()
{
  QString info;
  info.append("<small>");
  info.append(QString("App Version: %1").arg(LAST_TAG));
  info.append("<br>");
  info.append(QString("Qt Version: %1").arg(qVersion()));
  info.append("</small>");

  m_info_widget->setText(info);
  m_info_widget->setReadOnly(true);
}

void MainWindow::setZoom(const float factor)
{
  m_camera->setZoomFactor(factor);
}
