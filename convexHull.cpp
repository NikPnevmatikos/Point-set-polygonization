#include "convexHull.h"
#include "incremental.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  C  O  N  V  E  X    H  U  L  L  
Polygon_2 convex_hull(vector<Point_2> points, int edge_selection, double* resultarea) {

    Polygon_2 p;
    CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(p));
 
    // first, make the vector points store only the points inside the convex
    // by removing all the points that make the convex.
    for (const Point_2& p  : p.vertices()) {
        for (int i = 0; i < points.size(); i++) {
            if (points[i] == p) {
                points.erase(points.begin()+ i);
                break;
            }
        }
    }

    for (const Segment_2& e  : p.edges()) {
        cout << e << endl;
    }
    double area = abs(p.area());
    
    for (int i = 0; i < points.size(); i++) {
        cout << points[i] << endl;
    }

    // a loop for every inside point that must be inserted to the polygon
    while (points.size() > 0) {

        double minarea = -1;
        Point_2 point_insert = points[0];
        int minit = 1, to_be_inserted = 1;

        for (const Segment_2& e : p.edges()) {
            
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
            
            // if visible, then check if it is minimun the the minarea so far
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
        area -= minarea;
        for (int i = 0; i < points.size(); i++) {
            if (points[i] == point_insert) {
                points.erase(points.begin()+i);
            }
        }
    
    }

    *resultarea = area;
    return p;
}