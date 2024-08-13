#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <unordered_set>

class Instruction
{
public:
    // Constructors
    Instruction();
    Instruction(const std::string &curInstruction);
    ~Instruction();
    //
    static const std::unordered_set<std::string> instructionSet;
    // Attributes
    std::string ASMInstruction;
    std::string Mnemonic;
    std::string rdName;
    std::string rsName;
    std::string rtName;
    int16_t Imm;
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;
    std::string Opcode;
    std::string Funct;
    std::string RD;
    std::string RS;
    std::string RT;
    std::string IMM;
};

#endif