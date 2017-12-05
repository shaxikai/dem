#include "Display.h"
#include <math.h>
#include <Array.h>

using namespace std;
using namespace cv;

inline int tileCoor(double x, int size){
    if (x>0) return x/size+1;
    else return x/size-1;
}

Display_cv::Display_cv()
{
    tile_manager = SPtr<tileManager>(new tileManager());
}



int Display_cv::frame2dem(Frame& frame, Dem& dem)
{
    std::vector<pi::Point3d>& pointClouds = frame.pointClouds;
    std::vector<pi::Point2d>& pointPixs   = frame.pointPixs;
    std::vector<TriEle>& tris = frame.tris;
    cv::Mat src = frame.image;
    int size  = dem.size;
    int scale = dem.scale;

    double xmin = 1e99, xmax = -1e99, ymin = 1e99, ymax = -1e99;
    for(int i=0; i<pointClouds.size(); i++)
    {
        pointClouds[i] = pointClouds[i] * scale;
        pi::Point3d& p = pointClouds[i];

        if( xmin > p.x ) xmin = p.x;
        if( xmax < p.x ) xmax = p.x;
        if( ymin > p.y ) ymin = p.y;
        if( ymax < p.y ) ymax = p.y;
    }

    dem.tileMax = pi::Point2i(tileCoor(xmax, size), tileCoor(ymax, size));
    dem.tileMin = pi::Point2i(tileCoor(xmin, size), tileCoor(ymin, size));
    dem.pixMax  = pi::Point2i(dem.tileMax.x*size, dem.tileMax.y*size);
    dem.pixMin  = pi::Point2i(dem.tileMin.x*size, dem.tileMin.y*size);

//    cout << dem.tileMax << endl;
//    cout << dem.tileMin << endl;

    int height = dem.pixMax.y - dem.pixMin.y;
    int width  = dem.pixMax.x - dem.pixMin.x;

    //image
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
        Mat dst_  = Mat(height, width, src.type(), Scalar::all(0));
        Mat mask_ = Mat(height, width, CV_8UC1,    Scalar::all(0));

        srcTri[0] = Point2f(pointPixs[tris[i].c_1].x, pointPixs[tris[i].c_1].y);
        srcTri[1] = Point2f(pointPixs[tris[i].c_2].x, pointPixs[tris[i].c_2].y);
        srcTri[2] = Point2f(pointPixs[tris[i].c_3].x, pointPixs[tris[i].c_3].y);

        dstTri[0] = dst_ptc[tris[i].c_1];
        dstTri[1] = dst_ptc[tris[i].c_2];
        dstTri[2] = dst_ptc[tris[i].c_3];

        warp_mat = getAffineTransform(srcTri, dstTri);
        warpAffine(src, dst_, warp_mat, dst.size());

        Point triCs[1][3];
        triCs[0][0] = Point2i(dstTri[0].x, dstTri[0].y);
        triCs[0][1] = Point2i(dstTri[1].x, dstTri[1].y);
        triCs[0][2] = Point2i(dstTri[2].x, dstTri[2].y);

        const Point* pt[1] = {triCs[0]};
        int npt[1] = {3};

        polylines(mask_, pt, npt, 1, 1, Scalar::all(256));
        fillPoly( mask_, pt, npt, 1,    Scalar::all(256), 8);

        dst_.copyTo(dst, mask_);

    }
    dem.image = dst;

