#include <QApplication>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QtGui>

class DoubleSlider : public QSlider
{
  Q_OBJECT

public:
  DoubleSlider(QWidget *parent = 0) : QSlider(parent)
  {
    connect(this, SIGNAL(valueChanged(int)),
            this, SLOT(notifyValueChanged(int)));
  }

signals:
  void doubleValueChanged(double value);

public slots:
  void notifyValueChanged(int value)
  {
    double doubleValue = value / 10.0;
    emit doubleValueChanged(doubleValue);
  }
};

class Test : public QWidget
{
  Q_OBJECT
public:
  Test(QWidget *parent = 0) : QWidget(parent),
                              m_slider(new DoubleSlider()),
                              m_label(new QLabel())
  {
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setRange(0, 100);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_slider);
    layout->addWidget(m_label);
    connect(m_slider, SIGNAL(doubleValueChanged(double)),
            this, SLOT(updateLabelValue(double)));
    updateLabelValue(m_slider->value());
  }

public slots:
  void updateLabelValue(double value)
  {
    m_label->setText(QString::number(value, 'f', 2));
  }

private:
  QSlider *m_slider;
  QLabel *m_label;
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Test *wid = new Test();
  wid->show();

  return a.exec();
}
#include "test.moc"