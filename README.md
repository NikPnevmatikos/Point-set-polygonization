# Point-set-polygonization

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name:   Nikolaos Pnevmatikos 
AM:     1115201900157

Name:   Maria Diamanti
AM:     1115201900052
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

compile:

    cgal_create_CMakeLists -s main
    cmake -DCGAL_DIR=/user/lib/CGAL .
    make

run:

    $./to_polygon –i <point set input file> –ο <output file> –algorithm <incremental or
    convex_hull> -edge_selection <1 or 2 or 3> -initialization <1a
    or 1b or 2a or 2b | only in incremental>  

To compile and run the program you can use the exe.sh bash script:

    chmod x+u exe.sh    (only need this for the first time you compile-run)
    ./exe.sh            (for every other time you want to compile-run)


Input file should be in this form:

    # <description of point set>
    # parameters "convex_hull": {"area": "Χ"} / x is the area of convex hull 
    0 x0 y0
    1 x1 y1
    … … …
    n-1 xn yn

Show a graph of the polygon:

    python polygonprint.py


Files used:
    
    convertfile.h
    convertfile.cpp     
                        (contains functions that opens a file, extract points from file 
                        to vector<Point_2> and writes result to output file)
    
    convexHull.h
    convexHull.cpp      (implementation of the second algorithm)
    
    incremental.h
    incremental.cpp     (implementation of the first algorithm)
    
    sort.h
    sort.cpp            (containing the sorting algorithms)
    
    main.cpp            (execution of program)
    
    polygonprint.py     (prints the polygon in a graph)

    exe.sh              (used to compile and run the programs)
    


Program Description:

    We implemented the first two algorithms of the project.

    ~ For the first algorihm:
        
        We used 2 polygons. A convex hull polygon and the final simple polygon.
        First, sort the points according to the input arguments.
        Then, the algorithm creates a triangle with the first 3 points it finds,
        according to the sorting it was given. 
        
        The following run repeatedly, until all the points have been inserted to the polygon
        and the final area has been found.
        For each point:
            Finds the red edges on the convex hull polygon(visible edges from the point). 
            After finding the red edges, find the green edges of the final polygon.
            Pick the edge with the most beneficial triangle (greedy algorithm) for the final area 
            of the polygon.(max, min or random area)
            Connect the point to the edge picked in the previous step,
            Update the current area of the polygon
            And last, update the convex hull polygon.

    ~ For the second algorithm
        (for the visibility check we used the is_visible function of algorithm 1 in incremental.cpp file):

        First, create the convex hull polygon. After thet, remove from vector all vertices that 
        belong to the polygonal line of convex hull.

        While the inside points (the points that are not inserted to the polygon yet) exist:
            For each edge of polygon:
                Find the closest inside point, check its visibility and, then, if it is visible calculate 
                the area of the triangle it makes with the edge.
            
            Pick the point and edge with the most beneficial area (depending on the argument we picked:
            min, max or random)
            Insert it to the polygon and update the area of the polygon.

Observations:

    While testing the two algorithms, we came to the conclusion that the second algorithm
    is much slower than the first one. More specificly, for 600 points the second algorithm 
    runs for about an hour, while the first one for seconds.
    Both algorithms are greedy, because they don't guarantee that the final area is the maximum
    possible area or the minimum possible, but they do a pretty good job to find the maximum/minimum area approximately.

Some examples can be found in the testcases/results folders, images can be found in images folder. 
    
    