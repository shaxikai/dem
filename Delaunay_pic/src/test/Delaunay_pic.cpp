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

        // image
        string imgfile = datapath + "/images/DJI_0" + imgNum + ".JPG";
        frame.image=cv::imread(imgfile);

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

        frame.pointClouds = pointClouds;
        frame.pointPixs   = pointPixs;
        Points_filter ptsFilter(frame);
        ptsFilter.ptsPrefilter();
        pointClouds.clear();
        pointPixs.clear();
        frame = ptsFilter.frame;

        std::vector<Point> pt;
        for (int i=0; i<frame.pointPixs.size(); ++i) {
            pt.push_back(Point(frame.pointPixs[i].x, frame.pointPixs[i].y));
        }

        Triangler T;
        T.triPts(pt);
        frame.tris = T.tris;

        int l_ = 1;
        while(l_--)
        {
            ptsFilter.setFrame(frame);
            l_ =ptsFilter.ptsOutfilter();
            frame = ptsFilter.frame;

            std::vector<Point> pt;
            for (int i=0; i<frame.pointPixs.size(); ++i) {
                pt.push_back(Point(frame.pointPixs[i].x, frame.pointPixs[i].y));
            }

            Triangler T;
            T.triPts(pt);
            frame.tris = T.tris;
        }


        int h_ = 1;
        while(h_--)
        {
            for (int i=0; i<frame.pointClouds.size(); ++i) {
                vector<int> neiPts = frame.pt_getNeipts(i);
                if (neiPts.size()>5) {
                    vector<double> neiPts_h;
                    int size = neiPts.size();
                    for (int j=0; j<size; ++j) {
                        neiPts_h.push_back(frame.pointClouds[neiPts[j]].z);
                        sort(neiPts_h.begin(), neiPts_h.end());
                    }
                    if (size%2 == 0)
                        frame.pointClouds[i].z = 0.5 * (neiPts_h[size/2] + neiPts_h[size/2-1]);
                    else
                        frame.pointClouds[i].z = neiPts_h[size/2];
                }
            }
        }



        Display_cv D(frame);
        D.frame2dem();


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
    D_qgl.input(frame);
    D_qgl.show();

    return application.exec();
}
