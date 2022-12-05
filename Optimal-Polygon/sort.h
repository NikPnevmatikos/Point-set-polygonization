#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

bool decreasing_x(Point_2, Point_2);

bool increasing_x(Point_2, Point_2);

bool decreasing_y(Point_2, Point_2);

bool increasing_y(Point_2, Point_2);