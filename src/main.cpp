/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

// C++ Headers

// Third Party Headers
#include <QtWidgets/QApplication>

// Our Headers
#include "window.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(application);
  // QSurfaceFormat format = QSurfaceFormat::defaultFormat();
  // format.setVersion(3, 3);
  // format.setProfile(QSurfaceFormat::CoreProfile);

  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("madoodia.com");
  QCoreApplication::setApplicationName("Abyssal");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  Window win;
  // win.setFormat(format);
  win.show();

  return app.exec();
}
