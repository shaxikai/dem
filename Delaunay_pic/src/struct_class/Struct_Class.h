#ifndef STRUCT_CLASS_H
#define STRUCT_CLASS_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <Point.h>

struct TriEle
{
    int c_1, c_2, c_3;
};

class Frame
{
public :

    std::vector<int> pt_getNeipts(int id);
    std::vector<int> pt_getTris(int id);


    cv::Mat         image;
    std::vector<pi::Point2d> pointPixs;
    std::vector<pi::Point3d> pointClouds;
    std::vector<TriEle>  tris;
};

class Dem {
public :

    pi::Point2i tileMin, tileMax;
    pi::Point2i pixMin,  pixMax;
    int size = 256;

    cv::Mat image;
    cv::Mat img_h;
};

#endif // STRUCT_CLASS_H
