project (nlohmann)

add_library(nlohmann INTERFACE)

target_include_directories(nlohmann INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(nlohmann INTERFACE cxx_std_11)
