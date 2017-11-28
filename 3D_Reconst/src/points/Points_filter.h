#ifndef POINTS_FILTER_H
#define POINTS_FILTER_H
#include <vector>
#include <iostream>
#include <SE3.h>

using namespace std;
using namespace pi;

class Points_filter
{
public:
    Points_filter(){}
    Points_filter(vector<Point2d>& pointPixs_, vector<Point3d>& pointClouds_);

    void ptcRansac();
    void pixFilter();
    void ptcFilter();
    void ptsFilter();

    vector<Point2d> pointPixs;
    vector<Point3d> pointClouds;
};

#endif // POINTS_FILTER_H
