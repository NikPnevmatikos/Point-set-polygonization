#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/usr/lib/CGAL .
make
./main -edge_selection 2 -initialization 2a -algorithm incremental -i testcases/test2.txt -o results/test2.txt