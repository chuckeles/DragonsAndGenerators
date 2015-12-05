# configure the project
project(DragonsAndGeneratorsTests)

# add check include directory
include_directories({$CHECK_INCLUDE_DIRS})

# add test files
set(TEST_FILES Main.c History.c Heap.c Stage.c)

# build the test executable
add_executable(DragonsAndGeneratorsTests ${TEST_FILES})

# link with check and source
target_link_libraries(DragonsAndGeneratorsTests ${CHECK_LIBRARIES} DragonsAndGeneratorsSource)

# add cmake test
add_test(DragonsAndGeneratorsTests ${CMAKE_CURRENT_BINARY_DIR}/DragonsAndGeneratorsTests)
