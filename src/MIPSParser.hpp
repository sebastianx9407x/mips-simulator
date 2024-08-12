#ifndef MIPSPARSER_HPP
#define MIPSPARSER_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Instruction.hpp"

class MIPSParser {
public:
    // Constructor
    MIPSParser(const std::string& inputfile);
    ~MIPSParser();
    // File Name
    const std::string inputfile;
    const std::string cleanfile;
    // Table to map label to adress for jumping
    std::map<std::string, uint32_t> symbolTable; 
    // List of each instruction sequentially found in file
    std::vector<Instruction> instructions; 
private:
    // Getting symbol table 
    void createSymbolTable();
    // Creating instructions 
    void createInstrucions();
    // Method to open file
    void readFile();
    // Method to handle each line
    void parseLine(const std::string& line);
    // Method to output an error if wrong syntax is used
    void reportSyntaxError(const std::string& message);
    // Current address being processed
    uint32_t currentAddress;


};

// Enum to represent the current section of the assembly file
enum Section {
    NONE,   // No section
    TEXT,   // .text section
    DATA,   // .data section
    BSS,    // .bss section
    RODATA, // .rodata section
    KTEXT,  // .ktext section
    KDATA   // .kdata section
};

void cleanASMFile(const std::string& inputfile, const std::string& outfile);
void cleanASMLine(std::string& curLine);
void printFile(const std::string& inputfile);
const std::string generateCleanName(const std::string& filename);

#endif