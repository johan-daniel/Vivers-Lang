cmake_minimum_required(VERSION 3.25.1)

project(vivers)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE EXEC_HEADERS src/*.hpp)
file(GLOB_RECURSE EXEC_SOURCES src/*.cpp)

add_executable(viv ${EXEC_HEADERS} ${EXEC_SOURCES})
add_custom_command(TARGET viv POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/*.viv $<TARGET_FILE_DIR:viv>)
