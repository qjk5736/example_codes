cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0003 NEW)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

project(2dAlphaBeta VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)

function(print)
	message("${var} = ${${var}}")
endfunction()

print(PROJECT_NAME)
print(CMAKE_CXX_STANDARD)

add_library(
	abf	STATIC
	alpha_beta_filter.h 
	alpha_beta_filter.cpp
) 

add_executable(${PROJECT_NAME} testMain.cpp)

target_link_libraries( ${PROJECT_NAME} PRIVATE abf )




