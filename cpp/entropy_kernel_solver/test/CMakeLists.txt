set( test test )

set( sources
    testMain.cpp
  )

set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

add_executable( ${test} ${headers} ${sources})

link_directories( ${PROJECT_LIBRARY_DIRS})

target_link_libraries( ${test} 
  eks
)

target_include_directories( ${test}
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/../entropy_kernel_solver
  PRIVATE ${PROJECT_INCLUDE_DIRS}
    )
