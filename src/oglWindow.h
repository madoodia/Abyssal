/* --------------------- */
/* (C) 2020 madoodia.com */
/* --------------------- */

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
#include <QtCore/QTime>
#include <QtCore/QObject>
#include <QtGui/QPainter>
#include <QtGui/QVector2D>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Our Headers
#include "shader.h"

class OGLWindow : public QOpenGLWidget
{
  Q_OBJECT

public:
  OGLWindow(QWidget *parent = nullptr);
  ~OGLWindow();

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  void closeEvent(QCloseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  bool event(QEvent *event) override;

private:
  unsigned int vao, vbo, ebo, shaderProgram;
  unsigned int texture1, texture2;
  unsigned int modelLocation, projectionLocation, viewLocation;

  float mixValue;
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

  Shader ourShaders;
};

#endif // OGLWINDOW_H
