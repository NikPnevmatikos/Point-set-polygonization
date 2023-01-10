# Point-set-polygonization / Evaluate

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
    $./main -i <point set path> -ο <output file>

To compile and run the program you can use the exe.sh bash script:

    chmod x+u exe.sh    (only need this for the first time you compile-run)
    ./exe.sh            (for every other time you want to compile-run)


Input file should be in this form:

         || <Algorithm 1>                                 || <Algorithm 2>           || . . .
    Size || min score | max score | min bound | max bound || <same cols as previously>
    10   || <double> | <double> | <double> | <double>     || . . .
    20   || . . .
    30
    40
    50
    60
    70
    80
    90
    100
    200
    400
    800
    1000
    2000
    5000
    10000
    100000


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
                            (run 2 set of algorithms and writes the result into desired file)

    exe.sh                  (used to compile and run the programs)


    localSearch.h
    localSearch.cpp         (implementation for the local Search algorithm)

    optimal_convex.h
    optimal_convex.cpp      (updated convex hull algorithm for the sub-division)

    simulatedAnnealing.h
    simulatedAnnealing.cpp  (implementation for the simulatedAnnealing algorithm)
    


Program Description:

    Implemented a script to run two algorithm on any given file in a directory. Calculate the ratio between area produced by algorithms and convex hull area. The result is written into the desired output file.

Observations:

    While implemented the task, we came to the conclusion that the most consistand and fast algorithms to use are incremental-simulated annealing(local step) and convex hull-simulated annealing(global step). The second algorithm is much slower that the first one but produces better area results. Other algorithm compinations were slower or produced poor results (example convex hull-local search)

Code improvements:

    We improved the runtime of our code by:
        -Cutting unnecessary checks in convex hull algorithm.
        -Calculate the area of the polygon using triangles instead of using the polygon area
            function
        -Avoiding unnecessary checks in Simulated_Annealing(local Step)at the intersect
            function
        -Changing the visibility check in simulated_Annealing
        -Avoiding unnecessary checks in incremental algorithm by changing the visibility
            check.
    
Some examples can be found in the input folder, and results can be found in results folder. 
    
    