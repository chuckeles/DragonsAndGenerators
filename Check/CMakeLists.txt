# configure the project
project(Check)

# get some help from pkg-config
find_package(PkgConfig)

# find check
pkg_search_module(CHECK REQUIRED check)

# make sure
if (NOT CHECK_FOUND)
    message(FATAL_ERROR "Check not found")
endif (NOT CHECK_FOUND)
