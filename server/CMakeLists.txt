cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)
set(CMAK_CXX_STANDARD_REQUIRED TRUE)
project(cpp_web_server)

############################################## SERVER ##################################################
add_subdirectory(boost_beast)
add_executable(${PROJECT_NAME} server.cpp)

target_link_libraries(${PROJECT_NAME} boost_beast)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../cmake/)
# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_net REQUIRED)
# 
# include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIR})
# target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_NET_LIBRARY})
