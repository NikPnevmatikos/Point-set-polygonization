#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/home/nick/CGAL-5.5.1 .
make
#./main -edge_selection 3 -algorithm convex_hull -i testcases/stars200.txt -o results/stars200.txt
#./main -edge_selection 3 -initialization 1b -algorithm incremental -i testcases/test3.txt -o results/test3.txt
#./main -edge_selection 3 -initialization 1b -algorithm incremental -i testcases/paris600.txt -o results/paris600.txt
./main -edge_selection 3 -initialization 1b -algorithm incremental -i /home/nick/Λήψεις/instances/data/images/mona-lisa-1000000.instance -o results/mona-lisa-1000000.txt