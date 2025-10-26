// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#include "MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return QApplication::exec();
}
