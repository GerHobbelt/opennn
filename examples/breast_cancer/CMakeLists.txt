include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(breast_cancerSrcs main.cpp)
add_executable(breast_cancer ${breast_cancerSrcs})
target_link_libraries(breast_cancer libOpenNN)

install(TARGETS breast_cancer DESTINATION bin)
