cmake_minimum_required(VERSION 3.15)

project(periculc)

# set errors flag
add_compile_options(-Wall -Werror -Wextra)
add_executable(semm_project main.cpp)


# set C++14 version of C++ 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# add third-party libraries
target_include_directories(semm_project PRIVATE lib/simdjson/)
