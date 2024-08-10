# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MIPSSimulatorProject VERSION 1.0)

# Add executable target
add_executable(MIPSSimulator
    MIPSParser.cpp
    Instruction.cpp
)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)