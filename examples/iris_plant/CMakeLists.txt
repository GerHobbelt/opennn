include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(iris_plantSrcs main.cpp)
add_executable(iris_plant ${iris_plantSrcs})
target_link_libraries(iris_plant libOpenNN)

install(TARGETS iris_plant DESTINATION bin)
