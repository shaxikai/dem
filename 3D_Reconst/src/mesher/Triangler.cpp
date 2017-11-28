#include <algorithm>

#include "Triangler.h"

void Triangler::triPts(std::vector<Point> &pt)
{
    points = pt;

    Delaunay der;
    der.insert(pt.begin(), pt.end());
    Delaunay::Finite_faces_iterator fit = der.finite_faces_begin();
    for (; fit != der.finite_faces_end(); ++fit) {
        for (int i=0; i<3; ++i)
            pts.push_back(fit->vertex(i)->point());
    }


    tris.resize(pts.size() / 3);
    for (int i=0; i<pts.size(); ++i) {
        for (int j=0; j<pt.size(); ++j) {
            if(pts[i] == pt[j])
            {
                if (i%3 == 0) tris[i/3].c_1 = j;
                if (i%3 == 1) tris[i/3].c_2 = j;
                if (i%3 == 2) tris[i/3].c_3 = j;
            }
        }
    }
    triNum = der.number_of_faces();

}


