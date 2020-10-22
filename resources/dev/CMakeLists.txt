cmake_minimum_required(VERSION 3.8)
project(VirtualFPGAProject)

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})
find_package(Boost 1.65 COMPONENTS system thread REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found. Either install it, or set the VERILATOR_ROOT environment variable")
endif()

#if (Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#endif()

set(CMAKE_CXX_STANDARD 17)

# Create a new executable target that will contain all your sources
add_executable(VirtualFPGAProject 
    ./sim_main.cpp
    ./UDPClient.hpp
    )

target_link_libraries(VirtualFPGAProject PUBLIC Boost::boost Boost::system Boost::thread)

option(SIM_DLY "Simulation Delay in ms" 1)
option(IT "Iteration per cycle" 10)
add_compile_definitions(SIM_DELAY=${SIM_DLY} IT_PER_CYCLE=${IT})

# Add the Verilated circuit to the target
verilate(VirtualFPGAProject 
  INCLUDE_DIRS "."
  VERILATOR_ARGS -Os -x-assign 0 --pins-uint8
  SOURCES ./top_wrapper.v)
