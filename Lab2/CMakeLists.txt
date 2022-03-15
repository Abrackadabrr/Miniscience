cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(vtkdemo)
add_executable(spoon spoon.cpp)

# Найдём VTK
find_package(VTK REQUIRED)
# ... и подключим её со всеми её компонентами её нативными средствами
include(${VTK_USE_FILE})

# gmsh укажем явно по кусочкам (потому что он был просто распакован руками)
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/home/evgen/gmshbase/lib/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/home/evgen/gmshbase/include"
)
set(GMSH_LIBRARY gmsh)

target_link_libraries(spoon ${VTK_LIBRARIES})
target_link_libraries(spoon ${GMSH_LIBRARY})
