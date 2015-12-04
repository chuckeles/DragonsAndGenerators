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

# find check
find_library(Check REQUIRED)

# include check
include_directories(${CHECK_INCLUDE_DIRS})

# add test files
set(TEST_FILES Test/Main.c)

# build the test executable
add_executable(DragonsAndGeneratorsTests ${TEST_FILES})

# link with check
target_link_libraries(DragonsAndGeneratorsTests ${CHECK_LIBRARIES})

# add cmake test
add_test(DragonsAndGeneratorsTests ${CMAKE_CURRENT_BINARY_DIR}/DragonsAndGeneratorsTests)
