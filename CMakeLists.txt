# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MIPSSimulatorProject VERSION 1.0)

# Add executable and linking files
add_executable(MIPSSimulator
    src/MIPS.cpp
    src/MIPSParser.cpp
    src/Instruction.cpp
    src/Helpers.cpp
)

# Copy assembly files to the build directory
add_custom_command(TARGET MIPSSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assembly_files
    ${CMAKE_BINARY_DIR}/assembly_files
)

# Include directories for header files
target_include_directories(MIPSSimulator PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



