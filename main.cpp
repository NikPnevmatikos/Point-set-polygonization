#include "incremental.h"
#include "convertfile.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef K::Point_2 Point_2;
typedef vector<Point_2> Points;

using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    M   A   I   N  

int main (int argc, char **argv) {

    Points points;
    
    ifstream file;
    open_file(file, argv[1]);
    
    get_points(file, points);


    for (int i = 0; i < points.size(); i ++) {
        cout << points[i] << endl;
    }
    
    incremental(points);
    
    return 0;
}









