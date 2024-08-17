#ifndef MIPS_HPP
#define MIPS_HPP

#include "Instruction.hpp"
#include "MIPSParser.hpp"
#include "Data.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

class MIPS
{
public:
    MIPS();
    MIPS(const std::string &file);
    ~MIPS();
    // Table to map label to adress for jumping
    std::unordered_map<std::string, uint32_t> &labelTable;
    // Data tables
    std::unordered_map<std::string, Data> &dataTable;
    // List of each instruction sequentially found in file
    std::vector<Instruction> &instructions;
    std::string &global;

private:
    MIPSParser parser;
};

#endif