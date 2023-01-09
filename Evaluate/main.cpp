#include "incremental.h"
#include "convexHull.h"
#include "localSearch.h"
#include "simulatedAnnealing.h"
#include "convertfile.h"
#include <string.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <chrono>
#include <map>
#include <iterator>
#include <dirent.h>

typedef K::Point_2 Point_2;
typedef vector<Point_2> Points;

using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    M   A   I   N  

int main (int argc, char **argv) {

    auto start = chrono::high_resolution_clock::now();

    string inputfile;
    string outfile;

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
        else {
            perror("Unknown command given\n");
            exit(1);
        }
    }

    map<int, vector<double>> first;
    map<int, vector<double>> second;
    struct dirent *de;
	DIR *dr = opendir(inputfile.c_str());

	while ((de = readdir(dr)) != NULL){
        if(strcmp(de->d_name, "..") == 0){//without these two if directories will go back and forth infinate
            continue;
        }
        if(strcmp(de->d_name, ".") == 0){
            continue;
        }
        cout << de->d_name << endl;
    
        Points points;
        
        ifstream file;
        string filename = inputfile + "/" + de->d_name;
        cout << filename << endl;
        open_file(file, filename);
        
        // extract convex hull area and 2d points from file
        long convex_hull_area = get_points(file, points);

        Polygon_2 result;
        double area; 

        cout << "Starting incremental algorithm" <<endl;
    
        result = incremental(points, "1b", 3, &area);
        //result = convex_hull(points, edge_selection, &area);


        cout << "Starting Local Step algorithm" <<endl;
        
        double initarea = area;
                
        //result = localSearch_max(result, threshold, L, &area);

        //result = localSearch_min(result, threshold, L, &area);

        result = simulatedAnnealing(result, 100, convex_hull_area, "max", &area);

        //result = simulatedAnnealing_global(result,L,convex_hull_area,maxmin, &area);

        //result = simulatedAnnealing_subdivision(points, L, convex_hull_area,maxmin, &area);
        double max_score = area/convex_hull_area;
        area = 0.0;
        result = incremental(points, "1b", 2, &area);
        result = simulatedAnnealing(result, 100, convex_hull_area, "min", &area);

        double min_score = area/convex_hull_area;

        if (first.find(points.size()) == first.end()){
            vector<double> scores{ min_score , max_score , min_score , max_score};
            first[points.size()] = scores; 
        }
        else{
            (first[points.size()])[1] += max_score;
            (first[points.size()])[1] += min_score;
            if (max_score < (first[points.size()])[3]){
                (first[points.size()])[3] = max_score;
            }
            if(min_score < (first[points.size()])[2]){
                (first[points.size()])[2] = min_score;
            }
        }

        area = 0.0;
        result = convex_hull(points, 3, &area);
        result = simulatedAnnealing_global(result,100,convex_hull_area,"max", &area);
        max_score = area/convex_hull_area;

        area = 0.0;
        result = convex_hull(points, 2, &area);
        result = simulatedAnnealing_global(result,100,convex_hull_area,"min", &area);
        min_score = area/convex_hull_area;

        if (second.find(points.size()) == second.end()){
            vector<double> scores{ min_score , max_score , min_score , max_score};
            second[points.size()] = scores; 
        }
        else{
            (second[points.size()])[1] += max_score;
            (second[points.size()])[1] += min_score;
            if (max_score < (second[points.size()])[3]){
                (second[points.size()])[3] = max_score;
            }
            if(min_score < (second[points.size()])[2]){
                (second[points.size()])[2] = min_score;
            }
        }


        // auto stop = chrono::high_resolution_clock::now();
        // auto duration1 = chrono::duration_cast<chrono::milliseconds>(stop - start);

        // int duration = duration1.count();
    
    }

    cout << "Writing result to " << outfile << "." << endl;
    write_file(outfile, first, second);
    cout << "Successfully wrote results to file " << outfile << "!" << endl;
    return 0;
}









