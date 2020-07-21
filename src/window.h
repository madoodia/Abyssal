/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QMainWindow>

#include "oglWidget.h"

class Window : public QMainWindow
{
  Q_OBJECT
public:
  Window(QMainWindow *parent = nullptr);
  virtual ~Window();

private slots:
  void newFile();

protected:
  void
  closeEvent(QCloseEvent *event) override;

private:
  void createActions();
  void createStatusBar();

private:
  OGLWidget *viewport;
};

#endif // WINDOW_H