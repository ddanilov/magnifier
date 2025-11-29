// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <QBoxLayout>
#include <QCamera>
#include <QTextEdit>
#include <QVideoWidget>

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

signals:
  void fontPixelSizeChanged(int pixel_size);
  void switchView();

private slots:
  void setFontPixelSize(int pixel_size);
  void switchTorch();
  void switchBetweenVideoAndInfo();

private:
  void connectCamera();
  void addButtons();
  void setInfo();

  void setZoom(float factor);

  QTextEdit* m_info_widget;
  QVideoWidget* m_video_widget;
  QCamera* m_camera;

  QBoxLayout* m_control_layout;
};
