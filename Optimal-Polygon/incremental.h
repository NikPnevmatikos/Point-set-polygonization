#include <CGAL/Simple_cartesian.h>
#include <vector>
#include <iostream>
#include <CGAL/Polygon_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
 
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef K::Triangle_2 Triangle_2;

using namespace std;

Polygon_2 create_convex(Point_2, Polygon_2, int, int);

bool is_visible(Segment_2, Segment_2, Polygon_2); 

Polygon_2 incremental(vector<Point_2>,string, int, double*);
