#include "Display.h"

Display::Display()
{

}

void Display::show(cv::Mat img, std::vector<cv::Point2d> pts)
{
    for (int i=2; i<pts.size(); i+=3) {
        cv::line(img, pts[i-2], pts[i-1], cv::Scalar(255,0,0));
        cv::line(img, pts[i-1], pts[i], cv::Scalar(255,0,0));
        cv::line(img, pts[i], pts[i-2], cv::Scalar(255,0,0));
    }
    cv::resize(img, image, cv::Size(), 0.5, 0.5);
    cv::namedWindow("image", 0);
    cv::imshow("image", image);
    cv::waitKey(-1);
}
