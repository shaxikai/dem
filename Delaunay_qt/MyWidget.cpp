#include "MyWidget.h"


#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 1200, 800);
    T = std::shared_ptr<Triangler>(new Triangler());
}


void MyWidget::paintEvent(QPaintEvent *)
{   
    QPainter p(this);
    for (int i=2; i<pts.size(); i=i+3)
    {
        p.drawLine(pts[i-2], pts[i-1]);
        p.drawLine(pts[i-1], pts[i]);
        p.drawLine(pts[i], pts[i-2]);
    }
}


void MyWidget::mousePressEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();
    pts = T->convertPts(pt);
    update();
}


#include <QApplication>

int main (int argc, char** argv)
{
    QApplication app(argc, argv);
    MyWidget w;
    w.show();

    return app.exec();
}
