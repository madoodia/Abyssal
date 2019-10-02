// madoodia@gmail.com
// ------------------

#ifndef OGLWINDOW_H
#define OGLWINDOW_H


// C++ Headers
#include <stdlib.h>
#include <cmath>

// Third Party Headers
#include <GL/glew.h>

#include <QtWidgets/QOpenGLWidget>
#include <QtCore/QEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QCloseEvent>
#include <QtCore/Qt>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtCore/QObject>

// Our Headers
#include "shader.h"

class OGLWindow : public QOpenGLWidget
{
	Q_OBJECT

public:
	OGLWindow(QWidget* parent = 0);
	~OGLWindow();

protected:
	void initializeGL() override;
	void paintGL() override;

	void closeEvent(QCloseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	bool event(QEvent* event);

private:
	unsigned int vao, vbo, ebo, shaderProgram;
	Shader ourShaders;
};

#endif // OGLWINDOW_H
