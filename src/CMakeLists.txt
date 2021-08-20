project(business_logic) 

add_library(logic INTERFACE)

target_include_directories(logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
