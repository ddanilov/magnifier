// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

#include "MainWindow.h"
#include "MetaData.h"

#include <QApplication>

int main(int argc, char* argv[])
{
#ifdef Q_OS_ANDROID
  qputenv("QT_ANDROID_NO_EXIT_CALL", "1");
  qputenv("QT_ANDROID_DISABLE_ACCESSIBILITY", "1");
#endif

  QApplication::setOrganizationName(ORG_NAME);
  QApplication::setApplicationName(APP_NAME);

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return QApplication::exec();
}
