cmake_minimum_required(VERSION 2.8)

project (Delaunay_pic)


IF(CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++0x")
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake_module)

find_package(CGAL REQUIRED QUIET )
message("-- find CGAL")
include(${CGAL_USE_FILE})

find_package(Qt4 REQUIRED QUIET)
message("-- find Qt4")
include(${QT_USE_FILE})

find_package(GSLAM REQUIRED QUIET)
message("-- find GSLAM")

find_package(OpenCV REQUIRED QUIET)
message("-- find OpenCV")

find_package(GLOG REQUIRED QUIET)
message("-- find GLOG")

#include_directories (BEFORE ../../include ./mesher/)
#include_directories (BEFORE ./include)
INCLUDE_DIRECTORIES (BEFORE ./src/MapFusion/)
INCLUDE_DIRECTORIES (BEFORE ./src/mesher/)
INCLUDE_DIRECTORIES (BEFORE ./src/display/)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${GLOG_INCLUDE_DIRS}
        )


SET(SOURCES_FILES
    ./src/test/Delaunay_pic.cpp
    ./src/mesher/Triangler.h
    ./src/mesher/Triangler.cpp
    ./src/display/Display.cpp
    )

LIST(APPEND LINK_LIBS
        ${QT_LIBRARIES}
        ${CGAL_LIBRARIES}
        ${GSLAM_LIBRARIES}
        ${OpenCV_LIBRARIES}
        ${GLOG_LIBRARIES}
        )

add_executable (Delaunay_pic ${SOURCES_FILES} ${example_MOCS})
#add_to_cached_list( CGAL_EXECUTABLE_TARGETS Delaunay_pic )

target_link_libraries( Delaunay_pic ${LINK_LIBS} )





