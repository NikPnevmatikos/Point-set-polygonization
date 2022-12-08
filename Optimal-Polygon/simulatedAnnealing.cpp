#include "simulatedAnnealing.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

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


Polygon_2 simulatedAnnealing(Polygon_2 paste, double threshold, int L,double convex_area, double* resultarea) {


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
    double area = *resultarea;
    for (const Segment_2& e : pol.edges()) {
        cout << e << endl;
    }

    Polygon_2 out;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(out));
    double c_area = abs(out.area());

    double T = 1;
    double E = pol.vertices().size() * (1 - abs(area)/c_area);
    double DE = E;

    while (T >= 0){
        Polygon_2 copy = pol;
        int loop = 0;
        bool cannotChange = false;
        while(loop < copy.vertices().size()){
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
                break;
            }
            else {
                cout << "no <3" << endl;
                if(loop == copy.vertices().size()-1){
                    cannotChange = true;
                }
                copy = pol;
            }

            loop++;
        }

        if(cannotChange == true){
            break;
        }
        double newE = copy.vertices().size() * (1 - abs(copy.area())/c_area);
        double R = fRand(0,1);
        DE = E - newE;
        if(DE < 0 || (exp(-DE/T)) >= R){
            pol = copy;
            E = newE;
        }
        T -= 1/L;
        cout << "next loop" << endl;
    }

    *resultarea = abs(pol.area());
    cout << "final area " << *resultarea << endl;
    return pol;
}