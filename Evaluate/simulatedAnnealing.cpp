#include "simulatedAnnealing.h"
#include "optimal_convex.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>

double fRand(double fMin, double fMax) {        // find random double
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

bool seg_intersect(Segment_2 a, Segment_2 b) {
    const auto result = intersection(a, b);

    if (result) {       // "return result;" can't be used here cause result is not boolean type
        return true;
    }
    
    return false;
}


bool intersect(Triangle_2 a, vector<Point_2> points) {

    for (int i = 0; i < points.size(); i++) {
        // if the point is in the edges of the triangle
        if (a.bounded_side(points[i]) == 0) {
            bool is_vertex = false;
            // check if it one of the 3 triangle's points
            for (int j = 0; j < 3; j ++) {
                if (a.vertex(j) == points[i]) {
                    is_vertex = true;
                    break;
                }
            }
            // else the point intersects
            if (is_vertex == false) {
                return true;
            }
        }
        // if it is inside the area of the triangle
        // then it intersects
        if (a.bounded_side(points[i]) == 1) {
            return true;
        }
    }

    return false;
}


Polygon_2 simulatedAnnealing(Polygon_2 pol, int L, double convex_area, string minmax, double* resultarea, int cutoff) {

    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(stop - start);
    int duration = duration1.count();
    
    srand (time(NULL));

    double area = *resultarea;

    Polygon_2 out;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(out));
    double c_area = abs(out.area());

    Kd_Tree tree(pol.vertices_begin(), pol.vertices_end());

    double T = 1.0;
    double E;
    if (minmax.compare("max") == 0) {
        E = pol.vertices().size() * (abs(area) / c_area);
    }
    else{
        E = pol.vertices().size() * (1-abs(area) / c_area);
    }

    double DE = E;
    Polygon_2 max = pol;

    while (T >= 0 && cutoff > duration) {
        Polygon_2 copy = pol;
        int loop = 0;
        bool cannotChange = false;

        while (loop < copy.vertices().size()) {
            // pick a random vertex of the polygon
            int randvertex = rand() % (copy.vertices().size()-3) +1;

            Polygon_2::Vertex_iterator it = copy.vertices_begin();

            // "swap" the random vertex with the vertex after it
            Point_2 temp = *(it+randvertex);
            *(it+randvertex) = *(it+randvertex+1);
            *(it+randvertex+1) = temp;


            it = copy.vertices_begin();

            vector<Point_2> result;

            Point_2 first = *(it + randvertex -1);

            // find the lowest x and y and the highest from the vertices
            // from the 4 points, so that we can create the rectangle
            int low_x = first.x(), low_y = first.y(), up_x = first.x() , up_y = first.y();
            for (int i = 0; i < 3; i++) {
                Point_2 point = *(it+randvertex+i);

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


            // create the rectangle
            Fuzzy_iso_box approximate_range(Point_2(low_x, low_y), Point_2(up_x, up_y));
            tree.search(back_inserter(result), approximate_range);


            // create the two triangles
            Triangle_2 a(Point_2(*(it + randvertex-1)), Point_2(*(it + randvertex)), Point_2(*(it + randvertex+1)));
            Triangle_2 b(Point_2(*(it + randvertex)), Point_2(*(it + randvertex+1)), Point_2(*(it + randvertex+2)));
            // take the two edges
            Segment_2 seg1(Point_2(*(it + randvertex-1)), *(it + randvertex));
            Segment_2 seg2(Point_2(*(it + randvertex+1)), *(it + randvertex+2));

            // check if the segments intersect or if the area of the triangles have
            // any points. if any of the these happen, then the changes can occur
            if (seg_intersect(seg1, seg2) == false && intersect(a, result) == false && intersect(b, result) == false) {
                break;
            }
            if (loop == copy.vertices().size()-1) {
                cannotChange = true;
            }
            copy = pol;


            loop++;
        }

        if (cannotChange == true) {
            break;
        }


        // calculate new energy
        double newE;
        if (minmax.compare("max") == 0) {
            newE = copy.vertices().size() * (abs(copy.area())/c_area);
        }
        else{
            newE = copy.vertices().size() * (1-abs(copy.area())/c_area);
        }

        double R = fRand(0,1);
        DE = E - newE;
        //determin if the change will be applied
        if (DE < 0 || (exp(-DE/T)) >= R) {
            pol = copy;
            E = newE;
            T = T - 1.0/L;

        }

        stop = chrono::high_resolution_clock::now();
        duration1 = chrono::duration_cast<chrono::milliseconds>(stop - start);
        duration = duration1.count();
    }

    *resultarea = abs(pol.area());
    
    return pol;
}



Polygon_2 simulatedAnnealing_global(Polygon_2 pol, int L,double convex_area,string minmax, double* resultarea,int cutoff) {

    srand(time(NULL));

    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(stop - start);
    int duration = duration1.count();

    double area = *resultarea;
    
    Polygon_2 out;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(out));
    double c_area = abs(out.area());

    double T = 1.0;
    double E;
    if (minmax.compare("max") == 0) {
        E = pol.vertices().size() * (abs(area) / c_area);
    }
    else{
        E = pol.vertices().size() * (1-abs(area) / c_area);
    }
    double DE = E;

    while (T >= 0 && cutoff > duration) {

        Polygon_2 copy = pol;
        int loop = 0;
        bool cannotChange = false;

        while (loop < copy.vertices().size()) {
            // take a random vertex and a random edge
            int randvertex = rand() % (copy.vertices().size()-1) +1;
            int randedge = rand() % (copy.vertices().size()-2) +1;

            // if the vertex isa point of the edge
            // pick another edge
            while (randvertex == randedge || randvertex == randedge+1) {
                randedge = rand() % (copy.vertices().size()-2) +1;
            }

            Polygon_2::Vertex_iterator it = copy.vertices_begin();

            Segment_2 seg(Point_2(*(it+randedge)), Point_2(*(it+randedge+1)));

            Point_2 to_be_inserted = *(it+randvertex);
            copy.erase(copy.vertices_begin()+randvertex);

            int insert = 0;
            int j = 0;
            // insert the blue line, starting from the target of the edge
            for (const Point_2& p : copy.vertices()) {
                if (p == seg.target()) {
                    copy.insert(copy.vertices_begin() + j, to_be_inserted);
                    break;
                }
                j++;
            }

            if (copy.is_simple() == true) {
                break;
            }

            if (loop == copy.vertices().size()-1) {
                cannotChange = true;
            }

            copy = pol;
            loop++;
        }

        if (cannotChange == true) {
            break;
        }

        // calculate new energy
        double newE;
        if (minmax.compare("max") == 0) {
            newE = copy.vertices().size() * (abs(copy.area())/c_area);
        }
        else{
            newE = copy.vertices().size() * (1-abs(copy.area())/c_area);
        }

        double R = fRand(0, 1);
        DE = E - newE;

        if (DE < 0 || (exp(-DE/T)) >= R) {
            pol = copy;
            E = newE;
            T = T - 1.0/L;
        }

        stop = chrono::high_resolution_clock::now();
        duration1 = chrono::duration_cast<chrono::milliseconds>(stop - start);
        duration = duration1.count();

    }


    *resultarea = abs(pol.area());

    return pol;

}


