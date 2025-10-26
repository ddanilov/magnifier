// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <QCamera>
#include <QVideoWidget>

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);

private:
  void connectCamera();

  QVideoWidget* m_video_widget;
  QCamera* m_camera;
};
