#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/usr/lib/CGAL -DCMAKE_BUILD_TYPE=Release .
make
#./main -edge_selection 3 -algorithm convex_hull -i testcases/stars200.txt -o results/stars200.txt
#./main -edge_selection 3 -initialization 1b -algorithm incremental -i testcases/test3.txt -o results/test3.txt
./main -edge_selection 3 -initialization 1b -polygonInit incremental -i testcases/test3.txt -o results/test3.txt -L 100 -threshold 1000 -max -algorithm simulated_annealing
#./main -edge_selection 3 -initialization 1b -algorithm incremental -i testcases/paris600.txt -o results/paris600.txt