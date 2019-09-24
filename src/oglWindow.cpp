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
}

void OGLWindow::paintGL()
{
    glViewport(0, 0, width(), height());

    glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}