project(business_logic)

add_executable(bss main.cpp)

# link libraries
target_link_libraries(bss PRIVATE nlohmann)
