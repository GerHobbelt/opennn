include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(simple_function_regressionSrcs main.cpp)
add_executable(simple_function_regression ${simple_function_regressionSrcs})
target_link_libraries(simple_function_regression libOpenNN)

install(TARGETS simple_function_regression DESTINATION bin)
