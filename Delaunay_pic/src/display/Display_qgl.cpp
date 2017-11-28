#include "Display_qgl.h"

void Display_qgl::input(Frame frame_)
{
    frame = frame_;

    for (int i=0; i<frame.pointPixs.size(); ++i) {
        frame.pointPixs[i].x /= frame.image.cols;
        frame.pointPixs[i].y /= frame.image.rows;
    }
}

void Display_qgl::init()
{
    restoreStateFromFile();
    setBackgroundColor(::Qt::white);
    glDisable(GL_LIGHTING);
    //setGridIsDrawn();
    setSceneRadius(100);
    camera()->fitSphere(qglviewer::Vec(0,0,0), 200);
}

void Display_qgl::draw()
{
    //std::vector<pi::Point3d>& pointClouds = frame.pointClouds;

    for (size_t i=0; i<frame.tris.size(); ++i) {
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 255.0f);
        glVertex3dv(qglviewer::Vec(frame.pointClouds[frame.tris[i].c_1].x,
                                   frame.pointClouds[frame.tris[i].c_1].y,
                                   frame.pointClouds[frame.tris[i].c_1].z));
                //0.0));
        glVertex3dv(qglviewer::Vec(frame.pointClouds[frame.tris[i].c_2].x,
                                   frame.pointClouds[frame.tris[i].c_2].y,
                                   frame.pointClouds[frame.tris[i].c_2].z));
                //0.0));
        glVertex3dv(qglviewer::Vec(frame.pointClouds[frame.tris[i].c_3].x,
                                   frame.pointClouds[frame.tris[i].c_3].y,
                                   frame.pointClouds[frame.tris[i].c_3].z));
                //0.0));
        glEnd();
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    GLint last_texture_ID;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
    glColor3ub(255,255,255);
    unsigned int texName;
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    cv::resize(frame.image, frame.image, cv::Size(1024, 1024));
    //cv::imshow("image", image);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGB, frame.image.cols, frame.image.rows, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, frame.image.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    for (size_t i=0; i<frame.tris.size(); ++i) {
        glBindTexture(GL_TEXTURE_2D, texName);
        glBegin(GL_POLYGON);
        glTexCoord2d(double(frame.pointPixs[frame.tris[i].c_1].x),
                     double(frame.pointPixs[frame.tris[i].c_1].y));
        glVertex3dv(qglviewer::Vec(frame.pointClouds[frame.tris[i].c_1].x,
                                   frame.pointClouds[frame.tris[i].c_1].y,
                                   frame.pointClouds[frame.tris[i].c_1].z));
                //0.0));

        glTexCoord2d(double(frame.pointPixs[frame.tris[i].c_2].x),
                     double(frame.pointPixs[frame.tris[i].c_2].y));
        glVertex3dv(qglviewer::Vec(frame.pointClouds[frame.tris[i].c_2].x,
                                   frame.pointClouds[frame.tris[i].c_2].y,
                                   frame.pointClouds[frame.tris[i].c_2].z));
                //0.0));

        glTexCoord2d(double(frame.pointPixs[frame.tris[i].c_3].x),
                     double(frame.pointPixs[frame.tris[i].c_3].y));
        glVertex3dv(qglviewer::Vec(frame.pointClouds[frame.tris[i].c_3].x,
                                   frame.pointClouds[frame.tris[i].c_3].y,
                                   frame.pointClouds[frame.tris[i].c_3].z));
                //0.0));
        glEnd();
    }
}
