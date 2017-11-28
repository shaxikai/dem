#ifndef TRIANGLER_H
#define TRIANGLER_H

#include <Point.h>
#include <vector>
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

    void triPts(std::vector<Point> & pt);


    std::vector<int>        id;
    std::vector<Point>      pts;
    int                     triNum;

};

#endif // TRIANGLER_H
