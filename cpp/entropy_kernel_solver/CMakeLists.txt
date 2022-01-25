
cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0003 NEW)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

project(EntropyKernelSolver VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory( "entropy_kernel_solver" )
add_subdirectory( "test" )





 