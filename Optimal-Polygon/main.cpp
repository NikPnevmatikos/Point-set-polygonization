#include "incremental.h"
#include "convexHull.h"
#include "localSearch.h"
#include "simulatedAnnealing.h"
#include "convertfile.h"
#include <string.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <chrono>

typedef K::Point_2 Point_2;
typedef vector<Point_2> Points;

using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    M   A   I   N  

int main (int argc, char **argv) {

    auto start = chrono::high_resolution_clock::now();

    string inputfile;
    string outfile;
    string polygonInit; 
    int edge_selection = 0;
    string initialization;
    //////////////////////////////////////////

    string algorithm;
    string maxmin;
    int L;
    double threshold;


    // arguments can be accepted in any order
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-i") == 0) {
            if (inputfile.empty() == false) {
                perror("-i argument is given more than 1 times.\n");
                exit(1);
            }
            inputfile = argv[i + 1];
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (outfile.empty() == false) {
                perror("-o argument is given more than 1 times.\n");
                exit(1);
            }
            outfile = argv[i + 1];;

        }
        else if (strcmp(argv[i], "-polygonInit") == 0) {
            if (polygonInit.empty() == false) {
                perror("-polygonInit argument is given more than 1 times.\n");
                exit(1);
            }
            polygonInit = argv[i + 1];

        }
        else if (strcmp(argv[i], "-edge_selection") == 0) {
            if (edge_selection != 0) {
                perror("-edge_selection argument is given more than 1 times.\n");
                exit(1);
            }
            edge_selection = atoi(argv[i + 1]);

        }
        else if (strcmp(argv[i], "-initialization") == 0) {
            if (initialization.empty() == false) {
                perror("-initialization argument is given more than 1 times.\n");
                exit(1);
            }
            initialization = argv[i + 1];

        }
        else if (strcmp(argv[i], "-algorithm") == 0) {
            if (algorithm.empty() == false) {
                perror("-initialization argument is given more than 1 times.\n");
                exit(1);
            }
            algorithm = argv[i + 1];

        }
        else if (strcmp(argv[i], "-max") == 0) {
            if (maxmin.empty() == false) {
                perror("-initialization argument is given more than 1 times.\n");
                exit(1);
            }
            maxmin = "max";
            i--;

        }
        else if (strcmp(argv[i], "-min") == 0) {
            if (maxmin.empty() == false) {
                perror("-initialization argument is given more than 1 times.\n");
                exit(1);
            }
            maxmin = "min";
            i--;

        }
        else if (strcmp(argv[i], "-L") == 0) {
            if (L != 0) {
                perror("-edge_selection argument is given more than 1 times.\n");
                exit(1);
            }
            L = atoi(argv[i + 1]);

        }
        else if (strcmp(argv[i], "-threshold") == 0) {
            if (threshold != 0) {
                perror("-edge_selection argument is given more than 1 times.\n");
                exit(1);
            }
            threshold = atof(argv[i + 1]);

        }
        else {
            perror("Unknown command given\n");
            exit(1);
        }
    }


    Points points;
    
    ifstream file;
    cout << inputfile << endl;
    open_file(file, inputfile);
    
    // extract convex hull area and 2d points from file
    long convex_hull_area = get_points(file, points);

    Polygon_2 result;
    double area; 
    if (polygonInit.compare("incremental") == 0) {
        result = incremental(points, initialization, edge_selection, &area);
    }
    else if(polygonInit.compare("convex_hull") == 0){
        result = convex_hull(points, edge_selection, &area);
    }
    


    // //write to file
    // cout << "Writing result to " << outfile << "." << endl;
    // write_file(outfile, result, polygonInit, edge_selection, initialization, area, convex_hull_area, duration);
    
    // cout << "Successfully wrote results to file " << outfile << "!" << endl;

    //////////////////////////////////////////////////////////////////////////////
    // ergasia 2
    double initarea = area;
    if (algorithm.compare("local_search")== 0){
        if (maxmin.compare("max") == 0) {
            result = localSearch_max(result, threshold, L, &area);
        }
        else {
            result = localSearch_min(result, threshold, L, &area);
        }
    }
    else {
        result = simulatedAnnealing(result, threshold, L, &area);
    }


    auto stop = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int duration = duration1.count();

    // write to file
    cout << "Writing result to " << outfile << "." << endl;
    write_file(outfile, result, algorithm, maxmin, initarea, area, convex_hull_area, duration);
    cout << "Successfully wrote results to file " << outfile << "!" << endl;

    return 0;
}









