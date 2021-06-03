# Author: Lutz Pape
# Contact: Lutz.Pape@gmail.com

cmake_minimum_required(VERSION 3.1)

project(fish4tools VERSION 0.1)
enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include_directories(cmake)

find_package(Threads REQUIRED)
find_package(dl REQUIRED)
find_package(m REQUIRED)

#XXX Force symbol definition in search.h for hsearch_data
add_definitions("-D_GNU_SOURCE")

add_compile_options(-fPIE -rdynamic)

set(CMAKE_CXX_FLAGS "-std=gnu++11")
include_directories("${CMAKE_SOURCE_DIR}/include")

#### adding the project version number to the header-file
configure_file(include/version.h.in version.h)

################################################################################
# Add fish4tools tools
################################################################################
# add_subdirectory(tools)

################################################################################
# Add fish4tools library
################################################################################
add_subdirectory(lib)

################################################################################
# Add all tests
################################################################################
add_subdirectory(tests)
