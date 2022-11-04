#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

bool decreasing_x(Point_2 p1, Point_2 p2) {      
    if (p1.x() == p2.x()) {
        return (p1.y() > p2.y());
    }
    else {
        return (p1.x() > p2.x());
    }
}

bool increasing_x(Point_2 p1, Point_2 p2) {
    if (p1.x() == p2.x()) {
        return (p1.y() < p2.y());
    }
    else {
        return (p1.x() < p2.x());
    }
}

bool decreasing_y(Point_2 p1, Point_2 p2){

    if(p1.y() == p2.y()){
        return (p1.x() > p2.x());
    }
    else{ 
        return (p1.y() > p2.y());
    }
}

bool increasing_y(Point_2 p1, Point_2 p2){
    if(p1.y() == p2.y()){
        return (p1.x() < p2.x());
    }
    else{ 
        return (p1.y() < p2.y());
    }
}