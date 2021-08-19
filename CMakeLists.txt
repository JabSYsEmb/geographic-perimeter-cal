cmake_minimum_required(VERSION 3.15)

project(PerimeterCalculator)

# set errors flag
add_compile_options(-Wall -Werror -Wextra)


# set C++17 version of C++ 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# subdirectiories of the project
add_subdirectory(lib/nlohmann)
# add_subdirectory(lib/simdjson)
add_subdirectory(src)
