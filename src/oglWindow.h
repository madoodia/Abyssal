// madoodia@gmail.com
// ------------------
#ifndef OGLWINDOW_H
#define OGLWINDOW_H

// C++ Headers

// Third Party Headers
#include <QtWidgets/QOpenGLWidget>
#include <QtCore/QEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/Qt>

// Our Headers

class OGLWindow : public QOpenGLWidget
{
protected:
	void initializeGL() override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	bool event(QEvent* event);

private:
	uint vao1, vao2, vbo1, vbo2, shaderProgram;
};

#endif // OGLWINDOW_H
