#ifndef DISPLAY_H
#define DISPLAY_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Display_cv
{
public:
    Display_cv();

    void show(cv::Mat img, std::vector<cv::Point2d> pts);

    cv::Mat image;
};

#endif // DISPLAY_H
