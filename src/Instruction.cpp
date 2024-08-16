#include "Instruction.hpp"
#include "MIPS.hpp"
#include "Helpers.hpp"
#include <unordered_set>
#include <vector>
#include <string>
#include <stdexcept>

// Definitions of the static const sets
const std::unordered_set<std::string> Instruction::LAYOUT_DST = {
    "add", "addu", "sub", "subu",
    "and", "or", "xor", "nor",
    "slt", "sltu"};

const std::unordered_set<std::string> Instruction::LAYOUT_ST = {
    "mult", "multu", "div", "divu"};

const std::unordered_set<std::string> Instruction::LAYOUT_D = {
    "jr"};

const std::unordered_set<std::string> Instruction::LAYOUT_S = {
    "sll", "srl", "sra"};

const std::unordered_set<std::string> Instruction::LAYOUT_TSIMM = {
    "addi", "addiu", "andi", "ori",
    "xori", "slti", "sltiu"};

const std::unordered_set<std::string> Instruction::LAYOUT_TOFFS = {
    "lw", "sw", "lb", "sb",
    "lbu", "lh", "sh"};

const std::unordered_set<std::string> Instruction::LAYOUT_TIMM = {
    "lui"};

const std::unordered_set<std::string> Instruction::SYSCALL = {
    "syscall"};

Instruction::Instruction()
{
    // Constructor implementation
}
Instruction::Instruction(const std::string &curInstruction)
    : ASMInstruction(curInstruction)
{
    std::vector instructionTokens = split(curInstruction, ' ');
    std::string mnemonic = instructionTokens[0];
    if (MIPS::INSTRUCTIONMAP.find(mnemonic) == MIPS::INSTRUCTIONMAP.end())
    {
        throw std::runtime_error("Mnemonic not found: " + mnemonic);
    }
    this->mnemonic = mnemonic;
    this->opcode = MIPS::INSTRUCTIONMAP.at(this->mnemonic).opcode;
    this->funct = MIPS::INSTRUCTIONMAP.at(this->mnemonic).funct;

    // Adding registers
    if (isInLayout(Instruction::LAYOUT_DST))
    {
    }
    else if (isInLayout(Instruction::LAYOUT_ST))
    {
    }
    else if (isInLayout(Instruction::LAYOUT_D))
    {
    }
    else if (isInLayout(Instruction::LAYOUT_S))
    {
    }
    else if (isInLayout(Instruction::LAYOUT_TSIMM))
    {
    }
    else if (isInLayout(Instruction::LAYOUT_TOFFS))
    {
    }
    else if (isInLayout(Instruction::LAYOUT_TIMM))
    {
    }
    else if (isInLayout(Instruction::SYSCALL))
    {
    }
    else
    {
        std::cout << "No set for this mnemonic" << std::endl;
    }
    std::cout << *this << std::endl;
}

Instruction::~Instruction()
{
    // Destructor implementation (can be empty if there's nothing to clean up)
}

bool Instruction::isInLayout(const std::unordered_set<std::string> layout)
{
    return layout.find(this->mnemonic) != layout.end();
}

// Define the operator<< function
std::ostream &operator<<(std::ostream &os, const Instruction &instruction)
{
    os << "Instruction: " << instruction.ASMInstruction << "\n"
       << "Mnemonic: " << instruction.mnemonic << "\n"
       << "Opcode: " << instruction.opcode << "\n"
       << "Funct: " << (instruction.funct ? *instruction.funct : "None") << "\n";
    return os;
}