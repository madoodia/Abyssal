/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

#ifndef OGLWIDGET_H
#define OGLWIDGET_H

// C++ Headers
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vector>

// Third Party Headers
#include <GL/glew.h>

#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtCore/QTime>
#include <QtCore/Qt>
#include <QtGui/QCloseEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtGui/QSurfaceFormat>
#include <QtGui/QVector2D>
#include <QtWidgets/QOpenGLWidget>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Our Headers
#include "shader.h"

class OGLWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OGLWidget(QWidget *parent = nullptr);
  ~OGLWidget();

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  void closeEvent(QCloseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void enterEvent(QEvent *event) override;
  void leaveEvent(QEvent *event) override;
  bool event(QEvent *event) override;

private:
  unsigned int vao, vbo, ibo, ebo, shaderProgram;
  unsigned int modelLocation, projectionLocation, viewLocation;

  float xRot, yRot, zRot, fov;
  float xvRot, yvRot, zvRot;
  float xPan, yPan, zPan;

  glm::vec3 cameraPos;
  glm::vec3 cameraFront;

  glm::vec3 cameraDirection;
  glm::vec3 cameraRight;
  glm::vec3 cameraUp;

  float cameraSpeed;

  float deltaTime;
  float lastFrame;
  float currentFrame;

  // mouse
  float xPos, yPos;
  float lastX, lastY;
  float xOffset, yOffset;
  float sensitivity;
  float yaw, pitch;
  bool firstMouse;

  QVector2D mousePos;

  QTime t0, t1;
  float interval, nbFrames;

  GLuint length;

  Shader ourShaders;
};

#endif // OGLWIDGET_H
