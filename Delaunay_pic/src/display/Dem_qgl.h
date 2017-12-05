#ifndef DISPLAY_QGL_H
#define DISPLAY_QGL_H
#include <QGLViewer/qglviewer.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Point.h>

#include "Struct_Class.h"
#include "Tile.h"


class Dem_qgl : public QGLViewer
{
public :
    void input(TileHash& m_allTile_);
    virtual ~Dem_qgl(){}

protected :
    virtual void draw();
    virtual void init();

private :

    TileHash m_allTile;


};

#endif // DISPLAY_QGL_H
