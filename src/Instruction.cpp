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
    std::cout << "mnemonic: " << mnemonic << std::endl;
    if (MIPS::INSTRUCTIONMAP.find(mnemonic) == MIPS::INSTRUCTIONMAP.end())
    {
        throw std::runtime_error("Mnemonic not found: " + mnemonic);
    }
    this->Mnemonic = mnemonic;
}

Instruction::~Instruction()
{
    // Destructor implementation (can be empty if there's nothing to clean up)
}