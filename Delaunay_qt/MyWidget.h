#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "Triangler.h"

#include <memory>
#include <QWidget>
#include <iostream>

using namespace std;

class Triangler;

class MyWidget : public QWidget
{

public:
    explicit MyWidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

    std::vector<QPoint> pts;
    std::shared_ptr<Triangler> T;


signals:

public slots:

};

#endif // MYWIDGET_H
