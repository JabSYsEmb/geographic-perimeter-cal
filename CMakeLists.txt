cmake_minimum_required(VERSION 3.15)

project(PerimeterCalculator)

# set errors flag
add_compile_options(-Wall -Werror -Wextra)


# set C++11 version of C++ 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# add third-party libraries
# target_include_directories(semm_project PRIVATE lib/simdjson/)
add_subdirectory(lib/nlohmann)
add_subdirectory(src)
