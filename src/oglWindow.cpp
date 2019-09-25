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
        printf("W key is pressed!\n");
    }
    if (event->key() == Qt::Key_S)
    {
        printf("S key is pressed!\n");
    }
    if (event->key() == Qt::Key_D)
    {
        printf("D key is pressed!\n");
    }
    if (event->key() == Qt::Key_A)
    {
        printf("A key is pressed!\n");
    }
}

void OGLWindow::mouseMoveEvent(QMouseEvent *event)
{
    float x = event->x();
    float y = event->y();
    printf("xPos: %f , yPos: %f\n", x, y);
}
