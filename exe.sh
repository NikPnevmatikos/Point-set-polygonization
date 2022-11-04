#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/usr/lib/CGAL .
make
./main -edge_selection 3 -initialization 1b -algorithm convex_hull -i testcases/test4.txt -o results/test4.txt