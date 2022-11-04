#include "incremental.h"
#include "sort.h"
#include <string.h>
#include <time.h>       


// erase the red edges and then add the new point to the convex
Polygon_2 create_convex(Point_2 point, Polygon_2 convex, int start, int end) {
    Polygon_2 result;

    if (end == 0) {     // if end is the first point
        convex.erase(convex.vertices_begin()+start+1, convex.vertices_end());
        convex.push_back(Point_2(point));
    }
    else {
        convex.erase(convex.vertices_begin()+start+1, convex.vertices_begin()+end);
        convex.insert(convex.vertices_begin()+end, Point_2(point));
    }
    return convex;
}

// checks the visibility
// checks if any edge intersects with an edge of the polygon
// returns true if it is visible and false if it isn't
bool is_visible(Segment_2 seg1, Segment_2 seg2, Polygon_2 pol) {
    bool flag = true;
    for (const Segment_2& e : pol.edges()) {
        const auto result1 = intersection(e, seg1);
        const auto result2 = intersection(e, seg2);

        if (result1) {
            // checks if the intersection happens at the start or the end point 
            // of the edge we viewing checking
            if (const Point_2* p = boost::get<Point_2 >(&*result1)) {
                if (*p != seg1.source() && *p != seg1.target()) {
                    flag = false;
                    break;
                }
            }
        }
        if (result2) {
            if (const Point_2* p = boost::get<Point_2 >(&*result2)) {
                if (*p != seg2.source() && *p != seg2.target()) {
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}

// function to find the max area of the polygon
Polygon_2 insert_point_max(Polygon_2 p, Point_2 point, Point_2 start, Point_2 end, double* area) {
        
    vector<Segment_2> green_edges;
    bool filled = false;

    int to_be_inserted = 1;
    double max = -1;
    int maxit = 1;
    
    for (const Segment_2& e : p.edges()) {
        if (e.source() == start) {          // if the first point of the edge is the start, add green_edges
            filled = true;
        }
        if (filled) {
            Segment_2 seg1(e.source(), point);
            Segment_2 seg2(e.target(), point);

            if (is_visible(seg1, seg2, p)) {
                Triangle_2 temp(point, e.source(), e.target()); 

                if (abs(temp.area()) > max) {
                    max = abs(temp.area());
                    maxit = to_be_inserted;
                }
                green_edges.push_back(e);
            }
        }
        if (e.target() == end) {
            break;
        }

        to_be_inserted++;
    }

    p.insert(p.vertices_begin() + maxit, point);

    *area = *area + max;

    return p;
}

// function to find the min area of the polygon
Polygon_2 insert_point_min(Polygon_2 p, Point_2 point, Point_2 start, Point_2 end, double* area) {
        
    vector<Segment_2> green_edges;
    bool filled = false;

    int to_be_inserted = 1;
    double min = -1;
    int minit = -1;

    for (const Segment_2& e : p.edges()) {
        if (e.source() == start) {
            filled = true;
        }
        if (filled) {
            Segment_2 seg1(e.source(), point);
            Segment_2 seg2(e.target(), point);

            if (is_visible(seg1, seg2, p)) {
                Triangle_2 temp(point, e.source(), e.target());
                
                if (abs(temp.area()) < min || min == -1) {
                    min = abs(temp.area());
                    minit = to_be_inserted;

                }
                green_edges.push_back(e);
            }
        }
        if (e.target() == end) {
            break;
        }

        to_be_inserted++;
    }
    cout << "green edges " << green_edges.size() << endl;
    p.insert(p.vertices_begin() + minit, point);

    *area = *area + min;

    return p;
}


// function to find a random area of the polygon
Polygon_2 insert_point_random(Polygon_2 p, Point_2 point, Point_2 start, Point_2 end, double* area) {
    
    srand (time(NULL));
    
    vector<Segment_2> green_edges;
    vector<int> green_edges_pos;

    bool filled = false;
    int to_be_inserted = 1;

    for (const Segment_2& e : p.edges()) {
        if (e.source() == start) {
            filled = true;
        }
        if (filled) {
            Segment_2 seg1(e.source(), point);
            Segment_2 seg2(e.target(), point);

            if (is_visible(seg1, seg2, p)) {
                green_edges.push_back(e);
                // put all visible edges to the vector
                green_edges_pos.push_back(to_be_inserted);
            }
        }
        if (e.target() == end) {
            break;
        }

        to_be_inserted++;
    }

    // insert a random edge from green_edges_pos vector to the polygon
    p.insert(p.vertices_begin() + green_edges_pos[rand()%green_edges_pos.size()], point);

    *area = abs(p.area());

    return p;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  I N C R E M E N T A L   F U N C T I O N 
Polygon_2 incremental(vector<Point_2> points, string initialization, int edge_selection, double* resultarea) {

    if (initialization.compare("1a")) {
        sort(points.begin(), points.end(), decreasing_x);
    }
    else if (initialization.compare("1b")) {
        sort(points.begin(), points.end(), increasing_x);
    }
    else if (initialization.compare("2a")) {
        sort(points.begin(), points.end(), decreasing_y);
    }
    else if (initialization.compare("2b")) {
        sort(points.begin(), points.end(), increasing_y);
    }
    
    cout << "lala" << endl;
    Polygon_2 p;
    Polygon_2 convex;
    

    // make a triangle using the first 3 points
    for (int i = 0; i < 3; i++){
        p.push_back(Point_2(points[i]));
        convex.push_back(Point_2(points[i]));
    }

    double area = abs(p.area());

    for (int pointindex = 3; pointindex < points.size(); pointindex++) {
        cout << "begging of for loop" << endl;
        // find the orientation of the polygon
        // if it is positive(+) then the visible edges are going to be negative(-) and vice versa
        // the orientation of the polygon sometimes changes so we got to check it everytime
        CGAL::Sign orientation = CGAL::orientation(*(convex.vertices().begin()), *(convex.vertices().begin()+1), *(convex.vertices().begin()+2));
        
        vector<Segment_2> red_edges;
        Segment_2 prev;
        bool found = false, init = false;
        Point_2 start, end;
        int startcon = 0, endcon = 0;               // starting and ending position of the convex

        int curpos = 0;
        for (const Segment_2& e : convex.edges()) {

            if (CGAL::orientation(e.source(), e.target(), points[pointindex]) != orientation) { // visible
                if (!found) {
                    found = true;
                    if (e.source() == points[0] && e.target() == points[1]) {
                        start = e.source();
                    }
                    else {
                        if (prev.target() == e.target() || prev.target() == e.source()) {
                            start = prev.target();
                        }
                        else {
                            start = prev.source();
                        }
                    }
                    startcon = curpos;
                }
                cout << "(before push reedge)e.target is " << e.target() << endl;
                red_edges.push_back(e);
            }            
            else {      // not visible

                if (found) {
                    init = true;
                    if(e.target() == points[0]){
                        end = points[0];
                        endcon = 0;
                    }
                    else{
                        if (prev.target() == e.target() || prev.target() == e.source()) {
                            end = prev.target();
                        }
                        else {
                            end = prev.source();
                        }
                        endcon = curpos;                        
                    }
                    break;
                }
            }
            prev = e;
            curpos++;
        }

        if (init == false) {        // if the end point does't have a value, the value is the first point
            end = points[0];
            endcon = 0;
        }

        cout << "red edges found" << red_edges.size() << endl;
        if (edge_selection == 1) {
            p = insert_point_random(p, points[pointindex], start, end, &area);
        }
        else if (edge_selection == 2) {
            p = insert_point_min(p, points[pointindex], start, end, &area);
        }
        else {
            p = insert_point_max(p, points[pointindex], start, end, &area);
        }
        
        convex = create_convex(points[pointindex], convex, startcon, endcon);

    }

    *resultarea = area;
    return p;
}








