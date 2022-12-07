#include "simulatedAnnealing.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

bool seg_intersect(Segment_2 a, Segment_2 b){
    const auto result = intersection(a, b);

    cout << "a seg is " << a << endl;
    cout << "b seg is " << b << endl;
    if (result) {       // using if statement cause result is not boolean type
        cout << "they instersect " << endl;
        return true;    
    }
    cout << "they dont intersect" << endl;
    return false;
}


bool intersect(Triangle_2 a, vector<Point_2> points) {

    for (int i = 0; i < points.size(); i++) {
        cout << "tri    " << a.bounded_side(points[i]) << " point " << points[i] << endl;
        if (a.bounded_side(points[i]) == 0) {
            bool is_vertex = false;
            for (int j = 0; j < 3; j ++) {
                // cout << a.vertex(j) << " " << points[i] << endl;
                if (a.vertex(j) == points[i]) {
                    is_vertex = true;
                    break;
                }
            }
            if (is_vertex == false) {
                cout << points[i] << endl;
                return true;
            }
        }
        if (a.bounded_side(points[i]) == 1) {
            return true;
        }
    }

    return false;
}


Polygon_2 simulatedAnnealing(Polygon_2 paste, double threshold, int k, double* resultarea) {


    srand (time(NULL));

    Polygon_2 pol;
    pol.push_back(Point_2(1,0));
    pol.push_back(Point_2(1,3));
    pol.push_back(Point_2(3,3));
    //pol.push_back(Point_2(4,2));
    //pol.push_back(Point_2(4,3));
    pol.push_back(Point_2(4,5));
    pol.push_back(Point_2(7,6));
    pol.push_back(Point_2(8,5));
    pol.push_back(Point_2(8,0));
    pol.push_back(Point_2(6,0));
    pol.push_back(Point_2(5,4));
    pol.push_back(Point_2(2,1));

    //int threshold = 1000, k = 3;
    double Da = *resultarea;
    for (const Segment_2& e : pol.edges()) {
        cout << e << endl;
    }

    Polygon_2 copy = pol;
    int randvertex = rand() % (copy.vertices().size()-3) +1;
    cout << "rand pos " << randvertex << endl;
    
    Polygon_2::Vertex_iterator it = copy.vertices_begin();

    Point_2 temp = *(it+randvertex);
    *(it+randvertex) = *(it+randvertex+1); 
    *(it+randvertex+1) = temp;


    cout << "after" << endl;
    for (const Segment_2& e : copy.edges()) {
        cout << e << endl;
    }

    it = copy.vertices_begin();

    Kd_Tree	tree(copy.vertices_begin(), copy.vertices_end());	

    vector<Point_2> result;

    Point_2 first = *(it + randvertex -1); 
    int low_x = first.x(), low_y = first.y(), up_x = first.x() , up_y = first.y();
    for (int i = 0; i < 3; i++) {
        Point_2 point = *(it+randvertex+i); 
        //cout << " point is " << point.x() << " " << point.y() << endl;
        if (point.x() < low_x) {
            low_x = point.x();
        }
        if (point.y() < low_y) {
            low_y = point.y();
        }
        if (point.x() > up_x) {
            up_x = point.x();
        }
        if (point.y() > up_y){
            up_y = point.y();
        }
    }
    cout << low_x << " , " << low_y << endl;
    cout << up_x << " , " << up_y << endl;

    Fuzzy_iso_box approximate_range(Point_2(low_x, low_y), Point_2(up_x, up_y));
    tree.search(back_inserter(result), approximate_range);


    for (int i = 0; i < result.size(); i++) {
        cout << "box    " << result[i] << endl;
    }

    Triangle_2 a(Point_2(*(it + randvertex -1 )),Point_2(*(it + randvertex)),Point_2(*(it + randvertex+1)));
    Triangle_2 b(Point_2(*(it + randvertex)),Point_2(*(it + randvertex +1)),Point_2(*(it + randvertex + 2)));
    Segment_2 seg1(Point_2(*(it + randvertex -1 )), *(it + randvertex));
    Segment_2 seg2(Point_2(*(it + randvertex + 1)), *(it + randvertex + 2 ));


    if (seg_intersect(seg1,seg2) == false && intersect(a, result) == false && intersect(b, result) == false) {     
        cout << "eimai komple sta trigwna mou <3" << endl;
    }
    else {
        cout << "den mporei na ginei allagh" << endl;
    }

    cout << pol.area() << endl;
    cout << copy.area() << endl;

    // if (abs(pol.area()) < abs(copy.area())) {
        
    // }













    // Polygon_2 max = pol;
    // while (Da >= threshold) {
        
    //     for (const Segment_2& e : pol.edges()) {
    //         //Polygon_2 copy = pol;
    //         cout << "----loop---- " << e << endl;
    //         const Polygon_2::Vertices& range = pol.vertices();
    //         int start, end, counter = 0;
            
    //         for (auto it = range.begin(); it != range.end()-(k-1); it++) {
    //             Polygon_2 copy = pol;
    //             vector<Point_2> blueline;
    //             cout << *it << endl;

    //             // auto start = it;
    //             // int i = 0;
    //             bool flag = false;
    //             start = counter;                                    // starting point of the blue line
    //             end = counter + (k-1);                              // ending point of the blue line
    //             for (int i = 0; i < k; i++) {
    //                 //if (i > 0) {
    //                     // if (*(it+i-1) == e.source() && *(it+i) == e.target()) {
    //                     //     flag =  true;
    //                     //     break;
    //                     // }
    //                 if ((*(it+i) == e.target()) || (*(it+i) == e.source())) {
    //                     flag =  true;
    //                     cout << "m[hka" << endl;
    //                     break;
    //                 }   
    //                 //}
    //                 blueline.insert(blueline.begin()+0,*(it+i));
    //             }

    //             if (flag) {
    //                 cout << "nooooo blue line" << endl;
    //                 counter++;
    //                 continue;
    //             }
    //             cout << "blue line" << endl;
    //             cout << "start " << start << endl;
    //             cout << "end " << end << endl;
    //             for (int i = 0; i < blueline.size(); i++) {
    //                 cout << "  " << blueline[i] << endl;
    //             }
    //             cout << "stop blueline" << endl;

    //             // if (copy.vertices_begin()+end == copy.end()) {
    //             //     copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+0);
    //             // }
    //             //else {
    //             copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+end+1);
    //             // }
    //             // for (const Segment_2& e : pol.edges()) {

    //             //     cout <<  " delete     " << e << endl;
    //             // }
    //             //cout << " seg " << seg << endl;
    //             int insert = 0;
    //             //const Polygon_2::Vertices& findvertix = copy.vertices();
    //             int j = 0;
    //             for (const Point_2& p : copy.vertices()) {
                    
    //                 if (p == Point_2(e.target())) {
    //                     //cout << " j and it " << j <<  " " << *(it) << endl;
    //                     copy.insert(copy.vertices_begin() + j, blueline.begin(), blueline.end());
    //                     break;
    //                 }
    //                 j++;
    //             }

    //             for (const Segment_2& e : copy.edges()) {

    //                 cout <<  " posiball     " << e << endl;
    //             }

    //             cout << "copy area" << abs(copy.area()) << endl;
    //             cout << "max area" << abs(max.area()) << endl;
    //             if (copy.is_simple() == true) { 
    //                 if (abs(copy.area()) > abs(max.area())) {
    //                     max = copy;
    //                     cout << "change" << endl;
    //                 }
    //             }
                      
    //             counter++;
    //         }
            
    //     }
    //     pol = max;
    //     if(max.area() -  pol.area() == Da){
    //         break;
    //     }
    //     Da = max.area() -  pol.area();
    // }

    // pol = max;
    // for (const Segment_2& e : pol.edges()) {

    //     cout <<  " final     " << e << endl;
    // }
    // cout << "Max area found " << abs(pol.area()) << endl;

    // *resultarea = abs(pol.area());
    return pol;
}































