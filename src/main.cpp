// madoodia@gmail.com
// ------------------

// C++ Headers

// Third Party Headers
#include <QtWidgets/qapplication.h>

// Our Headers
#include "oglWindow.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    QApplication app(argc, argv);

    OGLWindow win;
    win.setFormat(format);
    win.show();

    return app.exec();
}