#include "Instruction.hpp"

Instruction::Instruction() {
    // Constructor implementation
}
Instruction::Instruction(const std::string& curInstruction) :
    ASMInstruction(curInstruction) {
    
}

Instruction::~Instruction() {
    // Destructor implementation (can be empty if there's nothing to clean up)
}