// Polygon_2 localSearch_min(Polygon_2 pol, double threshold, int k, double* resultarea) {

//     // Polygon_2 pol;
//     // pol.push_back(Point_2(2,2));
//     // pol.push_back(Point_2(2,5));
//     // pol.push_back(Point_2(0,7));
//     // pol.push_back(Point_2(4,6));
//     // pol.push_back(Point_2(6,5));
//     // pol.push_back(Point_2(7,5));
//     // pol.push_back(Point_2(9,8));
//     // pol.push_back(Point_2(11,2));
//     // pol.push_back(Point_2(8,1));
//     // pol.push_back(Point_2(4,3));

//     //int threshold = 1000, k = 3;
//     double Da = *resultarea;
//     for (const Segment_2& e : pol.edges()) {
//         cout << e << endl;
//     }


//     Polygon_2 min = pol;
//     while (Da >= threshold) {
        
//         for (const Segment_2& e : pol.edges()) {
//             //Polygon_2 copy = pol;
//             cout << "----loop---- " << e << endl;
//             const Polygon_2::Vertices& range = pol.vertices();
//             int start, end, counter = 0;
            
//             for (auto it = range.begin(); it != range.end()-(k-1); it++) {
//                 Polygon_2 copy = pol;
//                 vector<Point_2> blueline;
//                 cout << *it << endl;

