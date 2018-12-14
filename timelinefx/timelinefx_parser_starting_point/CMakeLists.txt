cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")
add_library(timelinefx_parser_starting_point SHARED ${SOURCES})

target_include_directories(timelinefx_parser_starting_point PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
