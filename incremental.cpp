#include "incremental.h"
#include "sort.h"

Polygon_2 create_convex(Point_2 point, Polygon_2 convex, int start, int end) {
    Polygon_2 result;

    // cout << "start and end    ----------- > "<< start << " " << end << endl;
    if (end == 0) {
        convex.erase(convex.vertices_begin()+start+1, convex.vertices_end());
        convex.push_back(Point_2(point));
    }
    else {
        convex.erase(convex.vertices_begin()+start+1, convex.vertices_begin()+end);
        convex.insert(convex.vertices_begin()+end, Point_2(point));
    }

    return convex;
}

bool is_visible(Segment_2 seg1, Segment_2 seg2, Polygon_2 pol) {
    for (const Segment_2& e : pol.edges()) {
        const auto result1 = intersection(e, seg1);
        const auto result2 = intersection(e, seg2);

        if (result1) {
        
            if (const Point_2* p = boost::get<Point_2 >(&*result1)) {
                if(*p != seg1.source() && *p != seg1.target()){
                    return false;
                }
            }
        }
        else if (result2) {

            if (const Point_2* p = boost::get<Point_2 >(&*result2)) {

                if(*p != seg2.source() && *p != seg2.target()){
                    return false;
                }
            }
            }          

    }
    return true;
}



void incremental(vector<Point_2> points) {

    sort(points.begin(), points.end(), increasing_x);
    Polygon_2 p;
    Polygon_2 convex;
    
    for (int i = 0; i < 3; i++){
        p.push_back(Point_2(points[i]));
        convex.push_back(Point_2(points[i]));
    }

    double area = abs(p.area());

    
    for (int pointindex = 3; pointindex < points.size(); pointindex++) {

        CGAL::Sign orientation = CGAL::orientation(*(convex.vertices().begin()), *(convex.vertices().begin()+1), *(convex.vertices().begin()+2));
        
        vector<Segment_2> red_edges;
        Segment_2 prev;
        bool found = false, init = false;
        Point_2 start, end;
        int startcon = 0, endcon = 0;               // starting and ending position of the convex

        int curpos = 0;
        for (const Segment_2& e : convex.edges()) {
            // cout << "Edge " << e << " for point " << points[pointindex] << " is ";

            // cout << "-----> orientation now is " << CGAL::orientation(e.source(), e.target(), points[pointindex]) << endl;
            if (CGAL::orientation(e.source(), e.target(), points[pointindex]) == CGAL::COLLINEAR) {
                // cout << "collinear" << endl;
            }
            else if (CGAL::orientation(e.source(), e.target(), points[pointindex]) != orientation) {
                // cout << "visible" << endl;
                if (!found) {
                    found = true;
                    if (e.source() == points[0] && e.target() == points[1]){
                        start = e.source();
                    }
                    else {
                        if (prev.target() == e.target() || prev.target() == e.source()){
                            start = prev.target();
                        }
                        else {
                            start = prev.source();
                        }
                    }
                    startcon = curpos;
                }
                red_edges.push_back(e);
            }            
            else {
                // cout << "not visible" << endl;

                if (found) {
                    init = true;
                    if (prev.target() == e.target() || prev.target() == e.source()) {
                        end = prev.target();
                    }
                    else {
                        end = prev.source();
                    }
                    endcon = curpos;
                    break;
                    
                }
            }
            prev = e;
            curpos++;
        }
        if (init == false) {        // if the end point does have a value, the value is the first point
            end = points[0];
            endcon = 0;
        }

        cout << "Red edges of point " << points[pointindex] << " are: " << endl;
        for (int i = 0; i < red_edges.size(); i++) {
            cout << red_edges[i] << endl;
        }

        cout << "start and finish points of the selected redline:" << endl;
        cout << start << "     " << end << endl;


        //~~~~~~~~~~~~~~~~~~~~~~~~~~ green edges
        vector<Segment_2> green_edges;
        bool filled = false;

        int to_be_inserted = 1;
        double max = -1;
        int maxit = 1;
        for (const Segment_2& e : p.edges()) {
            if (e.source() == start) {
                filled = true;
            }
            if (filled) {
                Segment_2 seg1(e.source(), points[pointindex]);
                Segment_2 seg2(e.target(), points[pointindex]);

                if (is_visible(seg1, seg2, p)) {
                    Triangle_2 temp(points[pointindex], e.source(), e.target()); // :)
                    // cout << "the area of the triangle now is " << abs(temp.area()) << endl;

                    if (abs(temp.area()) > max) {
                        max = abs(temp.area());
                        maxit = to_be_inserted;
                        // cout << "max changed " << max << endl;

                    }
                    green_edges.push_back(e);
                }
            }
            if (e.target() == end) {
                break;
            }

            to_be_inserted++;
        }

        p.insert(p.vertices_begin() + maxit, points[pointindex]);
        area += max;

        
        cout << "The current area of the polygon is : " << area << "." << endl;
        cout << "Polygon is:" << endl;
        for (const Segment_2& e : p.edges()) {
            std::cout << e.source() << "  " << e.target() << std::endl;

        }


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ convex
        convex = create_convex(points[pointindex], convex, startcon, endcon);

        cout << "Convex is:" << endl;
        for (const Segment_2& e : convex.edges()) {
            std::cout << e.source() << "  " << e.target() << std::endl;
        }
        cout << endl;
    }
}








