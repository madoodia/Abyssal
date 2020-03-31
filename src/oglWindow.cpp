/* --------------------- */
/* (C) 2020 madoodia.com */
/* --------------------- */

// C++ Headers

// Own Headers
#include "oglWindow.h"

OGLWindow::OGLWindow(QWidget *parent)
    : mixValue(0.2f), xRot(0.0f), yRot(1.0f),
      zRot(0.0f), xvRot(0.0f), yvRot(1.0f),
      zvRot(0.0f), xPan(0.0f), yPan(0.0f),
      zPan(-1.0f), fov(45.0f), cameraSpeed(0.05f),
      deltaTime(0.1f), lastFrame(0.0f), xPos(0.0f),
      yPos(0.0f), lastX(0.0f), lastY(0.0f),
      xOffset(0.0f), yOffset(0.0f), sensitivity(0.05f),
      yaw(-90.0f), pitch(0.0f), firstMouse(true),
      interval(1.0f), nbFrames(100.0f)
{
  setMouseTracking(true);
  t0 = QTime::currentTime();
}

OGLWindow::~OGLWindow()
{
}

void OGLWindow::initializeGL()
{
  printf("initializeGL\n");

  if (glewInit() != GLEW_OK)
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

  glViewport(0, 0, width(), height());

  ourShaders.addShaders("shaders/shader.vs", "shaders/shader.fs");

  // Vertex Data
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // load and create textures
  int w, h, nrChannels;

  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("textures/container.jpg", &w, &h, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    printf("Failed to load texture!\n");
  }
  stbi_image_free(data);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //stbi_set_flip_vertically_on_load(true);
  data = stbi_load("textures/awesomeface.png", &w, &h, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    printf("Failed to load texture!\n");
  }
  stbi_image_free(data);

  ourShaders.use();

  glUniform1i(glGetUniformLocation(ourShaders.getID(), "texture1"), 0);
  glUniform1i(glGetUniformLocation(ourShaders.getID(), "texture2"), 1);
  glUniform1f(glGetUniformLocation(ourShaders.getID(), "mixValue"), mixValue);

  // Camera
  cameraPos = glm::vec3(0.0f, 0.0f, 7.0f);
  cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  cameraDirection = glm::normalize(cameraPos - cameraFront);
  glm::vec3 tempUp(0.0f, 1.0f, 0.0f);
  cameraRight = glm::normalize(glm::cross(cameraDirection, tempUp));
  cameraUp = glm::cross(cameraDirection, cameraRight);
}

void OGLWindow::paintGL()
{
  printf("paintGL...\n");

  t1 = QTime::currentTime();
  float theoric = 0.001 * interval * nbFrames;
  float measured = 0.001 * t0.msecsTo(t1);
  float diff = (measured - theoric);
  deltaTime = diff / measured;

  //printf("CurrentTime: %f\n", currentFrame);
  //deltaTime = currentFrame - lastFrame;
  //lastFrame = currentFrame;

  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  ourShaders.use();
  glUniform1f(glGetUniformLocation(ourShaders.getID(), "mixValue"), mixValue);

  glm::mat4 view(1.0f);
  glm::mat4 projection(1.0f);

  //glm::vec3 front;
  //front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  //front.y = sin(glm::radians(pitch));
  //front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  //cameraFront = glm::normalize(front);

  view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  view = glm::translate(view, glm::vec3(xPan, yPan, 0.0f));
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, zPan));
  view = glm::rotate(view, glm::radians(xvRot), glm::vec3(1.0f, 0.0f, 0.0f));
  view = glm::rotate(view, glm::radians(yvRot), glm::vec3(0.0f, 1.0f, 0.0f));

  projection = glm::perspective(glm::radians(fov), (float)width() / (float)height(), 0.1f, 100.0f);

  modelLocation = glGetUniformLocation(ourShaders.getID(), "model");
  viewLocation = glGetUniformLocation(ourShaders.getID(), "view");
  projectionLocation = glGetUniformLocation(ourShaders.getID(), "projection");

  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

  glm::vec3 cubePositions[10] =
      {
          glm::vec3(0.0f, 0.0f, 0.0f)};

  for (unsigned int i = 0; i < 10; i++)
  {
    cubePositions[i] = glm::vec3(1.0f * i, 0.0f, 0.0f);
  }

  glBindVertexArray(vao);

  for (unsigned int i = 1; i <= 10; i++)
  {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i - 1]);
    model = glm::rotate(model, glm::radians(xRot * i), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(yRot * i), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(zRot * i), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  // Render Text
  QPainter painter(this);
  painter.beginNativePainting();
  painter.setPen(Qt::white);
  painter.setFont(QFont("Calibri", 12));
  painter.drawText(5, 5, width(), height(), Qt::AlignLeft, "OpenGL Version:");
  painter.drawText(5, 20, width(), height(), Qt::AlignLeft, "FPS:");
  painter.drawText(5, 35, width(), height(), Qt::AlignLeft, "x: y: ");
  painter.end();
}

