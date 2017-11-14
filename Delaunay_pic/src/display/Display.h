#ifndef DISPLAY_H
#define DISPLAY_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Display
{
public:
    Display();

    void show(cv::Mat img, std::vector<cv::Point2d> pts);

    cv::Mat image;
};

#endif // DISPLAY_H
