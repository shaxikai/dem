#ifndef DISPLAY_H
#define DISPLAY_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Struct_Class.h"
#include "Tile.h"

class Display_cv
{
public:
    Display_cv();

    int frame2dem(Frame& frame, Dem& dem);

    int demFusion(Dem& dem);


    SPtr<tileManager> tile_manager;

};

#endif // DISPLAY_H
