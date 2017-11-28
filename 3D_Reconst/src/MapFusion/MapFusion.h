#ifndef MAPFUSION
#define MAPFUSION

/**
  The MapFusion interface is the base class for both 2D and 3D Fusion.
  It handles keyframe images to generate 2D ortho-image map patches or 3D pointcloud and textures.

  #1. Input
  The Map2DFusion input several FusionFrames and one FusionFrame contains image, depth, pose, and camera parameters .etc.

  ##1.1. Pose
  It mainly support 2 types of Pose expression: GPS&RELATIVE.
  When GPS information available, the pose includes GPS position with WGS84 coordinates and rotation with Eular Angle in radius.
  When GPS information not available, the pose includes the relative position and rotation with Eular Angle in radius with UNKOWN SCALE.

  DEFINATION OF [YAW ROLL PITCH]
  yaw:   forward right
  roll:  rightward down
  pitch: forward up

  [yaw roll pitch] to|from quaternion [rx ry rz w]:
  @code

  @endcode

  [yaw roll pitch] to|from rotation matrix:
  @code

  @endcode

  ##1.2. Image
  The Images are represented with GImage, a tiny implementation of cv::Mat,
  which enables fast transfer from and to any other Image data structs and only depends on the standard library.
  The users can use the following code to convert GImage from|to cv::Mat.
  \code
    cv::Mat GImage2Mat(GImage& gimage)// fast operation, no copy
    {
        if(gimage.empty())  return cv::Mat();
        cv::Mat img(gimage.rows,gimage.cols,gimage.type(),gimage.getDataCopy(false));
        return img;
    }

    GSLAM::GImage GImagefromMat(const cv::Mat& mat)// deep copy of image
    {
        if(mat.empty()) return GSLAM::GImage();
        else return GSLAM::GImage(mat.cols,mat.rows,mat.type(),mat.data,true);
    }
  \endcode

  ##1.3. Depth
  The class FusionDepth is use to represent the dense and sparse Depth for one frame.

  ##1.4. CameraModel
  PINHOLE:  width height fx fy cx cy
  ATAN:     width height fx fy cx cy w
  OPENCV:   width height fx fy cx cy k1 k1 p1 p2 [k3]

  for a PINHOLE camera, $x_{img}= x_{camera}*fx+cx$.

  #2. Coordinates
  Generally the input type FUSION_GPS_SPARSE_PINHOLE offers camera position in WGS84 coordinates.
  Users can use the class CoordinateTrans to convert the WGS84 to|from local XYZ:
  @code
    CoordinateTrans trans(lngRef,latRef);
    // convert lng&lat to x&y
    double x,y;
    trans.getXYfromLngLat(lng,lat,x,y);

    // convert x&y to lng&lat
    trans.getLngLatfromXY(x,y,lng,lat);
  @endcode

  #3. Usage of MapFusion



**/
#include <iostream>
#include <vector>
#include <memory>
#include <functional>

#include "GImage.h"
#include "CoordinateTrans.h"
#include "Point.h"
#include "SPtr.h"
#include "SE3.h"


namespace mf{

typedef pi::Point2f Point2f;
typedef pi::Point2d Point2d;
typedef pi::Point3d Point3d;
typedef pi::Point3f Point3f;
typedef pi::Point3ub Point3ub;

enum FusionFrameFlags{
    FUSION_POSE_GPS     =0x1<<0,    // Pose type: 1--GPS 0--Relative
    FUSION_DEPTH_DENSE  =0x1<<1,    // Depth type: 1--Dense 0--Sparse

    // Camera type: 0--PINHOLE 1--ATAN 2--OPENCV
    FUSION_CAM_PINHOLE  =0x0<<2,
    FUSION_CAM_ATAN     =0x1<<2,
    FUSION_CAM_OPENCV   =0x2<<2,

    FUSION_GPS_DENSE_PINHOLE    = FUSION_POSE_GPS|FUSION_DEPTH_DENSE|FUSION_CAM_PINHOLE,
    FUSION_GPS_SPARSE_PINHOLE   = FUSION_POSE_GPS|FUSION_CAM_PINHOLE,
    FUSION_RELATIVE_SPARSE_PINHOLE= FUSION_CAM_PINHOLE
};

struct FusionPose {
//    union {double x;double lng;};
//    union {double y;double lat;};
//    union {double z;double alt;};
    double lng,lat,alt;
    float  yaw,roll,pitch;
};

struct PixelDepth{
    PixelDepth(Point2f position,const double& d,const double& iVar=-1)
        :pt(position),depth(d),sigma(iVar){}

