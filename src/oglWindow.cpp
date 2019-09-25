// madoodia@gmail.com
// ------------------

// C++ Headers
#include <stdlib.h>

// Third Party Headers
#include <GL/glew.h>

// Own Headers
#include "oglWindow.h"

void OGLWindow::initializeGL()
{
    if (glewInit() != GLEW_OK)
    {
        printf("Glew is not initialized!");
        exit(-1);
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    setMouseTracking(true);
}

void OGLWindow::paintGL()
{
    glViewport(0, 0, width(), height());
    glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OGLWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
    if (event->key() == Qt::Key_W)
    {
        if (event->modifiers() == Qt::ShiftModifier)
            printf("Shift+w = W\n");
        else
            printf("w key is pressed!\n");
    }
    if (event->key() == Qt::Key_S)
    {
        if (event->modifiers() == Qt::Modifier::SHIFT)
            printf("Shift+s = S\n");
        else
            printf("s key is pressed!\n");
    }
    if (event->key() == Qt::Key_D)
    {
        printf("d key is pressed!\n");
    }
    if (event->key() == Qt::Key_A)
    {
        printf("a key is pressed!\n");
    }
    // if (event->modifiers() == Qt::Modifier::ALT)
    // {
    //     printf("alt key is pressed!\n");
    // }
}

void OGLWindow::mouseMoveEvent(QMouseEvent *event)
{
    // float x = event->x();
    // float y = event->y();
    // printf("xPos: %f , yPos: %f\n", x, y);
}

void OGLWindow::mousePressEvent(QMouseEvent *event)
{
    // if (event->button() == Qt::LeftButton)
    //     printf("Left Button Mouse is Pressed!\n");
    // if (event->button() == Qt::MidButton)
    //     printf("Mid Button Mouse is Pressed!\n");
    // if (event->button() == Qt::RightButton)
    //     printf("Right Button Mouse is Pressed!\n");
}

bool OGLWindow::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::MouseButtonPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        if (ke->modifiers() == Qt::Modifier::ALT)
        {
            if (me->button() == Qt::LeftButton)
            {
                printf("The viewport is Rotated!\n");
                return true;
            }
            if (me->button() == Qt::MidButton)
            {
                printf("The viewport is Panned!\n");
                return true;
            }
            if (me->button() == Qt::RightButton)
            {
                printf("The viewport is Zoomed!\n");
                return true;
            }
        }
    }
    // if (event->type() == QEvent::KeyRelease)
    // {
    //     printf("We are in QEvent::KeyRelease!\n");
    // }
    return QWidget::event(event);
}