//    cv::imshow("dst", dst);

    //weight
    cv::Mat weight = cv::Mat(dst.rows, dst.cols, CV_8UC1, cv::Scalar::all(0));
    {
        float x_ = 0, y_ = 0;
        for (int i=0; i<dst_ptc.size(); ++i) {
            x_ += dst_ptc[i].x;
            y_ += dst_ptc[i].y;
        }
        Point2f center = Point2f(x_/dst_ptc.size(), y_/dst_ptc.size());

        float max_dis = 0;
        for (int i=0; i<dst_ptc.size(); ++i) {
            double dis = pow((center.x-dst_ptc[i].x), 2) +
                    pow((center.y-dst_ptc[i].y), 2);
            if ( dis > max_dis ) max_dis = dis;
        }

        uint8_t *p = weight.data;
        for (int i=0; i<weight.rows; ++i) {
            for (int j=0; j<weight.cols; ++j) {
                double dis = pow((i-center.y), 2) + pow((j-center.x), 2);
                dis = 1 - sqrt(dis) / sqrt(max_dis);
                p[0] = dis * 255;
                p++;
            }
        }
        cv::Mat gray;
        cv::cvtColor(dst, gray, CV_RGB2GRAY);
        weight.setTo(cv::Scalar::all(0), gray == 0);
    }

    dem.weight = weight;
    //cv::imshow("weight" ,weight);

    vector<Point3f> imgPtc;
    for (int i=0; i<pointClouds.size(); ++i) {
        imgPtc.push_back(Point3f(pointClouds[i].x - dem.pixMin.x,
                                 pointClouds[i].y - dem.pixMin.y,
                                 pointClouds[i].z));
    }
    //img_h
    int h_ = 0;
    for (int i=dem.tileMin.y; i<=dem.tileMax.y; ++i) {
        if (i==0) continue;
        int _i = 0, _j = 0;
        if(dem.tileMin.y<0 && i>0) _i = 1;
        else _i = 0;
        for (int j=dem.tileMin.x; j<=dem.tileMax.x; ++j) {
            if (j==0) continue;
            if(dem.tileMin.x<0 && j>0) _j = 1;
            else _j = 0;

            //get cell corners' hight
            for (int cor_i=0; cor_i<=16; ++cor_i) {
                for (int cor_j=0; cor_j<=16; ++cor_j) {
                    double coor_x = size*(j-dem.tileMin.x-_j)+cor_j*16;
                    double coor_y = size*(i-dem.tileMin.y-_i)+cor_i*16;

                    int tris_i = 0;
                    for (; tris_i<tris.size(); ++tris_i) {
                        int count = 0;

                        double k_ = (imgPtc[tris[tris_i].c_1].y - imgPtc[tris[tris_i].c_2].y)/
                                (imgPtc[tris[tris_i].c_1].x - imgPtc[tris[tris_i].c_2].x);
                        double b_ = imgPtc[tris[tris_i].c_1].y +
                                k_ * (coor_x-imgPtc[tris[tris_i].c_1].x);

                        if ( (coor_x-imgPtc[tris[tris_i].c_1].x) *
                             (coor_x-imgPtc[tris[tris_i].c_2].x) < 0 &&
                             coor_y > b_ )
                            count++;

                        k_ = (imgPtc[tris[tris_i].c_2].y - imgPtc[tris[tris_i].c_3].y)/
                                (imgPtc[tris[tris_i].c_2].x - imgPtc[tris[tris_i].c_3].x);
                        b_ = imgPtc[tris[tris_i].c_2].y +
                                k_ * (coor_x-imgPtc[tris[tris_i].c_2].x);

                        if ( (coor_x-imgPtc[tris[tris_i].c_2].x) *
                             (coor_x-imgPtc[tris[tris_i].c_3].x) < 0 &&
                             coor_y > b_ )
                            count++;

                        k_ = (imgPtc[tris[tris_i].c_3].y - imgPtc[tris[tris_i].c_1].y)/
                                (imgPtc[tris[tris_i].c_3].x - imgPtc[tris[tris_i].c_1].x);
                        b_ = imgPtc[tris[tris_i].c_3].y +
                                k_ * (coor_x-imgPtc[tris[tris_i].c_3].x);

                        if ( (coor_x-imgPtc[tris[tris_i].c_3].x) *
                             (coor_x-imgPtc[tris[tris_i].c_1].x) < 0 &&
                             coor_y > b_ )
                            count++;

                        if( count == 1 ) break;
                    }
                    //cout << bool(tris_i != tris.size()) << " ";
                    if (tris_i != tris.size()) {
                        vector<float> _a, _b, a_b;
                        _a.push_back(imgPtc[tris[tris_i].c_2].x - imgPtc[tris[tris_i].c_1].x);
                        _a.push_back(imgPtc[tris[tris_i].c_2].y - imgPtc[tris[tris_i].c_1].y);
                        _a.push_back(imgPtc[tris[tris_i].c_2].z - imgPtc[tris[tris_i].c_1].z);
                        _b.push_back(imgPtc[tris[tris_i].c_3].x - imgPtc[tris[tris_i].c_1].x);
                        _b.push_back(imgPtc[tris[tris_i].c_3].y - imgPtc[tris[tris_i].c_1].y);
                        _b.push_back(imgPtc[tris[tris_i].c_3].z - imgPtc[tris[tris_i].c_1].z);
                        a_b.push_back(_a[1]*_b[2] - _a[2]*_b[1]);
                        a_b.push_back(_a[2]*_b[0] - _a[0]*_b[2]);
                        a_b.push_back(_a[0]*_b[1] - _a[1]*_b[0]);
                        double _x = imgPtc[tris[tris_i].c_1].x - coor_x;
                        double _y = imgPtc[tris[tris_i].c_1].y - coor_y;
                        dem.img_h[h_][cor_i][cor_j] = imgPtc[tris[tris_i].c_1].z +
                                (a_b[0]*_x + a_b[1]*_y)/a_b[2];
                    } else dem.img_h[h_][cor_i][cor_j] = 0;
                }
            }
            ++h_;
        }
    }
    return 0;

}

