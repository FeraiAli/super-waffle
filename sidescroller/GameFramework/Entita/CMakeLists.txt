cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")
add_library(Entita SHARED ${SOURCES})

target_include_directories(Entita PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
