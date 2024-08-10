#ifndef MIPSPARSER_HPP
#define MIPSPARSER_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Instruction.hpp"

class MIPSParser {
public:
    // Constructor
    MIPSParser(const std::string& filename);
    ~MIPSParser();
    // File Name
    std::string filename;
    // Table to map label to adress for jumping
    std::map<std::string, uint32_t> symbolTable; 
    // List of each instruction sequentially found in file
    std::vector<Instruction> instructions; 
private:
    // Getting symbol table 
    std::map<std::string, uint32_t> createSymbolTable();
    // Creating instructions 
    std::vector<Instruction> createInstrucions();
    // Method to open file
    void readFile();
    // Method to handle each line
    void parseLine(const std::string& line);
    // Method to output an error if wrong syntax is used
    void reportSyntaxError(const std::string& message);
    // Current address being processed
    uint32_t currentAddress;
};

#endif