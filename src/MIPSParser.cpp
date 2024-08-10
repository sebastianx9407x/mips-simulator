#include "MIPSParser.hpp"
#include <fstream>
#include <iostream>


MIPSParser::MIPSParser(const std::string& inputfile)
    : filename(inputfile) {
    
    this->symbolTable = createSymbolTable();
    //this->instructions = createInstrucions();
    // Create symbol tables on first past threw 
    // Open File 
    // Readfile
    // Add symbols

    // Second pass through, create instructions and assign adress

}

MIPSParser::~MIPSParser() {
    // Destructor implementation
}

std::map<std::string, uint32_t> MIPSParser::createSymbolTable(){
    // Open file
    // Iterate through file and only add address on instructions
    // Add labels and data values
    // Open the input file named "input.txt" 
    std::ifstream inputFile(this->filename); 
    std::cout << this->filename << std::endl;
    // Check if the file is successfully opened 
    if (!inputFile.is_open()) { 
        std::cerr << "Failed to open file: " << filename << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
        return this->symbolTable; 
    } 
  
    std::string line; // Declare a string variable to store each 
                 // line of the file 
  
    // Read each line of the file and print it to the 
    // standard output stream 
    std::cout << "File Content: " << std::endl; 
    while (getline(inputFile, line)) { 
        std::cout << line << std::endl; // Print the current line 
    } 
  
    // Close the file 
    inputFile.close(); 
  
    return this->symbolTable; 
}
    
std::vector<Instruction> MIPSParser::createInstrucions()
{
    return this->instructions;
    
}

int main() {
    MIPSParser testOne("assembly_files/example1.asm");
    return 0;
}


