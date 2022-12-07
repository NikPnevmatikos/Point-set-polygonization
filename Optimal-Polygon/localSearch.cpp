#include "localSearch.h"


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

    //int threshold = 1000, k = 3;
    double Da = *resultarea;
    for (const Segment_2& e : pol.edges()) {
        cout << e << endl;
    }


    Polygon_2 max = pol;
    while (Da >= threshold) {
        
        for (const Segment_2& e : pol.edges()) {
            //Polygon_2 copy = pol;
            cout << "----loop---- " << e << endl;
            const Polygon_2::Vertices& range = pol.vertices();
            int start, end, counter = 0;
            
            for (auto it = range.begin(); it != range.end()-(k-1); it++) {
                Polygon_2 copy = pol;
                vector<Point_2> blueline;
                cout << *it << endl;

                // auto start = it;
                // int i = 0;
                bool flag = false;
                start = counter;                                    // starting point of the blue line
                end = counter + (k-1);                              // ending point of the blue line
                for (int i = 0; i < k; i++) {
                    //if (i > 0) {
                        // if (*(it+i-1) == e.source() && *(it+i) == e.target()) {
                        //     flag =  true;
                        //     break;
                        // }
                    if ((*(it+i) == e.target()) || (*(it+i) == e.source())) {
                        flag =  true;
                        cout << "m[hka" << endl;
                        break;
                    }   
                    //}
                    blueline.insert(blueline.begin()+0,*(it+i));
                }

                if (flag) {
                    cout << "nooooo blue line" << endl;
                    counter++;
                    continue;
                }
                cout << "blue line" << endl;
                cout << "start " << start << endl;
                cout << "end " << end << endl;
                for (int i = 0; i < blueline.size(); i++) {
                    cout << "  " << blueline[i] << endl;
                }
                cout << "stop blueline" << endl;

                // if (copy.vertices_begin()+end == copy.end()) {
                //     copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+0);
                // }
                //else {
                copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+end+1);
                // }
                // for (const Segment_2& e : pol.edges()) {

                //     cout <<  " delete     " << e << endl;
                // }
                //cout << " seg " << seg << endl;
                int insert = 0;
                //const Polygon_2::Vertices& findvertix = copy.vertices();
                int j = 0;
                for (const Point_2& p : copy.vertices()) {
                    
                    if (p == Point_2(e.target())) {
                        //cout << " j and it " << j <<  " " << *(it) << endl;
                        copy.insert(copy.vertices_begin() + j, blueline.begin(), blueline.end());
                        break;
                    }
                    j++;
                }

                for (const Segment_2& e : copy.edges()) {

                    cout <<  " posiball     " << e << endl;
                }

                cout << "copy area" << abs(copy.area()) << endl;
                cout << "max area" << abs(max.area()) << endl;
                if (copy.is_simple() == true) { 
                    if (abs(copy.area()) > abs(max.area())) {
                        max = copy;
                        cout << "change" << endl;
                    }
                }
                      
                counter++;
            }
            
        }
        pol = max;
        if(max.area() -  pol.area() == Da){
            break;
        }
        Da = max.area() -  pol.area();
    }

    pol = max;
    for (const Segment_2& e : pol.edges()) {

        cout <<  " final     " << e << endl;
    }
    cout << "Max area found " << abs(pol.area()) << endl;

    *resultarea = abs(pol.area());
    return pol;
}



Polygon_2 localSearch_min(Polygon_2 pol, double threshold, int k, double* resultarea) {

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

    //int threshold = 1000, k = 3;
    double Da = *resultarea;
    for (const Segment_2& e : pol.edges()) {
        cout << e << endl;
    }


    Polygon_2 min = pol;
    while (Da >= threshold) {
        
        for (const Segment_2& e : pol.edges()) {
            //Polygon_2 copy = pol;
            cout << "----loop---- " << e << endl;
            const Polygon_2::Vertices& range = pol.vertices();
            int start, end, counter = 0;
            
            for (auto it = range.begin(); it != range.end()-(k-1); it++) {
                Polygon_2 copy = pol;
                vector<Point_2> blueline;
                cout << *it << endl;

                bool flag = false;
                start = counter;                                    // starting point of the blue line
                end = counter + (k-1);                              // ending point of the blue line
                for (int i = 0; i < k; i++) {

                    if ((*(it+i) == e.target()) || (*(it+i) == e.source())) {
                        flag =  true;
                        cout << "m[hka" << endl;
                        break;
                    }   

                    blueline.insert(blueline.begin()+0,*(it+i));
                }

                if (flag) {
                    cout << "nooooo blue line" << endl;
                    counter++;
                    continue;
                }
                cout << "blue line" << endl;
                cout << "start " << start << endl;
                cout << "end " << end << endl;
                for (int i = 0; i < blueline.size(); i++) {
                    cout << "  " << blueline[i] << endl;
                }
                cout << "stop blueline" << endl;

                copy.erase(copy.vertices_begin()+start, copy.vertices_begin()+end+1);

                int insert = 0;
                //const Polygon_2::Vertices& findvertix = copy.vertices();
                int j = 0;
                for (const Point_2& p : copy.vertices()) {
                    
                    if (p == Point_2(e.target())) {
                        //cout << " j and it " << j <<  " " << *(it) << endl;
                        copy.insert(copy.vertices_begin() + j, blueline.begin(), blueline.end());
                        break;
                    }
                    j++;
                }

                for (const Segment_2& e : copy.edges()) {

                    cout <<  " posiball     " << e << endl;
                }

                cout << "copy area" << abs(copy.area()) << endl;
                cout << "min area" << abs(min.area()) << endl;
                if (copy.is_simple() == true) { 
                    if (abs(copy.area()) < abs(min.area())) {
                        min = copy;
                        cout << "change" << endl;
                    }
                }
                      
                counter++;
            }
            
        }
        pol = min;
        if(min.area() -  pol.area() == Da){
            break;
        }
        Da = min.area() -  pol.area();
    }

    pol = min;
    for (const Segment_2& e : pol.edges()) {

        cout <<  " final     " << e << endl;
    }
    cout << "min area found " << abs(pol.area()) << endl;

    *resultarea = abs(pol.area());
    return pol;
}