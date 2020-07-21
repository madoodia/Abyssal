/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>

#include "window.h"

Window::Window(QMainWindow *parent)
{
  viewport = new OGLWidget(this);
  setCentralWidget(viewport);

  setWindowTitle("Abyssal");
  resize(600, 600);
  showMaximized();
  createActions();
  createStatusBar();
}

Window::~Window()
{
}

void Window::createActions()
{
  QMenu *fileQM = menuBar()->addMenu(tr("&File"));
  QToolBar *toolbarQT = addToolBar(tr("Toolbar"));
  // const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
  QAction *newQA = new QAction(/*newIcon,*/ tr("&New"), this);
  newQA->setShortcut(QKeySequence::New);
  newQA->setStatusTip(tr("Create A new file!"));
  connect(newQA, &QAction::triggered, this, &Window::newFile);
  fileQM->addAction(newQA);
  toolbarQT->addAction(newQA);
}

void Window::createStatusBar()
{
  statusBar()->showMessage(tr("Ready!"));
}

void Window::newFile()
{
  statusBar()->showMessage(tr("I Love you my Sweet Heart <3!"));
}

void Window::closeEvent(QCloseEvent *event)
{
  QMainWindow::closeEvent(event);
}