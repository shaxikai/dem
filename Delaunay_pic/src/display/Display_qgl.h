#ifndef DISPLAY_QGL_H
#define DISPLAY_QGL_H
#include <QGLViewer/qglviewer.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Point.h>


class Display_qgl : public QGLViewer
{
public :
    void input(std::vector<qglviewer::Vec>& pointClouds_,
               std::vector<cv::Point2d>& pointPixs_,
               cv::Mat image_);

protected :
    virtual void draw();
    virtual void init();

private :

    std::vector<qglviewer::Vec> pointClouds;
    std::vector<pi::Point2d>      pointPixs;
    cv::Mat image;


};

#endif // DISPLAY_QGL_H
