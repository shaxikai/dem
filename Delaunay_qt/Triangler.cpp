#include "Triangler.h"

std::vector<QPoint> Triangler::convertPts(QPoint &pt)
{
    _pts.push_back(Point(pt.rx(), pt.ry()));
    Delaunay der;
    std::vector<QPoint> pts;
    der.insert(_pts.begin(), _pts.end());
    Delaunay::Finite_faces_iterator fit = der.finite_faces_begin();
    for (; fit != der.finite_faces_end(); ++fit) {
        pts.push_back(QPoint(fit->vertex(0)->point().hx(), fit->vertex(0)->point().hy()));
        //pts.push_back(QPoint(fit->vertex(1)->point().hx(), fit->vertex(1)->point().hy()));
        pts.push_back(QPoint(fit->vertex(1)->point().hx(), fit->vertex(1)->point().hy()));
        //pts.push_back(QPoint(fit->vertex(2)->point().hx(), fit->vertex(2)->point().hy()));
        pts.push_back(QPoint(fit->vertex(2)->point().hx(), fit->vertex(2)->point().hy()));
        //pts.push_back(QPoint(fit->vertex(0)->point().hx(), fit->vertex(0)->point().hy()));
    }
    return pts;
}
