#ifndef POINTS_FILTER_H
#define POINTS_FILTER_H
#include <vector>
#include <iostream>
#include <SE3.h>
#include <Struct_Class.h>

using namespace std;
using namespace pi;

class Points_filter
{
public:
    Points_filter(){}
    Points_filter(Frame& frame_);

    void setFrame(Frame& frame_);

    void ptcRansac();
    void pixFilter();
    void ptcFilter();
    void ptsPrefilter();
    int ptsOutfilter();

    Frame frame;
};

#endif // POINTS_FILTER_H
