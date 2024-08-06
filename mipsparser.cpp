#include "mipsparser.hpp"
#include <fstream>
#include <iostream>


MIPSParser::MIPSParser(const std::string& filename)
    : file(filename), currentAddress(0) {
    
    this->symbolTable = createSymbolTable();
    this->instructions = createInstrucions();
    // Create symbol tables on first past threw 
    // Open File 
    // Readfile
    // Add symbols

    // Second pass through, create instructions and assign adress

}

std::map<std::string, uint32_t> createSymbolTable(){

}
    
std::vector<Instruction> createInstrucions()
{
    
}


