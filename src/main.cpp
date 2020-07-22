/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

// C++ Headers

// Third Party Headers
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>

// Our Headers
#include "window.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(application);

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

  QApplication app(argc, argv);

  // Apply custom stylesheet to the application
  QFile style(":/style.css");
  if (style.open(QFile::ReadOnly))
  {
    QTextStream stylesheet(&style);
    app.setStyleSheet(stylesheet.readAll());
  }

  QCoreApplication::setOrganizationName("madoodia.com");
  QCoreApplication::setApplicationName("Abyssal");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  Window win;
  win.show();

  return app.exec();
}
