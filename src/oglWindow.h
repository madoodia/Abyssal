// madoodia@gmail.com
// ------------------
#ifndef OGLWINDOW_H
#define OGLWINDOW_H

// C++ Headers

// Third Party Headers
#include <QtWidgets/qopenglwidget.h>

// Our Headers

class OGLWindow : public QOpenGLWidget
{
protected:
    void initializeGL() override;
    void paintGL() override;
};

#endif // OGLWINDOW_H
