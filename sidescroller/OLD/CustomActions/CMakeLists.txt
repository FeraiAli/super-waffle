cmake_minimum_required(VERSION 3.7)

############################ RECURSIVELY FIND ALL FILES AND CREATE LIBRARY #############################
set(LIBRARY_NAME CustomActions)
file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")
add_library(${LIBRARY_NAME} SHARED ${SOURCES})

########################################## ENABLE SANITIZERS ###########################################
add_sanitizers(${LIBRARY_NAME})

######################################### INCLUDE DIRECTORIES ##########################################
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