//                 bool flag = false;
//                 start = counter;                                    // starting point of the blue line
//                 end = counter + (k-1);                              // ending point of the blue line
//                 for (int i = 0; i < k; i++) {

//                     if ((*(it+i) == e.target()) || (*(it+i) == e.source())) {
//                         flag =  true;
//                         cout << "m[hka" << endl;
//                         break;
//                     }   

//                     blueline.insert(blueline.begin()+0,*(it+i));
//                 }

//                 if (flag) {
//                     cout << "nooooo blue line" << endl;
//                     counter++;
//                     continue;
//                 }
//                 cout << "blue line" << endl;
//                 cout << "start " << start << endl;
//                 cout << "end " << end << endl;
//                 for (int i = 0; i < blueline.size(); i++) {
//                     cout << "  " << blueline[i] << endl;
//                 }
//                 cout << "stop blueline" << endl;

//                 copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+end+1);

//                 int insert = 0;
//                 //const Polygon_2::Vertices& findvertix = copy.vertices();
//                 int j = 0;
//                 for (const Point_2& p : copy.vertices()) {
                    
//                     if (p == Point_2(e.target())) {
//                         //cout << " j and it " << j <<  " " << *(it) << endl;
//                         copy.insert(copy.vertices_begin() + j, blueline.begin(), blueline.end());
//                         break;
//                     }
//                     j++;
//                 }

//                 for (const Segment_2& e : copy.edges()) {

//                     cout <<  " posiball     " << e << endl;
//                 }

//                 cout << "copy area" << abs(copy.area()) << endl;
//                 cout << "min area" << abs(min.area()) << endl;
//                 if (copy.is_simple() == true) { 
//                     if (abs(copy.area()) < abs(min.area())) {
//                         min = copy;
//                         cout << "change" << endl;
//                     }
//                 }
                      
//                 counter++;
//             }
            
//         }
//         pol = min;
//         if(min.area() -  pol.area() == Da){
//             break;
//         }
//         Da = min.area() -  pol.area();
//     }

//     pol = min;
//     for (const Segment_2& e : pol.edges()) {

//         cout <<  " final     " << e << endl;
//     }
//     cout << "min area found " << abs(pol.area()) << endl;

//     *resultarea = abs(pol.area());
//     return pol;
// }