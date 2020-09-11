# CMakeList.txt : CMake project for RVM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (rasm "main.cpp" "rvmassembler.cpp" "mapper.cpp" "mapper.h" "rvmassembler.h" "types.h")

# TODO: Add tests and install targets if needed.