Polygon_2 global(Polygon_2 pol, int L, double convex_area,string minmax, double* resultarea, Point_2 first, Point_2 last) {

    srand(time(NULL));

    double area = *resultarea;
    Polygon_2 out;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(out));
    double c_area = abs(out.area());

    double T = 1.0;
    double E;
    if (minmax.compare("max") == 0) {
        E = pol.vertices().size() * (abs(area) / c_area);
    }
    else{
        E = pol.vertices().size() * (1-abs(area) / c_area);
    }
    double DE = E;

    while (T >= 0) {

        Polygon_2 copy = pol;
        int loop = 0;
        bool cannotChange = false;
        bool stop;
        while (loop < copy.vertices().size()) {
            // take a random vertex and a random edge
            int randvertex = rand() % (copy.vertices().size()-1) +1;
            
            Polygon_2::Vertex_iterator it = copy.vertices_begin();
            int vercount = 0;
            while (1) {
                // the vertex shouldn't be the first or the last one
                if (*(it+randvertex) == first || *(it+randvertex) == last) {
                    randvertex = rand() % (copy.vertices().size()-1) +1;
                }
                else if (randvertex == copy.vertices().size()-1) {
                    if (*(it+0) == first || *(it+0) == last) {
                        randvertex = rand() % (copy.vertices().size()-1) +1;    
                    }
                }
                // nor the vertex before or after the first/last
                else if (*(it+randvertex+1) == first || *(it+randvertex+1) == last){
                    randvertex = rand() % (copy.vertices().size()-1) +1;
                }
                else if (*(it+randvertex-1) == first || *(it+randvertex-1) == last) {
                    randvertex = rand() % (copy.vertices().size()-1) +1;
                }
                else {
                    break;
                }

                // if we didn't find any vertex that qualifies the above critiria
                // after many tries, break the while-loop
                if (vercount == copy.vertices().size()) {
                    stop = true;
                    break;
                }
                vercount++;
            }

            if (stop == true) {
                break;
            }
            
            int randedge = rand() % (copy.vertices().size()-2) +1;

            it = copy.vertices_begin();

            int count = 0;
            stop = false;
            while (1) {
                // the vertex shouldn't have the same points as the edge
                if (randvertex == randedge || randvertex == randedge+1) {
                    randedge = rand() % (copy.vertices().size()-2) +1;
                }
                // the edge shouldn't be on the first or the last vertex
                else if (*(it+randedge) == first || *(it+randedge+1) == first) {
                    randedge = rand() % (copy.vertices().size()-2) +1;
                }
                else if (*(it+randedge) == last || *(it+randedge+1) == last) {
                    randedge = rand() % (copy.vertices().size()-2) +1;
                }
                else {
                    break;
                }

                // if we didn't find any edge that qualifies the above critiria
                // after many tries, break the while-loop
                if (count == copy.vertices().size()) {
                    stop = true;
                    break;
                }
                count++;
            }

            if (stop == true) {
                break;
            }
            it = copy.vertices_begin();

            Segment_2 seg(Point_2(*(it+randedge)), Point_2(*(it+randedge+1)));
            
            Point_2 to_be_inserted = *(it+randvertex);
            copy.erase(copy.vertices_begin()+randvertex);

            int insert = 0;
            int j = 0;

            // insert the blue line, starting from the target of the edge
            for (const Point_2& p : copy.vertices()) {
                if (p == seg.target()) {
                    copy.insert(copy.vertices_begin() + j, to_be_inserted);
                    break;
                }
                j++;
            }

            if (copy.is_simple() == true) {
                break;
            }

            if (loop == copy.vertices().size()-1) {
                cannotChange = true;
            }

            copy = pol;
            loop++;
        }

        if (cannotChange == true || stop == true) {
            break;
        }

        // calculate new energy
        double newE;
        if (minmax.compare("max") == 0) {
            newE = copy.vertices().size() * (abs(copy.area())/c_area);
        }
        else {
            newE = copy.vertices().size() * (1-abs(copy.area())/c_area);
        }

        double R = fRand(0, 1);
        DE = E - newE;
    
        if (DE < 0 || (exp(-DE/T)) >= R) {
            pol = copy;
            E = newE;
            T = T - 1.0/L;
        }
    }


    *resultarea = abs(pol.area());
    
    return pol;
}







