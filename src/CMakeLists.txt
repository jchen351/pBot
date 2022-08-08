
include_directories(${CMAKE_SOURCE_DIR}/include)
set(LIB_SOURCE
        MapFileIO.cpp
        pMap.cpp pObstacle.cpp)


add_library(pBot ${LIB_SOURCE})