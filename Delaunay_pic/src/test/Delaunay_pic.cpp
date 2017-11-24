#include <fstream>
#include <sstream>
#include <qapplication.h>

#include <CoordinateTrans.h>
#include <SPtr.h>
#include <GSLAM/core/GPS.h>

#include "Display.h"
#include "Triangler.h"
#include "Display_qgl.h"
#include "Points_filter.h"

//#include <Glog.h>

//#include "MapFusion.h"

struct Frame
{
    cv::Mat img;
    std::vector<cv::Point2d> ptsCv;
    std::vector<qglviewer::Vec> ptsQgl;

};

Frame frame;

class CameraPinhole
{
public:
    CameraPinhole():fx(0),fy(0),cx(0),cy(0),fx_inv(0),fy_inv(0){}
    CameraPinhole(int _w,int _h,double _fx,double _fy,double _cx,double _cy)
        :w(_w),h(_h),fx(_fx),fy(_fy),cx(_cx),cy(_cy),fx_inv(1./_fx),fy_inv(1./_fy)
    {}
    std::string CameraType(){return "PinHole";}

    bool isValid(){return w>0&&h>0&&fx!=0&&fy!=0;}

    Point2d Project(const Point3d& p3d)
    {
        if(p3d.z==1.)
        {
            return Point2d(fx*p3d.x+cx,fy*p3d.y+cy);
        }
        else
        {
            double z_inv=1./p3d.z;
            return Point2d(fx*z_inv*p3d.x+cx,fy*z_inv*p3d.y+cy);
        }
    }

    Point3d UnProject(const Point2d& p2d)
    {
        return Point3d((p2d.x-cx)*fx_inv,(p2d.y-cy)*fy_inv,1.);
    }

    int32_t w,h;
    double fx,fy,cx,cy,fx_inv,fy_inv;
};

