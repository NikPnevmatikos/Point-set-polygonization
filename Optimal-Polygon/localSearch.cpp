#include "localSearch.h"


//~~~~~~~~~~~~~~~~~~~~~~  L O C A L   S E A R C H   F O R   M A X I M U M   A R E A 

Polygon_2 localSearch_max(Polygon_2 pol, double threshold, int k, double* resultarea) {

    // Polygon_2 pol;
    // pol.push_back(Point_2(2,2));
    // pol.push_back(Point_2(2,5));
    // pol.push_back(Point_2(0,7));
    // pol.push_back(Point_2(4,6));
    // pol.push_back(Point_2(6,5));
    // pol.push_back(Point_2(7,5));
    // pol.push_back(Point_2(9,8));
    // pol.push_back(Point_2(11,2));
    // pol.push_back(Point_2(8,1));
    // pol.push_back(Point_2(4,3));

    double Da = *resultarea;
    Polygon_2 max = pol;

    while (Da >= threshold) {
        
        for (const Segment_2& e : pol.edges()) {

            const Polygon_2::Vertices& range = pol.vertices();
            int start, end, counter = 0;
            
            // iterator for all the edges of the polygon except the k-1 last ones
            // cause then the blueline can create problems with the start and the end
            // of the polygon 
            for (auto it = range.begin(); it != range.end()-(k-1); it++) {
                Polygon_2 copy = pol;
                vector<Point_2> blueline;

                bool flag = false;
                start = counter;                                    // starting point of the blue line
                end = counter + (k-1);                              // ending point of the blue line
                
                // create the blueline
                for (int i = 0; i < k; i++) {
                    // if any point of the blue line has the same point with the 
                    // edge, break
                    if ((*(it+i) == e.target()) || (*(it+i) == e.source())) {
                        flag = true;
                        break;
                    }   
                    blueline.insert(blueline.begin()+0, *(it+i));
                }

                // can't create the blue line
                if (flag) {
                    counter++;
                    continue;
                }

                // erase the blue line from the polygon
                copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+end+1);

                int insert = 0;
                int j = 0;
                // insert the blue line, starting from the target of the edge
                for (const Point_2& p : copy.vertices()) {
                    if (p == Point_2(e.target())) {
                        copy.insert(copy.vertices_begin() + j, blueline.begin(), blueline.end());
                        break;
                    }
                    j++;
                }

                // if the polygon is still simple and the new polygon 
                // has a greater area than before, then it's the new max
                if (copy.is_simple() == true) { 
                    if (abs(copy.area()) > abs(max.area())) {
                        max = copy;
                    }
                }
                      
                counter++;
            }
            
        }
        // max area of the polygon has been found 
        // if Da is reached, stop, else continue
        if (max.area() - pol.area() == Da) {
            break;
        }
        Da = max.area() - pol.area();
        pol = max;
    }

    pol = max;

    *resultarea = abs(pol.area());

    return pol;
}





//~~~~~~~~~~~~~~~~~~~~~~  L O C A L   S E A R C H   F O R   M I N I M U M   A R E A 

Polygon_2 localSearch_min(Polygon_2 pol, double threshold, int k, double* resultarea) {

    double Da = *resultarea;
    Polygon_2 min = pol;
    while (Da >= threshold) {
        
        for (const Segment_2& e : pol.edges()) {
            const Polygon_2::Vertices& range = pol.vertices();
            int start, end, counter = 0;
            
            // iterator for all the edges of the polygon except the k-1 last ones
            // cause then the blueline can create problems with the start and the end
            // of the polygon 
            for (auto it = range.begin(); it != range.end()-(k-1); it++) {
                Polygon_2 copy = pol;
                vector<Point_2> blueline;

                bool flag = false;
                start = counter;                                    // starting point of the blue line
                end = counter + (k-1);                              // ending point of the blue line
                // create the blueline
                for (int i = 0; i < k; i++) {
                    // if any point of the blue line has the same point with the 
                    // edge, break
                    if ((*(it+i) == e.target()) || (*(it+i) == e.source())) {
                        flag =  true;
                        break;
                    }   

                    blueline.insert(blueline.begin()+0,*(it+i));
                }
                
                // can't create the blue line
                if (flag) {
                    counter++;
                    continue;
                }

                // erase the blue line from the polygon
                copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+end+1);

                int insert = 0;
                int j = 0;

                // insert the blue line, starting from the target of the edge
                for (const Point_2& p : copy.vertices()) {
                    
                    if (p == Point_2(e.target())) {
                        copy.insert(copy.vertices_begin() + j, blueline.begin(), blueline.end());
                        break;
                    }
                    j++;
                }
              
                // if the polygon is still simple and the new polygon 
                // has less area than before, then it's the new min
                if (copy.is_simple() == true) { 
                    if (abs(copy.area()) < abs(min.area())) {
                        min = copy;
                    }
                }
                      
                counter++;
            }
            
        }
        // min area of the polygon has been found 
        // if Da is reached, stop, else continue
        if(min.area() -  pol.area() == Da){
            break;
        }
        Da = min.area() -  pol.area();
        pol = min;
    }

    pol = min;

    *resultarea = abs(pol.area());
    return pol;
}