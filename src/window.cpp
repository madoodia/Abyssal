/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

#include "window.h"

Window::Window(QMainWindow *parent)
{

  viewport = new OGLWidget(this);

  createActions();
  createStatusBar();

  QWidget *mainQW = new QWidget;
  setCentralWidget(mainQW);

  QWidget *leftPanelQW = new QWidget;

  QSplitter *hMainQS = new QSplitter;
  hMainQS->setOrientation(Qt::Horizontal);
  hMainQS->addWidget(viewport);
  hMainQS->addWidget(leftPanelQW);

  QHBoxLayout *mainLayoutQHBL = new QHBoxLayout;
  mainLayoutQHBL->setContentsMargins(1, 1, 1, 1);
  mainLayoutQHBL->addWidget(hMainQS);

  mainQW->setLayout(mainLayoutQHBL);

  setWindowTitle("Abyssal");
  resize(600, 600);
  showMaximized();
}

Window::~Window()
{
  delete viewport;
}

void Window::createActions()
{
  QMenu *fileQM = menuBar()->addMenu(tr("&File"));

  // MenuBars: File
  // const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
  QAction *newQA = new QAction(/*newIcon,*/ tr("&New"), this);

  newQA->setShortcut(QKeySequence::New);
  newQA->setStatusTip(tr("Create A new file!"));
  connect(newQA, &QAction::triggered, this, &Window::newFile);
  fileQM->addAction(newQA);

  // Toolbars
  QToolBar *toolbarQT = addToolBar(tr("Toolbar"));
  // const QIcon selectionIcon = QIcon::fromTheme("document-new", QIcon(":/images/selection.png"));
  QAction *selectionQA = new QAction(/*selectionIcon,*/ tr("&Selection"), this);
  // const QIcon moveBrushIcon = QIcon::fromTheme("document-new", QIcon(":/images/moveBrush.png"));
  QAction *moveBrushQA = new QAction(/*moveBrushIcon,*/ tr("&Move Brush"), this);
  // const QIcon cutBrushIcon = QIcon::fromTheme("document-new", QIcon(":/images/cutBrush.png"));
  QAction *cutBrushQA = new QAction(/*cutBrushIcon,*/ tr("&Cut Brush"), this);
  // const QIcon noiseBrushIcon = QIcon::fromTheme("document-new", QIcon(":/images/noiseBrush.png"));
  QAction *noiseBrushQA = new QAction(/*noiseBrushIcon,*/ tr("&NOise Brush"), this);
  // const QIcon clumpBrushIcon = QIcon::fromTheme("document-new", QIcon(":/images/clumpBrush.png"));
  QAction *clumpBrushQA = new QAction(/*clumpBrushIcon,*/ tr("&Clump Brush"), this);

  toolbarQT->addAction(selectionQA);
  toolbarQT->addAction(moveBrushQA);
  toolbarQT->addAction(cutBrushQA);
  toolbarQT->addAction(noiseBrushQA);
  toolbarQT->addAction(clumpBrushQA);
}

void Window::createStatusBar()
{
  statusBar()->showMessage(tr("Ready!"));
}

void Window::newFile()
{
  statusBar()->showMessage(tr("The new file is Created!"));
}

void Window::closeEvent(QCloseEvent *event)
{
  QMainWindow::closeEvent(event);
}