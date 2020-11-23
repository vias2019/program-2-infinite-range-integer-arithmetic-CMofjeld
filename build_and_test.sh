#!/usr/bin/env bash

# compile test code
g++ -std=c++11 -g ./Tests/*.cpp InfiniteInt.cpp DEIntQueue.cpp -o ./Build/TestMain

# run compiled tests
valgrind ./Build/TestMain