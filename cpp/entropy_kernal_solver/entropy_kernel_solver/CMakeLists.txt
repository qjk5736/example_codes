set( target eks )

set( sources
  ./entropy_kernel_solver.cpp
)

set( headers
  ./entropy_kernel_solver.h
)

set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

add_library( ${target} ${CMAKE_CURRENT_SOURCE_DIR}/${sources} ${CMAKE_CURRENT_SOURCE_DIR}/${headers} )



