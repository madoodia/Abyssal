/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

#include <QDoubleValidator>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QRadioButton>
#include <QRect>
#include <QSpinBox>
#include <QSplitter>
#include <QStatusBar>
#include <QToolBar>
#include <QToolButton>
#include <QWidget>

#include "window.h"

Window::Window(QMainWindow *parent)
{

  viewport = new OGLWidget(this);
  // viewport->setMinimumWidth(this->width() * .7);
  viewport->setMinimumSize(400, 400);

  createActions();
  createStatusBar();

  QWidget *mainQW = new QWidget;
  setCentralWidget(mainQW);

  QWidget *leftPanelQW = new QWidget;
  // leftPanelQW->setMinimumWidth(this->width() * .3);
  leftPanelQW->setMinimumSize(300, 400);
  leftPanelQW->setMaximumWidth(450);

  // C++ State Groups
  QGroupBox *threadStateQGB = new QGroupBox(tr("Method of Calculation (C++ Threads)  "));
  // threadStateQGB->setCheckable(true);

  QRadioButton *singleThreadQRB = new QRadioButton(tr("&Single"));
  QRadioButton *multiThreadQRB = new QRadioButton(tr("&Multi"));
  QRadioButton *openclQRB = new QRadioButton(tr("&OpenCL"));
  singleThreadQRB->setChecked(true);

  QHBoxLayout *methodsQHBL = new QHBoxLayout;
  methodsQHBL->addWidget(singleThreadQRB);
  methodsQHBL->addWidget(multiThreadQRB);
  methodsQHBL->addWidget(openclQRB);
  methodsQHBL->addStretch(1);
  threadStateQGB->setLayout(methodsQHBL);

  // Plane Properties Groups
  QGroupBox *planePropertiesQGB = new QGroupBox(tr("Plane"));
  // planePropertiesQGB->setCheckable(true);

  MDoubleSliderGroup *planeWidthMSB = new MDoubleSliderGroup("Width:", 1, 100, 1, 1);
  MDoubleSliderGroup *planeHeightMSB = new MDoubleSliderGroup("Height:", 1, 100, 1, 0.1);

  QLabel *divisionsQL = new QLabel("Div:");
  MIntSliderGroup *planeDivXQSB = new MIntSliderGroup("X:", 1, 10, 1, 1);
  MIntSliderGroup *planeDivYQSB = new MIntSliderGroup("Y:", 1, 10, 1, 1);

  QHBoxLayout *planesDivQHBL = new QHBoxLayout;
  planesDivQHBL->addWidget(divisionsQL);
  planesDivQHBL->addWidget(planeDivXQSB);
  planesDivQHBL->addWidget(planeDivYQSB);
  QVBoxLayout *planesPropertiesQVBL = new QVBoxLayout;
  planesPropertiesQVBL->addWidget(planeWidthMSB);
  planesPropertiesQVBL->addWidget(planeHeightMSB);
  planesPropertiesQVBL->addLayout(planesDivQHBL);
  planesPropertiesQVBL->setContentsMargins(1, 1, 1, 1);

  planePropertiesQGB->setLayout(planesPropertiesQVBL);

  // Hair Properties Groups
  QGroupBox *hairPropertiesQGB = new QGroupBox(tr("Hair"));
  // hairPropertiesQGB->setCheckable(true);

  MDoubleSliderGroup *hairLengthMSB = new MDoubleSliderGroup("Length:", 1, 100, 1, 1);

  QLabel *widthQL = new QLabel("Width:");
  MIntSliderGroup *hairWidthBaseMSB = new MIntSliderGroup("Base:", 1, 10, 1, 1);
  MIntSliderGroup *hairWidthTipMSB = new MIntSliderGroup("Tip:", 1, 10, 1, 1);

  QHBoxLayout *hairsWidthQHBL = new QHBoxLayout;
  hairsWidthQHBL->addWidget(widthQL);
  hairsWidthQHBL->addWidget(hairWidthBaseMSB);
  hairsWidthQHBL->addWidget(hairWidthTipMSB);

  QLabel *bendQL = new QLabel("Bend:");
  MIntSliderGroup *hairBendUMSB = new MIntSliderGroup("U:", -180, 180, 0, 1);
  MIntSliderGroup *hairBendVMSB = new MIntSliderGroup("V:", -180, 180, 0, 1);

  QHBoxLayout *hairsBendQHBL = new QHBoxLayout;
  hairsBendQHBL->addWidget(bendQL);
  hairsBendQHBL->addWidget(hairBendUMSB);
  hairsBendQHBL->addWidget(hairBendVMSB);

  MIntSliderGroup *hairPointsTipMSB = new MIntSliderGroup("Points:", 4, 1000, 1, 1);

  // for test
  MDoubleSliderGroup *planeYMSB = new MDoubleSliderGroup("High/Low:", -100, 100, 0, 1);

  QVBoxLayout *hairPropertiesQVBL = new QVBoxLayout;
  hairPropertiesQVBL->addWidget(hairLengthMSB);
  hairPropertiesQVBL->addLayout(hairsWidthQHBL);
  hairPropertiesQVBL->addLayout(hairsBendQHBL);
  hairPropertiesQVBL->addWidget(hairPointsTipMSB);
  hairPropertiesQVBL->addWidget(planeYMSB);
  hairPropertiesQVBL->setContentsMargins(1, 1, 1, 1);

  hairPropertiesQGB->setLayout(hairPropertiesQVBL);

  // main properties layout
  QVBoxLayout *propertiesQVBL = new QVBoxLayout;
  propertiesQVBL->addWidget(threadStateQGB);
  propertiesQVBL->addWidget(planePropertiesQGB);
  propertiesQVBL->addWidget(hairPropertiesQGB);
  propertiesQVBL->addStretch(1);
  propertiesQVBL->setContentsMargins(1, 1, 1, 1);

  leftPanelQW->setLayout(propertiesQVBL);

  // Small toolbar
  QWidget *smallToolsQW = new QWidget;
  smallToolsQW->setMinimumWidth(30);
  smallToolsQW->setMaximumWidth(30);

  // QToolButton *gridQTB = new QToolButton;
  // // gridQTB->setToolTip(toolTip);
  // // gridQTB->setIcon(icon);
  // // gridQTB->setIconSize(QSize(32, 32));

  // QToolButton *pointQTB = new QToolButton;
  // QToolButton *pointNumQTB = new QToolButton;

  QPushButton *gridQTB = new QPushButton("G");
  gridQTB->setStatusTip("Toggle Grid");
  QPushButton *wireframeQTB = new QPushButton("W");
  wireframeQTB->setStatusTip("Toggle Wireframe/Surface Shading");
  QPushButton *pointQTB = new QPushButton("P");
  pointQTB->setStatusTip("Toggle Show/Hide Curve Points");
  QPushButton *pointNumQTB = new QPushButton("N");
  pointNumQTB->setStatusTip("Toggle Show/Hide Curve Points Numbers");

  QVBoxLayout *smallToolsQVBL = new QVBoxLayout;
  smallToolsQVBL->addWidget(gridQTB);
  smallToolsQVBL->addWidget(wireframeQTB);
  smallToolsQVBL->addWidget(pointQTB);
  smallToolsQVBL->addWidget(pointNumQTB);
  smallToolsQVBL->addStretch(1);
  smallToolsQVBL->setContentsMargins(1, 1, 1, 1);

  smallToolsQW->setLayout(smallToolsQVBL);

  // Main Layout
  QSplitter *hMainQS = new QSplitter;
  hMainQS->setOrientation(Qt::Horizontal);
  hMainQS->addWidget(viewport);
  hMainQS->addWidget(smallToolsQW);
  hMainQS->addWidget(leftPanelQW);

  QHBoxLayout *mainLayoutQHBL = new QHBoxLayout;
  mainLayoutQHBL->setContentsMargins(1, 1, 1, 1);
  mainLayoutQHBL->addWidget(hMainQS);
  mainQW->setLayout(mainLayoutQHBL);

  // Signals to the Viewport
  /* Codes Here*/
  // connect(planeYMSB, &QDoubleSpinBox::valueChanged, viewport, SLOT(setPlaneY(float)));
  // -----------------------

  setWindowTitle("Abyssal");
  resize(650, 400);
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
  QAction *noiseBrushQA = new QAction(/*noiseBrushIcon,*/ tr("&Noise Brush"), this);
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

// ----------------------------------

// IntSlider::IntSlider(QString name,
//                      int min,
//                      int max,
//                      int def,
//                      int step,
//                      QWidget *parent)
// {
//   nameQL = new QLabel(name);
//   sliderQS = new QSlider;
//   numberQSB = new QSpinBox;
//   numberQSB->setRange(min, max);
//   numberQSB->setValue(def);
//   numberQSB->setSingleStep(step);
//   numberQSB->setButtonSymbols(QAbstractSpinBox::NoButtons);
//   sliderQS->setOrientation(Qt::Horizontal);
//   sliderQS->setGeometry(QRect(60, 60, 100, 22));
//   sliderQS->setSingleStep(step);
//   sliderQS->setRange(min, max);
//   sliderQS->setValue(def);
//   sliderQS->setTickPosition(QSlider::TicksBothSides);
//   sliderQS->setTickInterval(10);

//   QHBoxLayout *mainLayout = new QHBoxLayout;
//   mainLayout->addWidget(nameQL);
//   mainLayout->addWidget(numberQSB);
//   mainLayout->addWidget(sliderQS);

//   connect(sliderQS, &QSlider::valueChanged, numberQSB, QOverload<int>::of(&QSpinBox::setValue));
//   connect(numberQSB, QOverload<int>::of(&QSpinBox::valueChanged), sliderQS, &QSlider::setValue);

//   this->setLayout(mainLayout);
// }

// IntSlider::~IntSlider()
// {
// }

MIntSliderGroup::MIntSliderGroup(QString name,
                                 int min,
                                 int max,
                                 int def,
                                 int step,
                                 QWidget *parent)
{
  nameQL = new QLabel(name);

  // sliderQS = new MDoubleSlider;
  numberQSB = new QSpinBox;
  numberQSB->setRange(min, max);
  numberQSB->setGeometry(QRect(60, 60, 200, 22));
  numberQSB->setValue(def);
  numberQSB->setSingleStep(step);
  // numberQSB->setButtonSymbols(QAbstractSpinBox::NoButtons);
  // sliderQS->setOrientation(Qt::Horizontal);
  // sliderQS->setGeometry(QRect(60, 60, 100, 22));
  // sliderQS->setSingleStep(step);
  // sliderQS->setRange(min, max);
  // sliderQS->setValue(def);
  // sliderQS->setTickPosition(QSlider::TicksBothSides);
  // sliderQS->setTickInterval(10);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(nameQL);
  mainLayout->addWidget(numberQSB);
  // mainLayout->addStretch(1);
  // mainLayout->addWidget(sliderQS);

  // connect(sliderQS, &MDoubleSlider::doubleValueChanged,
  //         numberQDSB, &QDoubleSpinBox::setValue);
  // connect(sliderQS, SIGNAL(doubleValueChanged(double)),
  //         numberQDSB, SLOT(setValue(double)));
  // connect(numberQDSB, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
  //         sliderQS, &QSlider::setValue);

  this->setLayout(mainLayout);
}

MIntSliderGroup::~MIntSliderGroup()
{
}

MDoubleSliderGroup::MDoubleSliderGroup(QString name,
                                       int min,
                                       int max,
                                       int def,
                                       float step,
                                       QWidget *parent)
{
  nameQL = new QLabel(name);

  // sliderQS = new MDoubleSlider;
  numberQDSB = new QDoubleSpinBox;
  numberQDSB->setRange(min, max);
  numberQDSB->setGeometry(QRect(60, 60, 200, 22));
  numberQDSB->setValue(def);
  numberQDSB->setSingleStep(step);
  // numberQDSB->setButtonSymbols(QAbstractSpinBox::NoButtons);
  // sliderQS->setOrientation(Qt::Horizontal);
  // sliderQS->setGeometry(QRect(60, 60, 100, 22));
  // sliderQS->setSingleStep(step);
  // sliderQS->setRange(min, max);
  // sliderQS->setValue(def);
  // sliderQS->setTickPosition(QSlider::TicksBothSides);
  // sliderQS->setTickInterval(10);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(nameQL);
  mainLayout->addWidget(numberQDSB);
  // mainLayout->addStretch(1);
  // mainLayout->addWidget(sliderQS);

  // connect(sliderQS, &MDoubleSlider::doubleValueChanged,
  //         numberQDSB, &QDoubleSpinBox::setValue);
  // connect(sliderQS, SIGNAL(doubleValueChanged(double)),
  //         numberQDSB, SLOT(setValue(double)));
  // connect(numberQDSB, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
  //         sliderQS, &QSlider::setValue);

  this->setLayout(mainLayout);
}

MDoubleSliderGroup::~MDoubleSliderGroup()
{
}