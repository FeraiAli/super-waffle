cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(Boost 1.40.0 REQUIRED system)
include_directories(${Boost_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp" "*.ipp")
add_library(boost_beast SHARED ${SOURCES})
target_link_libraries(boost_beast ${Boost_SYSTEM_LIBRARY})

target_include_directories(boost_beast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
