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
#include <QtCore/QString>
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
#include "api.h"
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
  void initOriginPoint();
  void drawOriginPoint();

  void initGrid();
  void drawGrid();
  void gridMVP();

  void initPlane();
  void drawPlane();
  void planeMVP();

  float calculateFPS();

  // void drawAxes();

public slots:
  void setPlaneY(float newY);

private:
  uint shaderProgram;

  uint gridVao, gridVbo;
  uint originVao, originVbo;
  uint planeVao, planeVbo;

  glm::mat4 view;
  glm::mat4 projection;

  glm::mat4 gridModel;
  glm::mat4 planeModel;

  uint gridModelLocation;
  uint gridViewLocation;
  uint gridProjectionLocation;

  uint planeModelLocation;
  uint planeViewLocation;
  uint planeProjectionLocation;

  float xRot, yRot, zRot, fov;
  float xvRot, yvRot, zvRot;
  float xPan, yPan, zPan;

  glm::vec3 cameraPos;
  glm::vec3 cameraFront;

  glm::vec3 cameraDirection;
  glm::vec3 cameraRight;
  glm::vec3 cameraUp;

  float cameraSpeed;

  // mouse
  float xPos, yPos;
  float lastX, lastY;
  float xOffset, yOffset;
  float sensitivity;
  float yaw, pitch;
  bool firstMouse;

  QVector2D mousePos;

  GLuint length;

  // Grid Data
  std::vector<float> gridVertices;
  std::vector<float> originPoint;

  // Plane Data
  std::vector<float> planeVertices;

  Shader gridShaders;
  Shader planeShaders;

  // FPS Calculation
  float lastFrameTime;
  float deltaTime;
  float lastReportedFPSFrameTime;
  uint frameCount;
  float fps;
  float totalDeltaTime;

  // Test Signal Slots
  float mNewY;
};

#endif // OGLWIDGET_H
