#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/home/nick/CGAL-5.5.1 -DCMAKE_BUILD_TYPE=Release .
make

./main -i input -o results/examples.txt
