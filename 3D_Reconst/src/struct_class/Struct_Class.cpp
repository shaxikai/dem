#include "Struct_Class.h"

std::vector<int>  Frame::pt_getNeipts(int id) {
    std::vector<int> neiPts;
    for (int i=0; i<tris.size(); ++i) {
        if(id == tris[i].c_1) {
            neiPts.push_back(tris[i].c_2);
            neiPts.push_back(tris[i].c_3);
        } else if (id == tris[i].c_2) {
            neiPts.push_back(tris[i].c_1);
            neiPts.push_back(tris[i].c_3);
        } else if (id == tris[i].c_3){
            neiPts.push_back(tris[i].c_1);
            neiPts.push_back(tris[i].c_2);
        }
    }
    std::sort(neiPts.begin(), neiPts.end());
    neiPts.erase(std::unique(neiPts.begin(), neiPts.end()), neiPts.end());
    return neiPts;
}

std::vector<int> Frame::pt_getTris(int id) {
    std::vector<int> tris_id;
    for (int i=0; i<tris.size(); ++i) {
        if (id == tris[i].c_1 || id == tris[i].c_2 || id == tris[i].c_3) {
            tris_id.push_back(i);
        }
    }
    return tris_id;
}


