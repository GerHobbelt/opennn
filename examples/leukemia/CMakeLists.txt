include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(leukemiaSrcs main.cpp)
add_executable(leukemia ${leukemiaSrcs})
target_link_libraries(leukemia libOpenNN)

install(TARGETS leukemia DESTINATION bin)
