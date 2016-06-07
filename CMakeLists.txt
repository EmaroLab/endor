cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_CXX_FLAGS "-g -Wall")

PROJECT(endor)

#find_package(OGDF REQUIRED)
#FIND_PACKAGE(TULIP REQUIRED)

#SET(OGDF_DIR "/home/yeshi/OGDF")
#INCLUDE_DIRECTORIES(/home/yeshi/OGDF/include ${TulipCoreBuildInclude} ${TulipCoreInclude} ${TulipOGLInclude} ${TulipGUIInclude})
#link_directories(/home/yeshi/OGDF/_release)

#FILE(GLOB SOURCES "*.cpp" "*.c" "*.h" "*.hpp")
#ADD_EXECUTABLE(AOgraph ${SOURCES})

ADD_EXECUTABLE(endor
  ./main.cpp
  )

add_library(AndOrLib
        ./aograph.h ./aograph.cpp ./aonode.h ./aonode.cpp
        )

target_link_libraries(endor AndOrLib)