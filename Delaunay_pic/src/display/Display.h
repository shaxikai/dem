#ifndef DISPLAY_H
#define DISPLAY_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Struct_Class.h"

class Display_cv
{
public:
    Display_cv(){}
    Display_cv(Frame frame_);


    void frame2dem();

    Frame frame;
    Dem   dem;
};

#endif // DISPLAY_H
