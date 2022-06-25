# CMakeList.txt : CMake project for threebody_cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("threebody_cpp")

# Add source to this project's executable.
add_executable (threebody_cpp "threebody_sim.cpp" "threebody_sim.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET threebody_cpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
