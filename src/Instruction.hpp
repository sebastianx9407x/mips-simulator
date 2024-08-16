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
    // Layout sets
    static const std::unordered_set<std::string> LAYOUT_DST;
    static const std::unordered_set<std::string> LAYOUT_ST;
    static const std::unordered_set<std::string> LAYOUT_D;
    static const std::unordered_set<std::string> LAYOUT_S;
    static const std::unordered_set<std::string> LAYOUT_TSIMM;
    static const std::unordered_set<std::string> SYSCALL;
    static const std::unordered_set<std::string> LAYOUT_TOFFS;
    static const std::unordered_set<std::string> LAYOUT_TIMM;
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
    // Method
    friend std::ostream &operator<<(std::ostream &os, const Instruction &instruction);

private:
    bool isInLayout(const std::unordered_set<std::string> layout);
};

#endif