int delaunayPic() {
    string datapath = "./mavic-library";

    ifstream ifs("./mavic-library/mapfusion.txt");
    if(!ifs.is_open()) {
        cerr << "Can't open mapfusion file.\n";
        return -1;
    }

    string line;
    SPtr<mf::CoordinateTrans> trans;
    pi::SO3d                  ecef2local;
    int count = 0;
    while(getline(ifs, line)) {
        count ++;

        line.erase(std::remove(line.begin(),line.end(),','),line.end());
        stringstream sst(line);

        // timestamp
        string timestamp;
        sst >> timestamp;
        int l = timestamp.length();
        string imgNum = timestamp.substr(l-7, 3);

        // img
        string imgfile = datapath + "/images/DJI_0" + imgNum + ".JPG";
        frame.img=cv::imread(imgfile);

        // pose
        pi::SE3d pose;
        sst >> pose;
        pi::Point3d t = pose.get_translation();
        pi::SO3d    r = pose.get_rotation();

        pi::Point3d lla = GSLAM::GPS<>::XYZ2GPS(t);
        if(!trans)
        {
            trans = SPtr<mf::CoordinateTrans>(new mf::CoordinateTrans(lla.y, lla.x));
            double D2R = 3.1415925/180.;
            double lon = lla.y * D2R;
            double lat = lla.x * D2R;
            GSLAM::Point3d up(cos(lon)*cos(lat), sin(lon)*cos(lat), sin(lat));
            GSLAM::Point3d east(-sin(lon), cos(lon), 0);
            GSLAM::Point3d north=up.cross(east);
            double R[9]={east.x, north.x, up.x,
                         east.y, north.y, up.y,
                         east.z, north.z, up.z};
            ecef2local.fromMatrix(R);
            ecef2local = ecef2local.inv();
        }

        r = ecef2local * r;

        pi::SE3d curPose;
        curPose.get_rotation().FromEuler(r.getPitch(), r.getYaw(), r.getRoll());
        pi::Point3d& t_ = curPose.get_translation();
        trans->getXYfromLngLat(lla.y, lla.x, t_.x, t_.y);
        t_.z = lla.z - (400);



        // camera parameters
        int camNum;
        sst >> camNum;
        double camPara[6];
        for (int i = 0; i < camNum; ++i) {
            sst >> camPara[i];
        }
        CameraPinhole camera(camPara[0], camPara[1], camPara[2],
                             camPara[3], camPara[4], camPara[5]);


        // points cloud
        Point3d sparsePtc;
        vector<Point2d> pointPixs;
        vector<Point3d> pointClouds;
        int ptNum;
        sst >> ptNum;

        for (int i = 0; i < ptNum; ++i) {
            double depth, x, y, s;
            sst >> x >> y >> depth >> s;
            pointPixs.push_back(camera.Project(Point3d(x, y, 1.0)));
            sparsePtc = Point3d(x, y, depth);
            pointClouds.push_back(curPose*(Point3d(sparsePtc.x, sparsePtc.y, 1.0) / sparsePtc.z));
        }

        Points_filter ptsFilter(pointPixs, pointClouds);
        ptsFilter.ptsFilter();
        pointClouds.clear();
        pointPixs.clear();
        pointClouds = ptsFilter.pointClouds;
        pointPixs   = ptsFilter.pointPixs;



        {
//            for (int i = 0; i < ptNum; ++i) {
//                Point2d pointPix;
//                double depth, x, y, s;
//                sst >> x >> y >> depth >> s;
//                pointPix = camera.Project(Point3d(x, y, 1.0));
//                int j = 0;
//                for (; j<pointPixs.size(); ++j)
//                    if ((int)pointPixs[j].x==(int)pointPix.x && (int)pointPixs[j].y==(int)pointPix.y) break;
//                if (j == pointPixs.size()) {
//                    pointPixs.push_back(pointPix);
//                    sparsePtc.push_back(Point3d(x, y, depth));
//                }
//            }

//            //cout << ptNum << endl;
//            //cout << pointPixs.size() << endl;


//            pointClouds.resize(sparsePtc.size());
//            for (int i=0; i<pointClouds.size(); i++) {
//                Point3d& pt=sparsePtc[i];
//                pointClouds[i] = curPose*(Point3d(pt.x, pt.y, 1.0) / pt.z);
//                //cout << pointClouds[i] << endl;
//            }


//            vector<int> id;
//            for (int i=0; i<pointClouds.size(); ++i) {
//                for (int j=0; j<pointClouds.size(); ++j) {
//                    if (i!=j && (int)pointClouds[i].x==(int)pointClouds[j].x && (int)pointClouds[i].y==(int)pointClouds[j].y) {
//                        if (pointClouds[i].z > pointClouds[j].z) id.push_back(j);
//                        else id.push_back(i);
//                    }
//                }
//            }
//            sort(id.begin(), id.end());
//            id.erase(unique(id.begin(), id.end()), id.end());


//            int i_ = 0;
//            for(vector<Point3d>::iterator it=pointClouds.begin(); it!=pointClouds.end();) {
//                if (i_ == id.size()) break;
//                if ((int)(*it).x==(int)pointClouds[id[i_]-i_].x && (int)(*it).y==(int)pointClouds[id[i_]-i_].y) {
//                    it=pointClouds.erase(it);
//                    ++i_;
//                } else { ++it; }
//            }

//            i_ = 0;
//            for(vector<Point2d>::iterator it=pointPixs.begin(); it!=pointPixs.end();) {
//                if (i_ == id.size()) break;
//                if ((int)(*it).x==(int)pointPixs[id[i_]-i_].x && (int)(*it).y==(int)pointPixs[id[i_]-i_].y) {
//                    it=pointPixs.erase(it);
//                    ++i_;
//                } else { ++it; }
//            }
        }

        //cout << pointClouds.size() << endl;


        std::vector<Point> pt;
        for (int i=0; i<pointPixs.size(); ++i) {
            pt.push_back(Point(pointPixs[i].x, pointPixs[i].y));
        }
        Triangler T;
        T.triPts(pt);

        for (int i=0; i<T.pts.size(); ++i) {
            frame.ptsCv.push_back(cv::Point2d(T.pts[i].hx(), T.pts[i].hy()));
        }


//        Display_cv D;
//        D.show(frame.img, frame.ptsCv);

        for (int i=0; i<T.id.size(); ++i) {
            frame.ptsQgl.push_back(qglviewer::Vec(pointClouds[T.id[i]].x, pointClouds[T.id[i]].y, pointClouds[T.id[i]].z));
        }


        if (count == 1) break;
    }


}


int main(int argc, char** argv)
{
    delaunayPic();

    QApplication application(argc, argv);
    //google::SetLogDestination(google::INFO, "log_");

    Display_qgl D_qgl;
    D_qgl.setWindowTitle("simpleViewer");
    D_qgl.input(frame.ptsQgl, frame.ptsCv, frame.img);
    D_qgl.show();

    return application.exec();
}
