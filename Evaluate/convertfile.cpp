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

long get_points(ifstream& myfile, vector<Point_2> &P_v) {

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

    return stol(number);
}

void write_file(string outfile,map<int, vector<double>> result, map<int, vector<double>> second) {
    ofstream MyFile(outfile);

    MyFile << "\t\t||\t\t\t  incremental /  local_step\t\t\t ||";
    MyFile << "\t\t\t  convex hull / global_step\t\t\t  ||" << endl;
    MyFile << "size    || min score | max score | min bound | max bound ||";
    MyFile << " min score | max score | min bound | max bound ||" << endl;

    map<int, vector<double>>::iterator it;
    for (it = result.begin(); it != result.end(); ++it) {
        MyFile << it->first;
        for(int i = 0; i < 8 - to_string(it->first).length(); i++){
            MyFile << " ";
        }
        MyFile << "||";
        for (int i = 0; i < it->second.size(); i++){
            MyFile << to_string(it->second[i]);
            for(int j = 0; j < 11 - to_string(it->second[i]).length(); j++){
                MyFile << " ";
            }
            MyFile << "|";
        }
        MyFile << "|";

        for (int i = 0; i < second[it->first].size(); i++){
            MyFile << to_string(second[it->first][i]);
            for(int j = 0; j < 11 - to_string(second[it->first][i]).length(); j++){
                MyFile << " ";
            }
            MyFile << "|";
        }
        MyFile << "|" << endl;
        
    }
 
}