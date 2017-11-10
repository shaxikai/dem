#ifndef TRIANGLER_H
#define TRIANGLER_H

#include "MyWidget.h"

#include <vector>
#include <QPoint>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;
typedef Delaunay::Point Point;


class Triangler
{
public:
    Triangler(){}
    ~Triangler(){}


    std::vector<QPoint> convertPts(QPoint& pt);

private:
    std::vector<Point> _pts;


};

#endif // TRIANGLER_H
