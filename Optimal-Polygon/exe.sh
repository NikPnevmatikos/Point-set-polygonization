#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/home/nick/CGAL-5.5.1 -DCMAKE_BUILD_TYPE=Release .
make

./main -edge_selection 2 -initialization 1b -polygonInit incremental -i testcases/test3.txt -o results/test3.txt -L 100 -threshold 1 -min -algorithm simulated_annealing -annealing global