#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/user/lib/CGAL -DCMAKE_BUILD_TYPE=Release .
make

./main -edge_selection 2 -initialization 1b -polygonInit incremental -i testcases/test3.txt -o results/test3.txt -L 100 -threshold 1 -min -algorithm simulated_annealing -annealing global
