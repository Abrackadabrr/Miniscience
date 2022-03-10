cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(gmshdemo)
add_executable(thoros Step1/thoros.cpp)
add_executable(spoon Step2/spoon_mesh.cpp)
add_executable(circle_step_zero Step_0/circle.cpp)
add_executable(cube_step_zero Step_0/cube.cpp)
add_executable(cylindr_step_zero Step_0/cylindr.cpp)

# gmsh укажем явно (потому что он был просто распакован руками)
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/home/evgen/gmshbase/lib/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/home/evgen/gmshbase/include"
)
set(GMSH_LIBRARY gmsh)

# Укажем библиотеки для линковки
target_link_libraries(thoros ${GMSH_LIBRARY})
target_link_libraries(circle_step_zero ${GMSH_LIBRARY})
target_link_libraries(cube_step_zero ${GMSH_LIBRARY})
target_link_libraries(spoon ${GMSH_LIBRARY})
target_link_libraries(cylindr_step_zero ${GMSH_LIBRARY})
