#include <CGAL/Simple_cartesian.h>
#include <vector>
#include <iostream>
#include <CGAL/Polygon_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/Search_traits_2.h>
#include <CGAL/Fuzzy_iso_box.h>
 
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef K::Triangle_2 Triangle_2;
//typedef CGAL::Simple_cartesian<double> sc;
typedef CGAL::Search_traits_2<K> Traits;
typedef CGAL::Kd_tree<Traits> Kd_Tree;
typedef CGAL::Fuzzy_iso_box<Traits> Fuzzy_iso_box;

using namespace std;
 

Polygon_2 simulatedAnnealing(Polygon_2, int,double,string, double*,int);
Polygon_2 simulatedAnnealing_global(Polygon_2, int,double,string, double*, int);
Polygon_2 simulatedAnnealing_subdivision(vector<Point_2>,int,double,string, double*);