include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(pima_indians_diabetesSrcs main.cpp)
add_executable(pima_indians_diabetes ${pima_indians_diabetesSrcs})
target_link_libraries(pima_indians_diabetes libOpenNN)

install(TARGETS pima_indians_diabetes DESTINATION bin)
