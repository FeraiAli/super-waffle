cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp" "*.h")
add_library(core SHARED ${SOURCES})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