void OGLWindow::resizeGL(int w, int h)
{
  printf("resizeGL...\n");
  glViewport(0, 0, w, h);
  // update();
}

void OGLWindow::closeEvent(QCloseEvent *event)
{
  printf("The widget is closing...\n");
  return QWidget::closeEvent(event);
}

void OGLWindow::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
  }
  // xPan Camera
  if (event->key() == Qt::Key_Left)
  {
    //xPan += 0.1f;
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    update();
  }
  if (event->key() == Qt::Key_Right)
  {
    //xPan -= 0.1f;
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    update();
  }
  // yPan Camera
  if (event->key() == Qt::Key_Up)
  {
    //yPan -= 0.1f;
    cameraPos += cameraFront * cameraSpeed;
    update();
  }
  if (event->key() == Qt::Key_Down)
  {
    //yPan += 0.1f;
    cameraPos -= cameraFront * cameraSpeed;
    update();
  }
  // zPan Camera
  if (event->key() == Qt::Key_Period)
  {
    zPan += 0.1f;
    update();
  }
  if (event->key() == Qt::Key_Comma)
  {
    zPan -= 0.1f;
    update();
  }
  if (event->key() == Qt::Key_F)
  {
    fov += 1.0f;
    update();
  }
  if (event->key() == Qt::Key_O)
  {
    fov -= 1.0f;
    update();
  }
  if (event->key() == Qt::Key_Plus)
  {
    if (mixValue >= 1.0)
      mixValue = 1.0;
    else
      mixValue += 0.01;
    printf("mixValue: %f\n", mixValue);
    update();
  }
  if (event->key() == Qt::Key_Minus)
  {
    if (mixValue <= 0.0)
      mixValue = 0.0;
    else
      mixValue -= 0.01;
    printf("mixValue: %f\n", mixValue);
    update();
  }
  // Model rotation
  if (event->key() == Qt::Key_X)
  {
    xRot += 1.0f;
    update();
  }
  if (event->key() == Qt::Key_Y)
  {
    yRot += 1.0f;
    update();
  }
  if (event->key() == Qt::Key_Z)
  {
    zRot += 1.0f;
    update();
  }
  // View rotation
  if (event->key() == Qt::Key_1)
  {
    xvRot += 1.0f;
    update();
  }
  if (event->key() == Qt::Key_2)
  {
    yvRot += 1.0f;
    update();
  }
  if (event->key() == Qt::Key_3)
  {
    zvRot += 1.0f;
    update();
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
  if (event->key() == Qt::Key_Space)
  {
  }
  // if (event->modifiers() == Qt::Modifier::ALT)
  // {
  //     printf("alt key is pressed!\n");
  // }
  return QWidget::keyPressEvent(event);
}

void OGLWindow::mousePressEvent(QMouseEvent *event)
{
  QEvent *e = static_cast<QEvent *>(event);
  QKeyEvent *ke = static_cast<QKeyEvent *>(e);

  if (ke->modifiers() == Qt::Modifier::ALT)
  {
    if (event->buttons())
    {
      mousePos = QVector2D(event->localPos());
    }
  }
}

