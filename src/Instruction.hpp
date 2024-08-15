#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <unordered_set>
#include <optional>

class Instruction
{
public:
    // Constructors
    Instruction();
    Instruction(const std::string &curInstruction);
    ~Instruction();
    // Attributes
    std::string ASMInstruction;
    std::string mnemonic;
    std::string rdName;
    std::string rsName;
    std::string rtName;
    int16_t Imm;
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;
    std::string opcode;
    std::optional<std::string> funct;
    std::string RD;
    std::string RS;
    std::string RT;
    std::string IMM;
};

#endif