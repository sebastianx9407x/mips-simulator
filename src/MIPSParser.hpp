#ifndef MIPSPARSER_HPP
#define MIPSPARSER_HPP

#include "Instruction.hpp"
#include "Data.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Enum to represent the current section of the assembly file
enum Section
{
    NONE,   // No section
    TEXT,   // .text section
    DATA,   // .data section
    BSS,    // .bss section
    RODATA, // .rodata section
    // KTEXT,  // .ktext section
    // KDATA   // .kdata section
};

class MIPSParser
{
public:
    // Constructor
    MIPSParser(const std::string &inputfile);
    ~MIPSParser();
    // Pseudo Instructions
    static const std::unordered_set<std::string> PSEUDO_INSTRUCTIONS;
    // File Name
    const std::string inputfile;
    const std::string instructionfile;
    // Table to map label to adress for jumping
    std::unordered_map<std::string, uint32_t> labelTable;
    // Data tables
    std::unordered_map<std::string, Data> dataTable;
    // List of each instruction sequentially found in file
    std::vector<Instruction> instructions;
    std::string global;

private:
    // Handle Pseudo Instruction
    uint32_t handlePseudoInstr(std::vector<std::string> &stringVector, uint32_t pc);

    // Getting symbol table
    void createTables();
    // Create instructions
    void createInstructions();
    // Current address being processed

    uint32_t currentAddress;
    static const std::unordered_map<std::string, Section> sectionMap;
};

void cleanASMFile(const std::string &inputfile, const std::string &outfile);
void cleanASMLine(std::string &curLine);
void printFile(const std::string &inputfile);
const std::string generateCleanName(const std::string &filename);

#endif