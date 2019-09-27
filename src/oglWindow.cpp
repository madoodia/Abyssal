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
	if(glewInit() != GLEW_OK)
	{
		printf("Glew is not initialized!");
		close();
	}

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	setMouseTracking(true);

	// Vertex Shader
	const char* vertexShaderSource =
		"#version 330 core\n"
		"\n"
		"in layout (location = 0) vec3 aPos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0f);\n"
		"}\n";

	// Fragment Shader
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	uint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		printf("ERROR::SHADER:VERTEX::COMPILATION_FAILED\n", infoLog);
	}

	uint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		printf("ERROR::SHADER:FRAGMENT::COMPILATION_FAILED\n", infoLog);
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if(!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		printf("ERROR::PROGRAM::LINK_FAILED", infoLog);
	}

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);

	if(!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		printf("ERROR::PROGRAM::VALIDATE_FAILED", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertex Data
	float vertices[] =
	{
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] =   // note that we start from 0!
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; 
	// keep the EBO bound.
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OGLWindow::paintGL()
{
	glViewport(0, 0, width(), height());
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	// glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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