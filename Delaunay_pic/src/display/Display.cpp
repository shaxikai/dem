#include "Display.h"

using namespace std;
using namespace cv;

Display_cv::Display_cv(Frame frame_) : frame(frame_)
{

}

void Display_cv::frame2dem()
{
    std::vector<pi::Point3d>& pointClouds = frame.pointClouds;
    std::vector<pi::Point2d>& pointPixs   = frame.pointPixs;
    std::vector<TriEle>& tris = frame.tris;
    cv::Mat src = frame.image;
    int size = dem.size;


    double xmin = 1e99, xmax = -1e99, ymin = 1e99, ymax = -1e99;
    for(int i=0; i<pointClouds.size(); i++)
    {
        pi::Point3d& p = pointClouds[i];

        if( xmin > p.x ) xmin = p.x;
        if( xmax < p.x ) xmax = p.x;
        if( ymin > p.y ) ymin = p.y;
        if( ymax < p.y ) ymax = p.y;
    }

    dem.tileMax = pi::Point2i(xmax/size+1, ymax/size+1);
    dem.tileMin = pi::Point2i(xmin/size+1, ymin/size+1);
    dem.pixMax  = pi::Point2i(dem.tileMax.x*size, dem.tileMax.y*size);
    dem.pixMin  = pi::Point2i((dem.tileMin.x-1)*size, (dem.tileMin.y-1)*size);

    int height = dem.pixMax.y - dem.pixMin.y;
    int width  = dem.pixMax.x - dem.pixMin.x;

    Mat dst = Mat(height, width, src.type(), Scalar::all(0));

    vector<Point2f> dst_ptc;
    for (int i=0; i<pointClouds.size(); ++i) {
        dst_ptc.push_back(Point2f(pointClouds[i].x - dem.pixMin.x,
                                  pointClouds[i].y - dem.pixMin.y));
    }

    for (int i=0; i<tris.size(); ++i) {
        cv::Point2f srcTri[3];
        cv::Point2f dstTri[3];
        cv::Mat warp_mat( 2, 3, CV_32FC1 );

        srcTri[0] = Point2f(pointPixs[tris[i].c_1].x, pointPixs[tris[i].c_1].y);
        srcTri[1] = Point2f(pointPixs[tris[i].c_2].x, pointPixs[tris[i].c_2].y);
        srcTri[2] = Point2f(pointPixs[tris[i].c_3].x, pointPixs[tris[i].c_3].y);

        dstTri[0] = dst_ptc[tris[i].c_1];
        dstTri[1] = dst_ptc[tris[i].c_2];
        dstTri[2] = dst_ptc[tris[i].c_3];

        warp_mat = getAffineTransform(srcTri, dstTri);
        warpAffine(src, dst, warp_mat, dst.size());

        cv::imshow("image", dst);
        cv::waitKey(-1);


    }
}
