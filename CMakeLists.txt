cmake_minimum_required(VERSION 3.12.0 FATAL_ERROR)

project (space_pirates CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${space_pirates_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/headers/")

file(GLOB_RECURSE space_pirates_CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE space_pirates_H_SOURCES "src/*.h")

add_executable(space_pirates ${space_pirates_CPP_SOURCES} ${space_pirates_H_SOURCES})

target_link_libraries(space_pirates ${SDL2_LIBRARIES} SDL2_image)

add_custom_command(TARGET space_pirates PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:space_pirates>/data)
