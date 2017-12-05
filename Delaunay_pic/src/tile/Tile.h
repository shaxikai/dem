#ifndef TILE_H
#define TILE_H
#include <vector>
#include <memory>
#include <hash_map>
#include <list>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define SPtr std::shared_ptr
#define WPtr std::weak_ptr

using namespace std;

class tileElement
{
public:
    tileElement();
    tileElement(int _x, int _y);

    int64_t hashVal(void)
    {
        return hashVal(x, y);
    }
    static int64_t hashVal(int _x, int _y)
    {
        int64_t i = 0, j = 0;
        if (_x < 0) {i = 1; _x = -_x;}
        if (_y < 0) {j = 1; _y = -_y;}
        int64_t iy = _y, ix = _x;
        int64_t v  = j<<48 | iy<<32 | i<<16 | ix;
        return v;
    }

    int32_t x, y;
    int64_t hashIndex;

    cv::Mat image;
    cv::Mat weight;

    double cors[17][17];

};

typedef __gnu_cxx::hash_map<int64_t, SPtr<tileElement> > TileHash;

class tileManager
{
public :
    tileManager(){}
    virtual ~tileManager(){}


    int getTile(int x, int y, SPtr<tileElement>& te);
    int setTile(int x, int y, SPtr<tileElement>& te);

    TileHash                m_allTile;
    std::list<uint64_t>     m_keyTable;


};

#endif // TILE_H
