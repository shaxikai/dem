#include "Display_qgl.h"

void Display_qgl::input(std::vector<qglviewer::Vec>& pointClouds_,
                        std::vector<cv::Point2d>& pointPixs_,
                        cv::Mat image_)
{
    pointClouds = pointClouds_;
    image = image_.clone();
    pointPixs.resize(pointPixs_.size());
    for (int i=0; i<pointPixs_.size(); ++i) {
        pointPixs[i].x = pointPixs_[i].x / image.cols;
        pointPixs[i].y = pointPixs_[i].y / image.rows;
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
    for (int i=2; i<pointClouds.size(); i+=3) {
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 255.0f);
        glVertex3dv(pointClouds[i-2]);
        glVertex3dv(pointClouds[i-1]);
        glVertex3dv(pointClouds[i]);
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
    cv::resize(image, image, cv::Size(1024, 1024));
    //cv::imshow("image", image);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGB, image.cols, image.rows, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, image.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    for (int i=2; i<pointClouds.size(); i+=3) {
        glBindTexture(GL_TEXTURE_2D, texName);
        glBegin(GL_POLYGON);
        glTexCoord2d(double(pointPixs[i-2].x), double(pointPixs[i-2].y)); glVertex3dv(pointClouds[i-2]);
        glTexCoord2d(double(pointPixs[i-1].x), double(pointPixs[i-1].y)); glVertex3dv(pointClouds[i-1]);
        glTexCoord2d(double(pointPixs[i].x),   double(pointPixs[i].y));   glVertex3dv(pointClouds[i]);
        glEnd();
    }
}
