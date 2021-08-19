project(business_logic) 

add_library(logic INTERFACE)

target_include_directories(logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
# link libraries
# target_link_libraries(logic PRIVATE nlohmann)

# add the data to the file
# set (RESOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/sample_of_capitals.json)
# set_target_properties(bss PROPERTIES RESOURCE ${RESOURCE_FILE})
# add_custom_target(bss DEPENDS ${RESOURCE_FILE})
# add_dependencies(bss ${RESOURCE_FILE})
