// madoodia@gmail.com
// ------------------

// C++ Headers

// Own Headers
#include "oglWindow.h"

OGLWindow::OGLWindow(QWidget* parent)
{}

OGLWindow::~OGLWindow()
{}

void OGLWindow::initializeGL()
{
	printf("initializeGL\n");

	if(glewInit() != GLEW_OK)
	{
		printf("Glew is not initialized!");
		close();
	}

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	printf("OpenGL Max Vertex Attribs: %d\n", nrAttributes);

	/*
	Vectors:
	vecn: the default vector of n floats.
	bvecn: a vector of n booleans.
	ivecn: a vector of n integers.
	uvecn: a vector of n unsigned integers.
	dvecn: a vector of n double components.
	*/

	setMouseTracking(true);

	ourShaders.initializeShader("shaders/shader.vs", "shaders/shader.fs");
	ourShaders.compileShader();

	glViewport(0, 0, width(), height());
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Vertex Data
	float vertices[] =
	{
		// positions        // colors
		0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f    // top 
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OGLWindow::paintGL()
{
	ourShaders.useShader();

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OGLWindow::closeEvent(QCloseEvent* event)
{
	printf("The widget is closing...\n");
	return QWidget::closeEvent(event);
}

void OGLWindow::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Escape)
	{
		close();
	}
	if(event->key() == Qt::Key_W)
	{
		if(event->modifiers() == Qt::ShiftModifier)
			printf("Shift+w = W\n");
		else
			printf("w key is pressed!\n");
		update();
	}
	if(event->key() == Qt::Key_S)
	{
		if(event->modifiers() == Qt::Modifier::SHIFT)
			printf("Shift+s = S\n");
		else
			printf("s key is pressed!\n");
	}
	if(event->key() == Qt::Key_D)
	{
		printf("d key is pressed!\n");
	}
	if(event->key() == Qt::Key_A)
	{
		printf("a key is pressed!\n");
	}
	if(event->key() == Qt::Key_Space)
	{
	}
	// if (event->modifiers() == Qt::Modifier::ALT)
	// {
	//     printf("alt key is pressed!\n");
	// }
}

void OGLWindow::mouseMoveEvent(QMouseEvent* event)
{
	// float x = event->x();
	// float y = event->y();
	// printf("xPos: %f , yPos: %f\n", x, y);
}

void OGLWindow::mousePressEvent(QMouseEvent* event)
{
	// if (event->button() == Qt::LeftButton)
	//     printf("Left Button Mouse is Pressed!\n");
	// if (event->button() == Qt::MidButton)
	//     printf("Mid Button Mouse is Pressed!\n");
	// if (event->button() == Qt::RightButton)
	//     printf("Right Button Mouse is Pressed!\n");
}

bool OGLWindow::event(QEvent* event)
{
	QKeyEvent* ke = static_cast<QKeyEvent*>(event);
	QMouseEvent* me = static_cast<QMouseEvent*>(event);

	if(ke->type() == QKeyEvent::KeyPress || me->type() == QMouseEvent::MouseButtonPress)
	{
		if(ke->modifiers() == Qt::Modifier::ALT)
		{
			if(me->button() == Qt::LeftButton)
			{
				printf("The viewport is Rotated!\n");
				return true;
			}
			if(me->button() == Qt::MidButton)
			{
				printf("The viewport is Panned!\n");
				return true;
			}
			if(me->button() == Qt::RightButton)
			{
				printf("The viewport is Zoomed!\n");
				return true;
			}
		}
		else if(ke->modifiers() != Qt::Modifier::ALT)
		{
			if(me->button() == Qt::LeftButton)
			{
				printf("Only Left is Pressed!\n");
				return true;
			}
			if(me->button() == Qt::MidButton)
			{
				printf("Only Mid is Pressed!\n");
				return true;
			}
			if(me->button() == Qt::RightButton)
			{
				printf("Only Right is Pressed!\n");
				return true;
			}
		}
	}

	if(event->type() == QEvent::KeyRelease)
	{
		printf("We are in QEvent::KeyRelease!\n");
	}

	return QWidget::event(event);
}