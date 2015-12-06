# configure the project
project(DragonsAndGeneratorsSource)

# add the source files
set(SOURCE_FILES Heap.c Stage.c Path.c)

# build the source library
add_library(DragonsAndGeneratorsSource ${SOURCE_FILES})
