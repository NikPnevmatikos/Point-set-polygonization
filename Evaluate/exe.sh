#!/bin/bash

cgal_create_CMakeLists -s main
cmake -DCGAL_DIR=/user/lib/CGAL -DCMAKE_BUILD_TYPE=Release .
make

./main -i input -o results/examples.txt
