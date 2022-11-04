#include <CGAL/Simple_cartesian.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream> 
#include <iostream>
#include <CGAL/Polygon_2.h>
#include <ctype.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef CGAL::Polygon_2<K> Polygon_2;

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

int get_points(ifstream& myfile, vector<Point_2> &P_v) {

    string str;
    string number = "";
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
        else {
            int pos = str.find("area");
            if(pos != string::npos){
                for (int i = pos; i < str.length(); i++){
                    if(isdigit(str.at(i))){
                        number += str.at(i);
                    }
                }
            }

        }
    }

    return stoi(number);
}

void write_file(string outfile,Polygon_2 result, string algorithm, int edge_selection, string initialization, double area, double convex_area, int duration) {
    ofstream MyFile(outfile);

    for (const Point_2& p : result.vertices()) {
        MyFile << p << endl;
    }

    for (const Segment_2& e : result.edges()) {
        MyFile << e << endl;
    }

    MyFile << "Algorithm: " << algorithm << "_";
    MyFile << "edge_selection " << edge_selection << "_";
    if(initialization.empty() == false){
        MyFile << "initializtion " << initialization;
    }
    MyFile << "\nArea: " << area << endl;
    MyFile << "ratio: " << area/convex_area << endl;
    MyFile << "construction time: " << duration << endl; 
 
}