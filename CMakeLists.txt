# configure cmake
cmake_minimum_required(VERSION 2.8)

# silent a warning
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# configure the project
project(DragonsAndGenerators)
set(CMAKE_C_STANDARD 90)

# add the findcheck module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} CMakeModules)

# enable testing
enable_testing()

# add include files
include_directories(Include)

# add source files
set(SOURCE_FILES Source/Main.c)

# build the project executable
add_executable(DragonsAndGenerators ${SOURCE_FILES})
