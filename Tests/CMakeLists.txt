# configure the project
project(DragonsAndGeneratorsTests)

# add test files
set(TEST_FILES Main.c)

# build the test executable
add_executable(DragonsAndGeneratorsTests ${TEST_FILES})

# add cmake test
add_test(DragonsAndGeneratorsTests ${CMAKE_CURRENT_BINARY_DIR}/DragonsAndGeneratorsTests)
