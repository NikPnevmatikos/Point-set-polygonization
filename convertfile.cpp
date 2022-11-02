#include <CGAL/Simple_cartesian.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream> 
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

void open_file(ifstream& myfile, string file_name) {
    myfile.open(file_name);
    if (myfile.is_open()) {
        cout << "Succesfully opened file!" << endl;
    }
    else {
        cout << "Failed to open file!" << endl;
        exit(-1);
    }
}

void get_points(ifstream& myfile, vector<Point_2> &P_v) {

    string str;

    while (getline(myfile, str)) {
        if (str.at(0) != '#') {
            stringstream line;
            line << str;
            int ignore, x, y;

            line >> ignore;
            line >> x;
            line >> y;

            P_v.push_back(Point_2(x, y));
        }
    }
}