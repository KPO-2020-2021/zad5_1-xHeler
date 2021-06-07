#!/bin/bash

if [[ ! -f build ]]
then
    mkdir build
fi

cd build 

cmake ..

make

clear

./test/complex_test
