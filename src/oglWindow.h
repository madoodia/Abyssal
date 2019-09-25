// madoodia@gmail.com
// ------------------
#ifndef OGLWINDOW_H
#define OGLWINDOW_H

// C++ Headers

// Third Party Headers
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/QPoint>
#include <QtCore/Qt>

// Our Headers

class OGLWindow : public QOpenGLWidget
{
protected:
    void initializeGL() override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // OGLWINDOW_H
