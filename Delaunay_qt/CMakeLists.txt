# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

project (cgal)

cmake_minimum_required(VERSION 2.6.2)
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER 2.8.3)
  cmake_policy(VERSION 2.8.4)
else()
  cmake_policy(VERSION 2.6)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")


find_package(CGAL REQUIRED QUIET )
##find_package(CGAL QUIET COMPONENTS Core )

message("-- find CGAL")
include(${CGAL_USE_FILE})

find_package(Qt4 REQUIRED QUIET)
message("-- find Qt4")
include(${QT_USE_FILE})

include_directories (BEFORE ../../include ./)
include_directories (BEFORE ./include)

#QT4_WRAP_CPP(example_MOCS MyWidget.h)

add_executable  ( cgal MyWidget.cpp Triangler.cpp ${example_MOCS})
#set_target_properties(cgal PROPERTIES AUTOMOC ON)
add_to_cached_list( CGAL_EXECUTABLE_TARGETS cgal )

target_link_libraries( cgal ${QT_LIBRARIES} )
target_link_libraries( cgal ${CGAL_LIBRARIES} )



