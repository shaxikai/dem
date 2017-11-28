cmake_minimum_required(VERSION 2.8)

project (Delaunay_pic)

IF(CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++0x")
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake_module)

find_package(Qt4 REQUIRED QtGui QtCore QtOpengl QtXml)
message("-- find Qt4" ${QT_LIBRARIES})
include(${QT_USE_FILE})

find_package(OpenGL REQUIRED QTIET)
message("-- find OpenGL")

find_package(CGAL REQUIRED QUIET )
message("-- find CGAL ${CGAL_LIBRARIES}")
include(${CGAL_USE_FILE})

find_package(GSLAM REQUIRED QUIET)
message("-- find GSLAM")

find_package(OpenCV REQUIRED QUIET)
message("-- find OpenCV" ${OpenCV_LIBRARIES})

find_package(GLOG REQUIRED QUIET)
message("-- find GLOG")

find_package(QGLViewer REQUIRED QUIET)
message("-- find QGLViewer ${QGLVIEWER_LIBRARY}")


INCLUDE_DIRECTORIES (BEFORE ./src/MapFusion/)
INCLUDE_DIRECTORIES (BEFORE ./src/mesher/)
INCLUDE_DIRECTORIES (BEFORE ./src/display/)
INCLUDE_DIRECTORIES (BEFORE ./src/points/)
INCLUDE_DIRECTORIES (BEFORE ./src/struct_class/)

FIND_LIBRARY(QGLVIEWER_LIBRARY
        NAMES
        libQGLViewer.so.2.5
        libQGLViewer.so.2.5.0
        libQGLViewer.so
        libQGLViewer.so.2
        libQGLViewer.prl
        PATH
        /usr/lib/x86_64-linux-gnu
        /usr/lib
        /usr/local/lib
        )

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${OpenCV_INCLUDE_DIRS}
        ${GLOG_INCLUDE_DIRS}
        ${QGLVIEWER_INCLUDE_DIR}
        )


SET(SOURCES_FILES
    ./src/test/Delaunay_pic.cpp
    ./src/mesher/Triangler.h
    ./src/mesher/Triangler.cpp
    ./src/display/Display.cpp
    ./src/display/Display_qgl.cpp
    ./src/points/Points_filter.cpp
    ./src/struct_class/Struct_Class.cpp
    )

LIST(APPEND LINK_LIBS
        ${QT_LIBRARIES}
        ${CGAL_LIBRARIES}
        ${GSLAM_LIBRARIES}
        ${OpenCV_LIBRARIES}
        ${GLOG_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
        ${QGLVIEWER_LIBRARY}
        )

qt4_automoc(
    ./src/test/Delaunay_pic.cpp
    ./src/mesher/Triangler.cpp
    ./src/display/Display.cpp
    ./src/display/Display_qgl.cpp
    )

add_executable (Delaunay_pic ${SOURCES_FILES} ${example_MOCS})
#add_to_cached_list( CGAL_EXECUTABLE_TARGETS Delaunay_pic )

target_link_libraries( Delaunay_pic ${LINK_LIBS} )





