# MIPS Simulator

A C++ MIPS simulator that executes and debugs MIPS assembly code. This project focuses on accuracy and flexibility, simulating the MIPS instruction set, including arithmetic, logic, control operations, and memory handling.

# Note 

This project is still a work in progess as I will update with a list of instructions supported and intend on adding gui later down the road than entirely terminal based. 

# Goal 

This project aims to achieve a level of similarity to the MARS simulator, an open-source tool for simulating MIPS processors. For reference and inspiration, you can explore the MARS simulator at MARS Simulator.

## Features

- Accurate simulation of MIPS instruction set.
- Support for RISC instructions and memory operations.
- Modular and easy to extend.
- Built with CMake for cross-platform compatibility.

## Requirements

- C++17 or later
- CMake 3.10 or later
- A compatible C++ compiler (e.g., GCC, Clang)

## Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/sebastianx9407x/mips-simulator.git
    cd mips-simulator
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Generate the build files with CMake:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

5. Run the simulator:
    ```sh
    ./mips-simulator
    ```

## Usage

Place your MIPS assembly files in the `assembly_files` directory within the build directory. The simulator will process and execute them.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
