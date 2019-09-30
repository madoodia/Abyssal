// madoodia@gmail.com
// ------------------
#ifndef OGLWINDOW_H
#define OGLWINDOW_H

// C++ Headers

// Third Party Headers
#include <QtWidgets/QOpenGLWidget>
#include <QtCore/QEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/Qt>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtCore/QObject>

// Our Headers

class OGLWindow : public QOpenGLWidget
{
	Q_OBJECT

public:
	OGLWindow();
	~OGLWindow();
protected:
	void initializeGL() override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	bool event(QEvent* event);

private:
	uint vao, vbo, ebo, shaderProgram;
	QTimer* timer;
	float step;
};

#endif // OGLWINDOW_H
