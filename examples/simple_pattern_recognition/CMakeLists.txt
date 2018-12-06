include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(simple_pattern_recognitionSrcs main.cpp)
add_executable(simple_pattern_recognition ${simple_pattern_recognitionSrcs})
target_link_libraries(simple_pattern_recognition libOpenNN)

install(TARGETS simple_pattern_recognition DESTINATION bin)
