# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("Hux")

file(GLOB_RECURSE C_CPP_FILES "src/*.h" "src/*.c" "src/*.cpp" "src/*.hpp")

message("Now OS is: " ${CMAKE_SYSTEM_NAME})
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
add_definitions(-DLINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
add_definitions(-DWINDOWS)
endif()

set(CMAKE_CXX_STANDARD 14)
add_executable (Hux "main.cpp" ${C_CPP_FILES} )
