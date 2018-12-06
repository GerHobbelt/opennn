include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(logical_operationsSrcs main.cpp)
add_executable(logical_operations ${logical_operationsSrcs})
target_link_libraries(logical_operations libOpenNN)

install(TARGETS logical_operations DESTINATION bin)
