#include "Dem_qgl.h"

using namespace qglviewer;

void Dem_qgl::input(TileHash& m_allTile_) {
    m_allTile = m_allTile_;
}

void Dem_qgl::init()
{
    restoreStateFromFile();
    setBackgroundColor(::Qt::white);
    glDisable(GL_LIGHTING);
    //setGridIsDrawn();
    setSceneRadius(2000);
    camera()->fitSphere(qglviewer::Vec(0,0,0), 2000);
}

void Dem_qgl::draw()
{
    int tileSize = 256;
    int cellSize = 16;

    //show axis
    {
        glBegin(GL_LINES);
        glColor3f(255.0f, 0.0f, 0.0f);
        glVertex3dv(Vec(0.0, 0.0, 0.0));
        glVertex3dv(Vec(20.0, 0.0, 0.0));
        glColor3f(255.0f, 255.0f, 0.0f);
        glVertex3dv(Vec(0.0, 0.0, 0.0));
        glVertex3dv(Vec(0.0, 20.0, 0.0));
        glColor3f(0.0f, 255.0f, 0.0f);
        glVertex3dv(Vec(0.0, 0.0, 0.0));
        glVertex3dv(Vec(0.0, 0.0, 20.0));
        glEnd();
    }

    TileHash::iterator it = m_allTile.begin();
    for ( ; it != m_allTile.end(); ++it) {

        SPtr<tileElement> te = it->second;
        cv::Mat img = te->image.clone();

        int tileX = te->x > 0? te->x-1 : te->x;
        int tileY = te->y > 0? te->y-1 : te->y;
        int ltcorX = tileX * tileSize;
        int ltcorY = tileY * tileSize;

        //show mesher
        {
//            for (int ci=0; ci<cellSize; ++ci) {
//                for (int cj=0; cj<cellSize; ++cj) {
//                    Vec corsVec[4];
//                    corsVec[0] = Vec(ltcorX+cellSize*cj,
//                                     ltcorY+cellSize*ci,
//                                     te->cors[ci][cj]);
//                    corsVec[1] = Vec(ltcorX+cellSize*(cj+1),
//                                     ltcorY+cellSize*ci,
//                                     te->cors[ci][cj+1]);
//                    corsVec[2] = Vec(ltcorX+cellSize*(cj+1),
//                                     ltcorY+cellSize*(ci+1),
//                                     te->cors[ci+1][cj+1]);
//                    corsVec[3] = Vec(ltcorX+cellSize*(cj),
//                                     ltcorY+cellSize*(ci+1),
//                                     te->cors[ci+1][cj]);
//                    glBegin(GL_LINE_LOOP);
//                    glColor3f(0.0f, 0.0f, 255.0f);
//                    for (int i=0; i<4; ++i)
//                        glVertex3dv(corsVec[i]);
//                    glEnd();
//                }
//            }
        }

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        GLint last_texture_ID;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
        glColor3ub(255,255,255);
        unsigned int texName;
        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexImage2D(GL_TEXTURE_2D, 0,
                     GL_RGB, img.cols, img.rows, 0,
                     GL_BGR_EXT, GL_UNSIGNED_BYTE, img.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        for (int ci=0; ci<cellSize; ci++) {
            for (int cj=0; cj<cellSize; cj++) {
                Vec corsVec[4];
                corsVec[0] = Vec(ltcorX+cellSize*cj,
                                 ltcorY+cellSize*ci,
                                 te->cors[ci][cj]);
                corsVec[1] = Vec(ltcorX+cellSize*(cj+1),
                                 ltcorY+cellSize*ci,
                                 te->cors[ci][cj+1]);
                corsVec[2] = Vec(ltcorX+cellSize*(cj+1),
                                 ltcorY+cellSize*(ci+1),
                                 te->cors[ci+1][cj+1]);
                corsVec[3] = Vec(ltcorX+cellSize*(cj),
                                 ltcorY+cellSize*(ci+1),
                                 te->cors[ci+1][cj]);

                glBindTexture(GL_TEXTURE_2D, texName);
                glBegin(GL_POLYGON);
                glTexCoord2d(double(cellSize*cj)/img.cols,
                             double(cellSize*ci)/img.rows);
                glVertex3dv(corsVec[0]);

                glTexCoord2d(double(cellSize*(cj+1))/img.cols,
                             double(cellSize*ci)/img.rows);
                glVertex3dv(corsVec[1]);

                glTexCoord2d(double(cellSize*(cj+1))/img.cols,
                             double(cellSize*(ci+1))/img.rows);
                glVertex3dv(corsVec[2]);

                glTexCoord2d(double(cellSize*cj)/img.cols,
                             double(cellSize*(ci+1))/img.rows);
                glVertex3dv(corsVec[3]);
                glEnd();

            }
        }

        glBindTexture(GL_TEXTURE_2D, last_texture_ID);
    }
}
