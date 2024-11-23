cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cc-wc)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add library
add_library(ccwc_lib src/file_stats_counter.cpp 
                     src/process_arguments.cpp                     
                     include/file_stats_counter.h 
                     include/process_arguments.h )

target_include_directories(ccwc_lib PUBLIC include)

# Add the executable
add_executable(ccwc src/main.cpp)
target_link_libraries(ccwc PRIVATE ccwc_lib)

# Add the test executable
add_executable(ccwc_test test/ccwc_test.cpp 
                         test/catch2/catch.hpp)
target_link_libraries(ccwc_test PRIVATE ccwc_lib)
target_include_directories(ccwc_test PRIVATE test/catch2)
set_target_properties(ccwc_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test" )
