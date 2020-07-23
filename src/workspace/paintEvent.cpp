#include <QApplication>
#include <QtWidgets>

class PixmapLabel : public QLabel
{
public:
  explicit PixmapLabel(QWidget *parent = nullptr) : QLabel(parent)
  {
    //By default, this class scales the pixmap according to the label's size
    setScaledContents(true);
  }
  ~PixmapLabel() {}

protected:
  void paintEvent(QPaintEvent *event);

private:
  //QImage to cache the pixmap()
  //to avoid constructing a new QImage on every scale operation
  QImage cachedImage;
  //used to cache the last scaled pixmap
  //to avoid calling scale again when the size is still at the same
  QPixmap scaledPixmap;
  //key for the currently cached QImage and QPixmap
  //used to make sure the label was not set to another QPixmap
  qint64 cacheKey{0};
};

//based on the implementation of QLabel::paintEvent
void PixmapLabel::paintEvent(QPaintEvent *event)
{
  //if this is assigned to a pixmap
  if (pixmap() && !pixmap()->isNull())
  {
    QStyle *style = PixmapLabel::style();
    QPainter painter(this);
    drawFrame(&painter);
    QRect cr = contentsRect();
    cr.adjust(margin(), margin(), -margin(), -margin());
    int align = QStyle::visualAlignment(layoutDirection(), alignment());
    QPixmap pix;
    if (hasScaledContents())
    { //if scaling is enabled
      QSize scaledSize = cr.size() * devicePixelRatioF();
      //if scaledPixmap is invalid
      if (scaledPixmap.isNull() || scaledPixmap.size() != scaledSize || pixmap()->cacheKey() != cacheKey)
      {
        //if cachedImage is also invalid
        if (pixmap()->cacheKey() != cacheKey)
        {
          //reconstruct cachedImage
          cachedImage = pixmap()->toImage();
        }
        QImage scaledImage = cachedImage.scaled(
            scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        scaledPixmap = QPixmap::fromImage(scaledImage);
        scaledPixmap.setDevicePixelRatio(devicePixelRatioF());
      }
      pix = scaledPixmap;
    }
    else
    { // no scaling, Just use pixmap()
      pix = *pixmap();
    }
    QStyleOption opt;
    opt.initFrom(this);
    if (!isEnabled())
      pix = style->generatedIconPixmap(QIcon::Disabled, pix, &opt);
    style->drawItemPixmap(&painter, cr, align, pix);
  }
  else
  { //otherwise (if the label is not assigned to a pixmap)
    //call base paintEvent
    QLabel::paintEvent(event);
  }
}

//DEMO program
QPixmap generatePixmap(QSize size)
{
  QPixmap pixmap(size);
  pixmap.fill(Qt::white);
  QPainter p(&pixmap);
  p.setRenderHint(QPainter::Antialiasing);
  p.setPen(QPen(Qt::black, 10));
  p.drawEllipse(pixmap.rect());
  p.setPen(QPen(Qt::red, 2));
  p.drawLine(pixmap.rect().topLeft(), pixmap.rect().bottomRight());
  p.drawLine(pixmap.rect().topRight(), pixmap.rect().bottomLeft());
  return pixmap;
}

int main(int argc, char *argv[])

{
  QApplication a(argc, argv);

  QPixmap pixmap = generatePixmap(QSize(1280, 960));
  PixmapLabel label;
  label.setPixmap(pixmap);
  label.setAlignment(Qt::AlignCenter);
  label.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  label.setMinimumSize(320, 240);
  label.show();

  return a.exec();
}