cmake_minimum_required(VERSION 0.0)

PROJECT(UCC_VM)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/grammar/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libparser/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libparser/build)

FILE(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE generated_sources ${CMAKE_CURRENT_SOURCE_DIR}/grammar/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/grammar/src/*.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

ADD_LIBRARY(ucc-vm ${sources} ${generated_sources})

target_link_libraries(ucc-vm parser)
