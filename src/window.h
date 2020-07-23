/* --------------------- */
/* (C) 2020 madoodia.com */
/*  All Rights Reserved. */
/* --------------------- */

#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

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
  // void createGroup();

private:
  OGLWidget *viewport;
};

// -------------------------------------

class MDoubleSlider : public QSlider
{
  Q_OBJECT

public:
  MDoubleSlider(QWidget *parent = nullptr)
      : QSlider(parent)
  {
    connect(this, SIGNAL(valueChanged(double)),
            this, SLOT(notifyValueChanged(int)));
  }

signals:
  void doubleValueChanged(double value);

public slots:
  void notifyValueChanged(int value)
  {
    double doubleValue = (double)value / 10.0;
    emit doubleValueChanged(doubleValue);
  }

private:
  float mDivider;
};

class MDoubleSliderGroup : public QWidget
{
  Q_OBJECT
public:
  MDoubleSliderGroup(QString name,
                     int min,
                     int max,
                     int def,
                     float step = 1.0,
                     QWidget *parent = nullptr);
  ~MDoubleSliderGroup();

private:
  QLabel *nameQL;
  // MDoubleSlider *sliderQS;
  QDoubleSpinBox *numberQDSB;
};

class MIntSliderGroup : public QWidget
{
  Q_OBJECT
public:
  MIntSliderGroup(QString name,
                  int min,
                  int max,
                  int def,
                  int step = 1,
                  QWidget *parent = nullptr);
  ~MIntSliderGroup();

private:
  QLabel *nameQL;
  // MDoubleSlider *sliderQS;
  QSpinBox *numberQSB;
};

/*
class IntSlider : public QWidget
{
  Q_OBJECT
public:
  IntSlider(QString name,
            int min,
            int max,
            int def,
            int step = 1,
            QWidget *parent = nullptr);
  ~IntSlider();

private:
  QLabel *nameQL;
  QSlider *sliderQS;
  QSpinBox *numberQSB;
};
class DoubleSlider : public QWidget
{
  Q_OBJECT
public:
  DoubleSlider(QString name,
               int min,
               int max,
               int def,
               float step = 0.1,
               QWidget *parent = nullptr);
  ~DoubleSlider();

private:
  QLabel *nameQL;
  QSlider *sliderQS;
  QDoubleSpinBox *numberQDSB;
};
*/
#endif // WINDOW_H