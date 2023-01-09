#include "optimal_convex.h"
#include "incremental.h"


Polygon_2 max_optimal(Polygon_2 p, vector<Point_2> &points, double* area, Segment_2 first, Segment_2 last) {
    double minarea = -1;
    Point_2 point_insert = points[0];
    int minit = 1, to_be_inserted = 1;

    //for every inside point iterate all the polygon edges to find the best fit
    for (const Segment_2& e : p.edges()) {

        // the edge can't be the first or the last
        if (e == first || e == last) {
            to_be_inserted++;
            continue;
        }

        double min = -1;
        Point_2 minPoint;

        for (int i = 0; i < points.size(); i++) {
            
            // find the point with the minimum distance from the edges of the polygon
            double distance = CGAL::squared_distance(e, points[i]);
            if (distance < min || min == -1) {
                min = distance;
                minPoint = points[i];
            }
        }
        
        // get the point with the minimum distance from the edge and check if it's visible
        Segment_2 seg1(e.source(), minPoint);
        Segment_2 seg2(e.target(), minPoint);
        
        // if visible, then check if it is the minimum area so far
        // if it is, it is the new minarea.
        if (is_visible(seg1, seg2, p)) {
            Triangle_2 temp(minPoint, e.source(), e.target());

            if (abs(temp.area()) < minarea || minarea == -1) {
                minarea = abs(temp.area());
                minit = to_be_inserted;
                point_insert = minPoint;
            } 
        }
        to_be_inserted++;
    }
    
    // insert the point with the minimum area to the polygon
    p.insert(p.vertices_begin() + minit, point_insert);

    // update current area
    *area -= minarea;
    for (int i = 0; i < points.size(); i++) {
        if (points[i] == point_insert) {
            points.erase(points.begin()+i);
        }
    }

    return p;
}

Polygon_2 min_optimal(Polygon_2 p, vector<Point_2> &points, double* area,Segment_2 first, Segment_2 last) {
    double maxarea = -1;
    Point_2 point_insert = points[0];
    int maxit = 1, to_be_inserted = 1;

    // for every inside point iterate all the polygon edges to find the best fit
    for (const Segment_2& e : p.edges()) {
        
        // the edge can't be the first or the last
        if (e == first || e == last) {
            to_be_inserted++;
            continue;
        }
        
        double min = -1;
        Point_2 minPoint;

        for (int i = 0; i < points.size(); i++) {
            
            // find the point with the maximum distance from the edges of the polygon
            double distance = CGAL::squared_distance(e, points[i]);
            if (distance < min || min == -1) {
                min = distance;
                minPoint = points[i];
            }
        }
        
        // get the point with the maximum distance from the edge and check if it's visible
        Segment_2 seg1(e.source(), minPoint);
        Segment_2 seg2(e.target(), minPoint);
        
        // if visible, then check if it is maximum the the maxarea so far
        // if it is, it is the new maxarea.
        if (is_visible(seg1, seg2, p)) {
            Triangle_2 temp(minPoint, e.source(), e.target());

            if (abs(temp.area()) > maxarea) {
                maxarea = abs(temp.area());
                maxit = to_be_inserted;
                point_insert = minPoint;
            } 

        }
        
        to_be_inserted++;
    }
    
    // insert the point with the maximum area to the polygon
    p.insert(p.vertices_begin() + maxit, point_insert);

    //update current area
    *area -= maxarea;
    for (int i = 0; i < points.size(); i++) {
        if (points[i] == point_insert) {
            points.erase(points.begin()+i);
        }
    }

    return p;
}


Polygon_2 random_optimal(Polygon_2 p, vector<Point_2> &points, double* area,Segment_2 first, Segment_2 last) {
    
    srand (time(NULL));

    Point_2 point_insert = points[0];
    int to_be_inserted = 1;

    vector<int> randompos;
    vector<Point_2> randomPoint;

    //for every inside point itterate all the polygon edges to find the best fit
    for (const Segment_2& e : p.edges()) {
        
        // can't be the first or the last
        if (e == first || e == last) {
            to_be_inserted++;
            continue;
        }
                
        double min = -1;
        Point_2 minPoint;

        for (int i = 0; i < points.size(); i++) {
            // find the point with the minimum distance from the edges of the polygon
            double distance = CGAL::squared_distance(e, points[i]);
            if (distance < min || min == -1) {
                min = distance;
                minPoint = points[i];
            }
        }
        
        // get the point with the minimum distance from the edge and check if it's visible
        Segment_2 seg1(e.source(), minPoint);
        Segment_2 seg2(e.target(), minPoint);
        
        // if visible, then check if it is minimum the the minarea so far
        // if it is, then it is the new minarea.
        if (is_visible(seg1, seg2, p)) {
            Triangle_2 temp(minPoint, e.source(), e.target());

            randompos.push_back(to_be_inserted);
            randomPoint.push_back(minPoint);
            point_insert = minPoint;
        } 

        to_be_inserted++;
    }
       
    // insert the point with the minmum area to the polygon
    int randomindex = rand() % randompos.size();
    p.insert(p.vertices_begin() + randompos[randomindex] , randomPoint[randomindex]);

    //update current area
    *area = abs(p.area());

    for (int i = 0; i < points.size(); i++) {
        if (points[i] == randomPoint[randomindex]) {
            points.erase(points.begin()+i);
        }
    }

    return p;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  C  O  N  V  E  X    H  U  L  L  

Polygon_2 convex_hull_optimal(Point_2 start, Point_2 end, vector<Point_2> points, int edge_selection, double* resultarea) {

    Polygon_2 p;
    CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(p));

    Segment_2 first;
    Segment_2 last;

    // find the first and last edge of sub-polygon
    for (const Segment_2& e: p.edges()) {
        if (e.source() == start) {
            if (e.target().y() < e.source().y()) {
                first = e;
            }
        }
        if (e.target() == start) {
            if (e.source().y() < e.target().y()) {
                first = e;
            }
        }
        if (e.source() == end) {
            if (e.source().y() > e.target().y()) {
                last = e;
            }
        }
        if (e.target() == end) {
            if(e.target().y() > e.source().y()) {
                last = e;
            }
        }
    }


    // first, make the vector points store only the points inside the convex
    // by removing all the points that make the convex hull.
    for (const Point_2& p : p.vertices()) {
        for (int i = 0; i < points.size(); i++) {
            if (points[i] == p) {
                points.erase(points.begin()+ i);
                break;
            }
        }
    }

    double area = abs(p.area());
  
    // a loop for every inside point that must be inserted to the polygon
    while (points.size() > 0) {
        if (edge_selection == 1) {
            p = random_optimal(p, points, &area, first, last);
        }
        else if (edge_selection == 2) {
            p = min_optimal(p, points, &area, first, last);
        }
        else {
            p = max_optimal(p, points, &area, first, last);
        }
    }

    *resultarea = area;
    return p;
}