void OGLWindow::mouseMoveEvent(QMouseEvent *event)
{
  QEvent *e = static_cast<QEvent *>(event);
  QKeyEvent *ke = static_cast<QKeyEvent *>(e);

  QVector2D diff = QVector2D(event->localPos()) - mousePos;
  if (ke->modifiers() == Qt::Modifier::ALT)
  {
    if (event->buttons() & Qt::LeftButton)
    {
      xPos = diff.x();
      yPos = diff.y();

      xOffset = xPos - lastX;
      yOffset = yPos - lastY;

      xvRot -= yOffset;
      yvRot -= xOffset;

      mousePos = QVector2D(event->pos());
      xPos = mousePos.x();
      yPos = mousePos.y();

      update();
    }
    if (event->buttons() & Qt::MidButton)
    {
      xPos = diff.x();
      yPos = diff.y();

      xOffset = xPos - lastX;
      yOffset = yPos - lastY;
      xOffset *= sensitivity;
      yOffset *= sensitivity;
      xPan -= xOffset;
      yPan += yOffset;

      mousePos = QVector2D(event->pos());
      xPos = mousePos.x();
      yPos = mousePos.y();
      update();
    }
    if (event->buttons() & Qt::RightButton)
    {
      xPos = diff.x();
      yPos = diff.y();

      xOffset = xPos - lastX;
      xOffset *= sensitivity;
      zPan += xOffset;

      mousePos = QVector2D(event->pos());
      xPos = mousePos.x();
      update();
    }
  }
}

void OGLWindow::mouseReleaseEvent(QMouseEvent *event)
{
}

bool OGLWindow::event(QEvent *event)
{
  QKeyEvent *ke = static_cast<QKeyEvent *>(event);
  QMouseEvent *me = static_cast<QMouseEvent *>(event);

  //if(ke->type() == QKeyEvent::KeyPress || me->type() == QMouseEvent::MouseButtonPress || me->type() == QMouseEvent::MouseMove)
  //{
  //	if(ke->modifiers() == Qt::Modifier::ALT)
  //	{
  //		if(me->buttons() & Qt::LeftButton)
  //		{
  //			if(firstMouse)
  //			{
  //				lastX = xPos;
  //				lastY = yPos;
  //				firstMouse = false;
  //			}
  //			xPos = me->localPos().x();
  //			yPos = me->localPos().y();

  //			xOffset = xPos - lastX;
  //			yOffset = lastY - yPos;

  //			lastX = xPos;
  //			lastY = yPos;

  //			xOffset *= sensitivity;
  //			yOffset *= sensitivity;

  //			yaw += xOffset;
  //			pitch += yOffset;

  //			printf("xOffset: %f, yOffset: %f\n", xOffset, yOffset);
  //			printf("yaw: %f, pitch: %f\n", yaw, pitch);

  //			if(pitch > 89.0f)
  //				pitch = 89.0f;
  //			if(pitch < -89.0f)
  //				pitch = -89.0f;

  //			update();
  //			return true;
  //		}
  //		if(me->buttons() & Qt::MidButton)
  //		{
  //			printf("The viewport is Panned!\n");
  //			return true;
  //		}
  //		if(me->buttons() & Qt::RightButton)
  //		{
  //			printf("The viewport is Zoomed!\n");
  //			return true;
  //		}
  //	}
  //	else if(ke->modifiers() == Qt::NoModifier)
  //	{
  //		if(me->button() == Qt::LeftButton)
  //		{
  //			printf("Only Left is Pressed!\n");
  //			return true;
  //		}
  //		if(me->button() == Qt::MidButton)
  //		{
  //			printf("Only Mid is Pressed!\n");
  //			return true;
  //		}
  //		if(me->button() == Qt::RightButton)
  //		{
  //			printf("Only Right is Pressed!\n");
  //			return true;
  //		}
  //	}
  //}

  //if(event->type() == QEvent::KeyRelease)
  //{
  //	printf("We are in QEvent::KeyRelease!\n");
  //}

  return QWidget::event(event);
}