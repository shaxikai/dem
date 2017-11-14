#include "Triangler.h"

void Triangler::triPts(std::vector<Point> &pt)
{


    Delaunay der;
    der.insert(pt.begin(), pt.end());
    Delaunay::Finite_faces_iterator fit = der.finite_faces_begin();
    for (; fit != der.finite_faces_end(); ++fit) {
        for (int i=0; i<3; ++i)
            pts.push_back(fit->vertex(i)->point());


//        pts.push_back(pi::Point2d(fit->vertex(0)->point().hx(), fit->vertex(0)->point().hy()));
//        //pts.push_back(QPoint(fit->vertex(1)->point().hx(), fit->vertex(1)->point().hy()));
//        pts.push_back(pi::Point2d(fit->vertex(1)->point().hx(), fit->vertex(1)->point().hy()));
//        //pts.push_back(QPoint(fit->vertex(2)->point().hx(), fit->vertex(2)->point().hy()));
//        pts.push_back(pi::Point2d(fit->vertex(2)->point().hx(), fit->vertex(2)->point().hy()));
//        //pts.push_back(QPoint(fit->vertex(0)->point().hx(), fit->vertex(0)->point().hy()));
    }
    for (int i=0; i<pts.size(); ++i) {
        for (int j=0; j<pt.size(); ++j) {
            if(pts[i] == pt[j])
                id.push_back(j);
        }
    }
    triNum = der.number_of_faces();
}
