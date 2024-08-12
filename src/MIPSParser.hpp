#ifndef MIPSPARSER_HPP
#define MIPSPARSER_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Instruction.hpp"

// Enum to represent the current section of the assembly file
enum Section {
    NONE,   // No section
    TEXT,   // .text section
    DATA,   // .data section
    BSS,    // .bss section
    RODATA, // .rodata section
    // KTEXT,  // .ktext section
    // KDATA   // .kdata section
};

class MIPSParser {
public:
    // Constructor
    MIPSParser(const std::string& inputfile);
    ~MIPSParser();
    // File Name
    const std::string inputfile;
    const std::string cleanfile;
    
    static const std::unordered_map<std::string, Section> sectionMap;
    
    // Table to map label to adress for jumping
    std::unordered_map<std::string, uint32_t> labelTable; 
    // Data tables
    std::unordered_map<std::string, std::string> dataTable; 
    // List of each instruction sequentially found in file
    std::vector<Instruction> instructions; 
    std::string global;
private:
    // Getting symbol table 
    void createSymbolTables();
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

std::vector<std::string> split(const std::string &s, char delim);

void cleanASMFile(const std::string& inputfile, const std::string& outfile);
void cleanASMLine(std::string& curLine);
void printFile(const std::string& inputfile);
const std::string generateCleanName(const std::string& filename);

#endif