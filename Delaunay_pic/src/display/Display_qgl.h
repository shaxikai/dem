#ifndef DISPLAY_QGL_H
#define DISPLAY_QGL_H
#include <QGLViewer/qglviewer.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Point.h>

#include "Struct_Class.h"


class Display_qgl : public QGLViewer
{
public :
    void input(Frame frame_);

protected :
    virtual void draw();
    virtual void init();

private :

    Frame frame;


};

#endif // DISPLAY_QGL_H
