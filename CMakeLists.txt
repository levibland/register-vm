# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("RVM")

# Include sub-projects.
add_subdirectory ("rvm")
add_subdirectory ("rvmassembler")

include( CTest )
enable_testing()