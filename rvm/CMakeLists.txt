# CMakeLists.txt: CMake project for RVM, include source and define 
# project specific logic here
#

cmake_minimum_required(VERSION 3.8)

# Add sources to this project's executable
add_executable(RVM "main.cpp" "rvm.cpp" "rvm.h")

# TODO: add tests and install targets if needed