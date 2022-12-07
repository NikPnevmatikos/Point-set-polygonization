#include <CGAL/Simple_cartesian.h>
#include <vector>
#include <string>
#include <iostream>
#include <CGAL/Polygon_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;

using namespace std;

void open_file(ifstream &, string);
int get_points(ifstream &, vector<Point_2> &);
void write_file(string, Polygon_2, string,string, double , double, double, int);