#ifndef MIPS_HPP
#define MIPS_HPP

#include "Instruction.hpp"
#include "MIPSParser.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

// Define a structure to hold the register information
struct RegisterInfo
{
    uint32_t decVal;    // The integer representation
    std::string binStr; // The binary string representation
};

struct InstructionInfo
{
    std::string opcode;                  // The opcode in binary string form
    std::optional<std::string> function; // The function in binary string form (optional)
};

class MIPS
{
public:
    MIPS();
    MIPS(const std::string &file);
    ~MIPS();
    // Table to map label to adress for jumping
    std::unordered_map<std::string, uint32_t> &labelTable;
    // Data tables
    std::unordered_map<std::string, std::string> &dataTable;
    // List of each instruction sequentially found in file
    std::vector<Instruction> &instructions;
    std::string &global;
    static const std::unordered_map<std::string, RegisterInfo> REGISTERMAP;
    static const std::unordered_map<std::string, InstructionInfo> INSTRUCTIONMAP;

private:
    MIPSParser parser;
};

#endif