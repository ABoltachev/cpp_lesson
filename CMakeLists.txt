cmake_minimum_required(VERSION 3.16)

project(Cpp_Lessons)

set(CMAKE_CXX_STANDARD 17)

add_library(LessonLib SHARED LessonLib.cpp)

add_executable(main main.cpp)

target_link_libraries(main LessonLib)