bool increasing(Point_2 p1, Point_2 p2) {
    if (p1.x() == p2.x()) {
        return (p1.y() < p2.y());
    }
    else {
        return (p1.x() < p2.x());
    }
}

Polygon_2 simulatedAnnealing_subdivision(vector<Point_2> points, int L, double convex_area,string minmax, double* resultarea) {

    sort(points.begin(), points.end(), increasing);

    vector<vector<Point_2>> set_of_points;      // each vector contains the points for the sub-polygons
    int m = 100;
    bool flag = false;
    vector<Point_2> subPoints;
    for (int i = 0; i < points.size(); i++) {
        if (i >= m && i != points.size()-1) {
            // if the point before i is lower and the point after i is lower then 
            // the we can create a sub-polygon
            if (points[i].y() > points[i-1].y() && points[i].y() > points[i+1].y()) {
                flag = true;
            }
        }
        
        subPoints.push_back(points[i]);

        // if the sub-polygon is found
        if (flag == true) {
            set_of_points.push_back(subPoints);
            flag = false;
            m += i;
            subPoints.clear();

            // push back the point again because it is a point for the next
            // sub-polygon as well
            subPoints.push_back(points[i]);    
        }
        // if the point is the last one push back the point to the last sub-polygon
        else if (i == points.size()-1) {
            set_of_points.push_back(subPoints);   
        }    
        
    }

    vector<Polygon_2> subPolygons;
    for (int i = 0; i < set_of_points.size(); i++) {

        Polygon_2 temp;
        double area;
        if(minmax.compare("max") == 0){
            temp = convex_hull_optimal(set_of_points[i].front(), set_of_points[i].back(), set_of_points[i], 3, &area);
        }
        else{
            temp = convex_hull_optimal(set_of_points[i].front(), set_of_points[i].back(), set_of_points[i], 2, &area);
        }
        Polygon_2 p;
        CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(p));        
        double convex_hull_area = p.area();
        temp = global(temp,L, convex_hull_area,minmax, &area, set_of_points[i].front(), set_of_points[i].back());

        subPolygons.push_back(temp);
    
    }


    for (int i = 1; i < subPolygons.size(); i++) {

        int insert = 0;
        int loop = 0;
        for (Point_2 p: subPolygons[0].vertices()) {
            // take the last point of the sub-polygon, which is 
            // the point where the sub-polygons meet
            if (p == set_of_points[i-1].back()) {
                insert = loop;
            }
            loop++;
        }
        
        loop = 0;
        int start = 0;        
        for (Point_2 p: subPolygons[i].vertices()) {
            if (p == set_of_points[i].front()) {
                start = loop;
                break;
            }
            loop++;
        }
        
        // insert vertex from the point of the first sub-polygon before the join point, to the point of the 
        // next sub-polygon after the join point
        subPolygons[0].insert(subPolygons[0].begin() + insert, subPolygons[i].begin() + start + 1, subPolygons[i].end());
        if (start != 0) {
            subPolygons[0].insert(subPolygons[0].begin() + insert + (subPolygons[i].end() - (subPolygons[i].begin() + start)) -1, subPolygons[i].begin(), subPolygons[i].begin() + start);
        }
    }


    *resultarea = subPolygons[0].area();
    return subPolygons[0];
}





















