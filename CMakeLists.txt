project(pBot LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_subdirectory(tests)
add_subdirectory(src)
add_subdirectory(gui)

include_directories(include)