int Display_cv::demFusion(Dem &dem) {

    int size = dem.size;
    cv::Mat image  = dem.image;
    cv::Mat weight = dem.weight;

    //tile fusion
    int h_ = 0;
    for (int i=dem.tileMin.y; i<=dem.tileMax.y; ++i) {
        if (i==0) continue;
        int _i = 0, _j = 0;
        if(dem.tileMin.y<0 && i>0) _i = 1;
        else _i = 0;
        for (int j=dem.tileMin.x; j<=dem.tileMax.x; ++j) {
            if (j==0) continue;
            if(dem.tileMin.x<0 && j>0) _j = 1;
            else _j = 0;

            //tile fusion
            cv::Rect tileRect(size*(j-dem.tileMin.x-_j),
                                size*(i-dem.tileMin.y-_i),
                                size, size);

            cv::Mat tileSrcImg    = image(tileRect).clone();
            cv::Mat tileSrcWeight = weight(tileRect).clone();

//            cv::imshow("src", tileSrcImg);
//            cv::imshow("wei", tileSrcWeight);

            SPtr<tileElement> te;

            if(!tile_manager->getTile(i, j, te)){

                te = SPtr<tileElement>(new tileElement);

                te->image  = cv::Mat(size, size, CV_8UC3, cv::Scalar::all(0));
                te->weight = cv::Mat(size, size, CV_8UC1, cv::Scalar::all(0));
                memset(te->cors, 0, sizeof(te->cors));
            }

            uint8_t *pSrcWeight = tileSrcWeight.data;
            uint8_t *pDstWeight = te->weight.data;

            for (int i=0; i<=16; ++i) {
                for (int j=0; j<=16; ++j) {
                    int coor_y = i * 16;
                    int coor_x = j * 16;
                    if (i!=0) coor_y--;
                    if (j!=0) coor_x--;

                    if (*(pSrcWeight+size*coor_y+coor_x) >
                        *(pDstWeight+size*coor_y+coor_x)  )
                        te->cors[i][j] = dem.img_h[h_][i][j];
                }
            }

            pSrcWeight = tileSrcWeight.data;
            pDstWeight = te->weight.data;

            pi::Array_<uchar,3> *pSrc = (pi::Array_<uchar,3>*) tileSrcImg.data;
            pi::Array_<uchar,3> *pDst = (pi::Array_<uchar,3>*) te->image.data;

            for(int ih=0; ih<size; ih++)
            {
                for(int iw=0; iw<size; iw++)
                {
                    if( *pSrcWeight > *pDstWeight )
                    {
                        *pDst = *pSrc;
                        *pDstWeight = *pSrcWeight;
                    }

                    pSrc++;
                    pDst++;
                    pSrcWeight ++;
                    pDstWeight ++;
                }
            }

            te->image.setTo(cv::Scalar::all(0), te->weight == 0);

            tile_manager->setTile(i, j, te);

//            cv::imshow("te_image", te->image);
//            cv::waitKey(-1);

            ++h_;
        }
    }
    return 0;
}
