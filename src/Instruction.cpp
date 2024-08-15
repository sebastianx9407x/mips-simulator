#include "Instruction.hpp"
#include "MIPS.hpp"
#include "Helpers.hpp"
#include <unordered_set>
#include <vector>
#include <string>
#include <stdexcept>

Instruction::Instruction()
{
    // Constructor implementation
}
Instruction::Instruction(const std::string &curInstruction)
    : ASMInstruction(curInstruction)
{
    std::cout << curInstruction << std::endl;
    std::vector instructionTokens = split(curInstruction, ' ');
    std::string mnemonic = instructionTokens[0];
    if (MIPS::INSTRUCTIONMAP.find(mnemonic) == MIPS::INSTRUCTIONMAP.end())
    {
        throw std::runtime_error("Mnemonic not found: " + mnemonic);
    }
    this->mnemonic = mnemonic;
    this->opcode = MIPS::INSTRUCTIONMAP.at(this->mnemonic).opcode;
    this->funct = MIPS::INSTRUCTIONMAP.at(this->mnemonic).funct;

    // Checking output
    std::cout << "mnemonic: " << this->mnemonic << std::endl;
    std::cout << "opcode: " << this->opcode << std::endl;
    if (this->funct.has_value())
    {
        std::cout << "funct: " << *this->funct << std::endl;
    }
    else
    {
        std::cout << "funct: None" << std::endl;
    }
}

Instruction::~Instruction()
{
    // Destructor implementation (can be empty if there's nothing to clean up)
}