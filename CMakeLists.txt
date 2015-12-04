# configure cmake
cmake_minimum_required(VERSION 2.8)

# configure the project
project(DragonsAndGenerators)
set(CMAKE_C_STANDARD 90)

# add source files
set(SOURCE_FILES Source/Main.c)

# build the project executable
add_executable(DragonsAndGenerators ${SOURCE_FILES})
