cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)
set(CMAK_CXX_STANDARD_REQUIRED TRUE)
project(cpp_web_client)
############################################# CLIENT ##################################################
set(CMAKE_SYSTEM_NAME Emscripten)
set(EMSCRIPTEN TRUE)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

add_executable(${PROJECT_NAME} client.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
target_compile_definitions(${PROJECT_NAME} PUBLIC -DEMSCRIPTEN=1)

set(EMSCRIPTEN_PATH "${CMAKE_CURRENT_LIST_DIR}/../../emscripten/emsdk/emscripten/1.38.21/")
set(CMAKE_C_COMPILER "${EMSCRIPTEN_PATH}/emcc")
set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_PATH}/em++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_NET=2 -s WASM=0")

include_directories(/emscripten/ ${EMSCRIPTEN_PATH}/system/include/)
