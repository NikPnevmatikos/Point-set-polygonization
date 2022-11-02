#include <CGAL/Simple_cartesian.h>
#include <vector>
#include <string>
#include <iostream>
#include <CGAL/intersections.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

void open_file(ifstream &, string);
void get_points(ifstream &, vector<Point_2> &);