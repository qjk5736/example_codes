cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0003 NEW)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

project(ChoelskyDecomp VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)

function(print)
	message("${var} = ${${var}}")
endfunction()

print(PROJECT_NAME)
print(CMAKE_CXX_STANDARD)

add_library(
	chde	STATIC
	Exception.h 
	Exception.cpp
	Choelsky.h 
	Choelsky.cpp
) 


add_executable(${PROJECT_NAME} Choelsky_driver.cpp)

target_link_libraries( ${PROJECT_NAME} PRIVATE chde )