#include "imagewidget.h"
#include <QPaintEvent>
#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent) {
  setMinimumSize(50,50);
  setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
}

void ImageWidget::setImage(const QImage & image) {
   _image = image;
   if( isVisible()) {
     update();
   }
}

void ImageWidget::paintEvent(QPaintEvent *) {
   if(_image.isNull()) {
       return;
   }
   QPainter p(this);
   p.drawImage(0,0,_image.scaled(size()));
}

bool ImageWidget::hasHeightForWidth() const {
  return true;
}

int ImageWidget::heightForWidth(int width) const {
  return width;
}
