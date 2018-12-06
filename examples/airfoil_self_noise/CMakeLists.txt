include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(airfoil_self_noiseSrcs main.cpp)
add_executable(airfoil_self_noise ${airfoil_self_noiseSrcs})
target_link_libraries(airfoil_self_noise libOpenNN)

install(TARGETS airfoil_self_noise DESTINATION bin)
