cmake_minimum_required(VERSION 3.16)

project(Cpp_seminar)

set(CXX_STANDARD 17)

file(GLOB_RECURSE LIB_SOURCES ${CMAKE_SOURCE_DIR}/testlib/*.cpp)

list(REMOVE_ITEM LIB_SOURCES ${CMAKE_SOURCE_DIR}/main.cpp)

add_library(Test_library SHARED ${LIB_SOURCES})

target_compile_definitions(Test_library PUBLIC TESTLIB_EXPORTS)

add_executable(main main.cpp)

target_link_libraries(main Test_library)

include_directories(${CMAKE_SOURCE_DIR})
