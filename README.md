# pBot
A project for path finding robots

## Dependencies
- Qt6
- CMake, set `CMAKE_PREFIX_PATH` to folder that contains Qt Modules cmake files, for example, `CMAKE_PREFIX_PATH="~/Qt/6.3.1/macos`
- make (macos or linux) or ninja  
## Build Instructions
Highly recommend using QtCreator to build this project.

For command line building with cmake:
```
cd pBot
mkdir build
cd build
cmake ..
make -j
```
