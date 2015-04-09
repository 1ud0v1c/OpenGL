#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>

class QPaintEvent;

class ImageWidget : public QWidget {
    Q_OBJECT
    public:
      ImageWidget(QWidget *parent = 0);
      void setImage(const QImage & image);

    protected:
      void paintEvent(QPaintEvent *) override;
      bool hasHeightForWidth() const;
      int heightForWidth(int ) const override;

    public slots:

    private:
      QImage _image;
};

#endif // IMAGEWIDGET_H
