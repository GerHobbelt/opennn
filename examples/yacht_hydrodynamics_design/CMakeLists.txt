include_directories(${CMAKE_SOURCE_DIR}/opennn)

set(yacht_hydrodynamics_designSrcs main.cpp)
add_executable(yacht_hydrodynamics_design ${yacht_hydrodynamics_designSrcs})
target_link_libraries(yacht_hydrodynamics_design libOpenNN)

install(TARGETS yacht_hydrodynamics_design DESTINATION bin)
