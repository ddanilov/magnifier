// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <QBoxLayout>
#include <QCamera>
#include <QVideoWidget>

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);

private:
  void connectCamera();
  void addButtons();

  QVideoWidget* m_video_widget;
  QCamera* m_camera;

  QBoxLayout* m_control_layout;
};