    Point2f  pt;
    double   depth,sigma;
};

struct FusionDepth {
    FusionDepth():factor(1.){}

    double                  factor;
    GImage                  denseDepth;
    std::vector<PixelDepth> sparseDepth;
};

// The input stream of MapFusion
struct FusionFrame {
    int                 type;       // bit0--Pose Type, bit1--Depth Type, bit2-3--Camera Type, bit
    double              timestamp;  // Timestamp in UTC seconds
    FusionPose          pose;       // GPS or RELATIVE
    GImage              img;
    FusionDepth         depth;      // Dense and Sparse
    std::vector<double> camPara;    // Camera parameters
};

// The output stream of MapFusion
class MapFusionCallBackData
{
public:
    virtual ~MapFusionCallBackData(){}
    virtual std::string type(){return "CallBackNone";}
};

class MapFusionOrthoPatch: public MapFusionCallBackData
{
public:
    virtual ~MapFusionOrthoPatch(){}
    virtual std::string type(){return "MapFusionOrthoPatch";}

    bool operator <(const MapFusionOrthoPatch& rh)const
    {
        //return lat<rh.alt?:(lat==rh.alt&&lng<rh.lng);   // FIXME: wrong
        return lat<rh.lat?:(lat==rh.lat&&lng<rh.lng);
    }

    double  timestamp;  //update time, in UTC seconds
    double  lng,lat,alt;//top-left position
    float   pixelSize;  //pixel size in meters
    GImage  img;        //ortho image, channels=3--rgb 4--rgba 5--rgb-d-alt
};

class MapFusionTile: public MapFusionCallBackData
{
public:
    virtual ~MapFusionTile(){}
    virtual std::string type(){return "MapFusionTile";}

    bool operator <(const MapFusionTile& rh)const
    {
		//return lat<rh.lat?:(lat==rh.lat&&lng<rh.lng);
		return y > rh.y ?:(y==rh.y&& x < rh.x );
    }

    double  timestamp;      ///< update time, in UTC seconds
    int     x, y, zoom;     ///< tile x, y, zoom level
    float   pixelSize;      ///< pixel size in meters
    GImage  img;            ///< ortho image, channels=3--rgb 4--rgba 5--rgb-d-alt
    GImage  DME;            ///< DME data
};

class MapFusionPointCloud: public MapFusionCallBackData
{
public:
    template <typename T,int Size>
    class MapFusionVec
    {
    public:
        T data[Size];
    };

    virtual std::string type(){return "MapFusionPointCloud";}

    FusionPose                          pose;
    std::vector<MapFusionVec<float,3> > points,normals;
    std::vector<MapFusionVec<uchar,3> > colors;
};

typedef std::function<void(MapFusionCallBackData*)> MapFusionCallBack;// Callback Function, need to be free outside

// Base class interface of MapFusion, include 3D&2D
class MapFusion
{
public:
    MapFusion():cbk(NULL){}                                     //
    virtual ~MapFusion(){}

    virtual std::string type(){return "MapFusionNone";}

    virtual bool valid(){return false;}                         // whether if this Map2DFusion usable
    virtual void draw(){}                                       // Plot things with OpenGL
    virtual bool feed(FusionFrame* frame){return false;}        // Feed a FusionFrame, need to be free inside of the MapFusion
    virtual void call(const std::string& cmd,void* ptr=NULL){}  // arbituary call fuction

    virtual bool getTile(const int x, const int y, const int z, SPtr<MapFusionTile>& tile) { return false; }

    void setCallBack(MapFusionCallBack callback){cbk=callback;}

protected:
    MapFusionCallBack cbk;
};

} // end of namespace mf

/// create and release function, create when system is not NULL and release when system is NULL
typedef SPtr<mf::MapFusion> (*createMapFusionFunction)();
extern "C"
{
SPtr<mf::MapFusion> createMapFusion();
}


#endif // MAPFUSION

