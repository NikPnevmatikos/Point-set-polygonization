# Point-set-polygonization
compile:

    cgal_create_CMakeLists -s main
    cmake -DCGAL_DIR=/user/lib/CGAL .
    make

run:

    $./to_polygon –i <point set input file> –ο <output file> –algorithm <incremental or
    convex_hull> -edge_selection <1 or 2 or 3> -initialization <1a
    or 1b or 2a or 2b | only in incremental>  


input file must be in this form:

    # <description of point set>
    # parameters "convex_hull": {"area": "Χ"} / x is the area of convex hull 
    0 x0 y0
    1 x1 y1
    … … …
    n-1 xn yn


