# Point-set-polygonization / Optimal-Polygon

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name:   Nikolaos Pnevmatikos 
AM:     1115201900157

Name:   Maria Diamanti
AM:     1115201900052
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

compile:

    cgal_create_CMakeLists -s main
    cmake -DCGAL_DIR=/user/lib/CGAL -DCMAKE_BUILD_TYPE=Release .
    make

run:

    $./to_polygon –i <point set input file> –ο <output file> polygonInit <incremental or
    convex_hull> -edge_selection <1 or 2 or 3> -initialization <1a
    or 1b or 2a or 2b | only in incremental>  –algorithm <local_search or simulated_annealing or ant_colony> -L [L parameter according to algorithm] –max [maximal area polygonization] –min [minimal area polygonization] –threshold <double> [in local search] –annealing <"local" or
    "global" or "subdivision" in simulated annealing>

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

    python polygonprint.py <filename>


Files used:
    
    convertfile.h           (contains functions that opens a file, extract points from file 
    convertfile.cpp         to vector<Point_2> and writes result to output file)
                        
    convexHull.h
    convexHull.cpp          (implementation of the second algorithm)
    
    incremental.h
    incremental.cpp         (implementation of the first algorithm)
    
    sort.h
    sort.cpp                (containing the sorting algorithms)
    
    main.cpp                (execution of program)
    
    polygonprint.py         (prints the polygon in a graph)

    exe.sh                  (used to compile and run the programs)


New Files Added:

    localSearch.h
    localSearch.cpp         (implementation for the local Search algorithm)

    optimal_convex.h
    optimal_convex.cpp      (updated convex hull algorithm for the sub-division)

    simulatedAnnealing.h
    simulatedAnnealing.cpp (implementation for the simulatedAnnealing algorithm)
    


Program Description:

    We implemented the first two algorithms of the second project.

    ~ For the first algorihm:
        
        We follow the pseudocode shown to us in the class. From the result polygon of the first two algorithms, 
            iterate all the edges
                for every edge find all k-paths
                    for every k path apply the local step, check if the polygon is simple and if
                    it is find if the new polygon has better area (min or max area)
            
            apply changes
        repeat until da < threshold


    ~ For the second algorithm
        
        Local Step Algorithm: 
            Pick a random vertex k and swap it with the next one.  
            Check if (k-1, k) edge and (k+1, k+2) edge intersect with each other (creating an X). 
            If not, then take the (k-1, k, k+1) and (k, k+1, k+2) triangles and 
            check if a vertex exist inside any of the two triangles we created. 
            If the above is false calculated the DE and metropolis criterion.
            If DE < 0 or the metropolis criterion is true, apply the changes

        Global Step Algorithm: 
            It's the same as local search Algorithm, with L = 1.
                
        Subdivisition Algorithm:
            Sort all the points and divide them into ceil([n-1]/[m-1]) parts. Each part will have a common point.
            For each sub-polygon created, calculate the polygon using convex hull algorithm and then 
            improve the area using the global step algorithm. 
            When all ceil([n-1]/[m-1]) sub-polygons are created merge them together and create the final polygon.

Observations:

    While testing the two algorithms, we came to the conclusion that the first algorithm
    is much slower than the first one. 
    Both algorithms improve the final area of the polygon produced by incremental or convex hull algorithms, but the Local Search algorithm although slower it does a much better job finding the best area approximatelly.

    
Some examples can be found in the testcases/results folders, images of the polygon results can be found in images folder. 
    
    