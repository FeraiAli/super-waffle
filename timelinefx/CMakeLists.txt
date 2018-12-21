cmake_minimum_required(VERSION 3.7)
# TODO - Add source_control (github) support
# TODO - Add static_analyzer tool (cpp_check) on commit
# TODO - Add continuous integration (Travis CI)
# TODO - Add code coverage analysis (lcov, coveralls)
# TODO - Add llvm based tools (include-what-you-use, clang-modernize, clang-check clang-tidy)

############################################## SET COMPILE OPTIONS ##################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SANITIZE_ADDRESS    FALSE)
set(SANITIZE_MEMORY     FALSE)
set(SANITIZE_UNDEFINED  FALSE)
set(SANITIZE_THREAD     FALSE)
add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)

project(timelinefx)

############################################## CMAKE FIND PACKAGES ##################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../cmake/)
find_package(Sanitizers)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
find_package(PugiXML REQUIRED)

############################################## ADD SUBDIRECTORIES ###################################################
add_subdirectory(core)
add_subdirectory(DataStructures)
add_subdirectory(Events)
add_subdirectory(SpriteBatcher)
add_subdirectory(ParticleTimelineFX)

############################################## ADD EXECUTABLE ########################################################
add_executable(${PROJECT_NAME} main.cpp)
add_sanitizers(${PROJECT_NAME})

############################################## INCLUDE DIRECTORIES ###################################################
include_directories(
    ${SFML_INCLUDE_DIR}
    ${PUGIXML_INCLUDE_DIR}
)

############################################## LINK TARGET PROJECT ###################################################
target_link_libraries(
    ${PROJECT_NAME}
    ${SFML_LIBRARIES}
    ${PUGIXML_LIBRARIES}
    core
    DataStructures
    Events
    SpriteBatcher
    ParticleTimelineFX
)
