#include "MIPSParser.hpp"
#include "Helpers.hpp"
#include "Globals.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <stdexcept>
#include <algorithm>

const std::unordered_map<std::string, Section> MIPSParser::sectionMap = {
    {".text", TEXT},
    {".data", DATA},
    {".bss", BSS},
    {".rodata", RODATA}};

const std::unordered_set<std::string> MIPSParser::PSEUDO_INSTRUCTIONS = {
    "li",   // Load Immediate
    "la",   // Load Address
    "move", // Move from one register to another
    "bne",  // Branch Not Equal
    "beq",  // Branch Equal
    "blt",  // Branch Less Than
    "bgt",  // Branch Greater Than
    "ble",  // Branch Less Than or Equal
    "bge",  // Branch Greater Than or Equal
    "beqz", // Branch if Equal to Zero
    "bnez", // Branch if Not Equal to Zero
    "not",  // Bitwise Not
    "neg",  // Negate
    "seq",  // Set on Equal
    "sne",  // Set on Not Equal
    "sle",  // Set on Less or Equal
    "sge",  // Set on Greater or Equal
};

MIPSParser::MIPSParser(const std::string &inputfile)
    : inputfile(inputfile), instructionfile(generateCleanName(inputfile))
{
    // Creating instructions and symbol tables
    createTables();
    createInstructions();
}

MIPSParser::~MIPSParser()
{
    // Destructor implementation
}

void MIPSParser::createTables()
{
    // Initializing variables
    uint32_t pc = PC_START;
    uint32_t dataAddress = DATA_START;
    Section curSection = NONE;
    // Opening clean asm file
    std::ifstream asmFile(this->inputfile);
    if (!asmFile)
    {
        throw std::runtime_error("Failed to open file: " + this->inputfile);
        return;
    }
    std::ofstream instrFile(this->instructionfile);
    if (!instrFile)
    {
        throw std::runtime_error("Failed to open file: " + this->instructionfile);
        return;
    }
    std::string curLine;
    std::vector<std::string> stringVector;
    // Proccessing each line
    while (std::getline(asmFile, curLine))
    {
        cleanASMLine(curLine);
        stringVector = split(curLine, ' ');

        // Check if empty string
        if (!stringVector.size())
        {
            continue;
        }
        // Setting global
        if (stringVector[0] == ".globl" && stringVector.size() == 2)
        {
            this->global = stringVector[1];
            continue;
        }
        // Determing section
        auto sectionLoc = sectionMap.find(stringVector[0]);
        if (sectionLoc != sectionMap.end())
        {
            curSection = sectionLoc->second;

            continue;
        }
        // Parsing labels, data, and isntructions
        std::string textLabel;
        std::size_t colonPos;
        std::string instrOne;
        std::string instrTwo;
        Data curData;
        switch (curSection)
        {
        case NONE:
            break;
        case TEXT:
            colonPos = curLine.find(':');
            if (colonPos != std::string::npos)
            {
                textLabel = stringVector[0].substr(0, colonPos);
                this->labelTable[textLabel] = pc;
                if (stringVector.size() > 1)
                {
                    stringVector.erase(stringVector.begin());
                    curLine = curLine.substr(colonPos + 2);
                }
                else
                {
                    continue;
                }
            }
            // Will change function
            instrFile << curLine << std::endl;
            pc += 4;
            break;
        case DATA:
            curData = Data(curLine, dataAddress);
            dataTable[curData.label] = curData;
            dataAddress += 4;
            break;
        case BSS:
            std::cout << "BSS NOT IMPLEMENTED" << std::endl;
            break;
        case RODATA:
            std::cout << "RODATA NOT IMPLEMENTED " << std::endl;
            break;
        default:
            std::cout << "NO MATCHES " << std::endl;
            break;
        }
    }
    asmFile.close();
    instrFile.close();
    return;
}

void MIPSParser::createInstructions()
{
    // Initializing variables
    uint32_t pc = PC_START;
    std::ifstream instrFile(this->instructionfile);
    if (!instrFile)
    {
        throw std::runtime_error("Failed to open file: " + this->instructionfile);
        return;
    }
    std::string curLine;
    std::vector<std::string> stringVector;
    // Proccessing each line
    while (std::getline(instrFile, curLine))
    {
        stringVector = split(curLine, ' ');
        if (PSEUDO_INSTRUCTIONS.find(stringVector[0]) != PSEUDO_INSTRUCTIONS.end())
        {
            pc = handlePseudoInstr(stringVector, pc);
        }
        else
        {
            Instruction curInstr(curLine, pc, this->labelTable, this->dataTable);
            this->instructions.push_back(curInstr);
            pc += 4;
        }
    }
    instrFile.close();
}

void cleanASMLine(std::string &curLine)
{
    // Remove all commas from the line
    std::replace(curLine.begin(), curLine.end(), ',', ' ');

    // Reading only up to comment if existent
    std::size_t pos = curLine.find('#');
    if (pos != std::string::npos)
    {
        curLine = curLine.substr(0, pos);
    }
    // Add a space after each colon if it is not followed by a space
    std::string::size_type i = 0;
    while (i < curLine.size())
    {
        if (curLine[i] == ':')
        {
            // Check if next character is not a space
            if (i + 1 < curLine.size() && curLine[i + 1] != ' ')
            {
                curLine.insert(i + 1, " ");
                i++; // Skip the added space
            }
        }
        i++;
    }

    // Removing trailing whitespace and making spaces a distance of 1 max
    std::istringstream stream(curLine);
    std::string word;
    std::string result;

    while (stream >> word)
    {
        if (!result.empty())
        {
            result += ' ';
        }
        result += word;
    }

    // Update the original string with the normalized result
    curLine = result;
    return;
}

void printFile(const std::string &inputfile)
{
    std::ifstream inputFile(inputfile);
    std::cout << "Filename: " << inputfile << std::endl;
    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Failed to open file: " + inputfile);
    }

    std::string line; // Declare a string variable to store each
                      // line of the file

    // Read each line of the file and print it to the
    // standard output stream
    std::cout << "File Content: " << std::endl;
    while (getline(inputFile, line))
    {
        std::cout << line << std::endl; // Print the current line
    }

    // Close the file
    inputFile.close();
    return;
}

const std::string generateCleanName(const std::string &filename)
{
    // Define the extension to be replaced
    const std::string extension = ".asm";

    // Check if the filename ends with the specified extension
    if (filename.size() > extension.size() &&
        filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0)
    {
        // Create the new filename by replacing the extension with "_clean.asm"
        return filename.substr(0, filename.size() - extension.size()) + "_instructions" + extension;
    }

    // Return the original filename if it does not end with ".asm"
    return filename;
}

uint32_t MIPSParser::handlePseudoInstr(std::vector<std::string> &stringVector, uint32_t pc)
{
    std::string instrOne = "";
    std::string instrTwo = "";
    std::string regOne;
    std::string regTwo;
    std::string label;
    std::string immStr;
    std::int32_t imm;
    Data data;
    // Will change function
    if (stringVector[0] == "li")
    {
        validateVectorSize(3, stringVector);
        regOne = stringVector[1];
        immStr = stringVector[2];
        imm = handleValue(immStr);

        if (fitsIn16Bits(imm))
        {
            instrOne = std::format("addi {} $zero {}", regOne, imm);
        }
        else
        { // First line
            std::int16_t upper = static_cast<std::int16_t>(imm >> 16);
            instrOne = std::format("lui {} {}", regOne, upper);
            // Second line
            std::int16_t lower = imm & 0xFFFF;
            instrTwo = std::format("ori {} {} {}", regOne, regOne, lower);
        }
    }
    else if (stringVector[0] == "la")
    {
        validateVectorSize(3, stringVector);
        regOne = stringVector[1];
        data = this->dataTable.at(stringVector[2]);
        imm = data.address;
        if (fitsIn16Bits(imm))
        {
            instrOne = std::format("addi {} $zero {}", regOne, imm);
        }
        else
        { // First line
            std::int16_t upper = static_cast<std::int16_t>(imm >> 16);
            instrOne = std::format("lui {} {}", regOne, upper);
            // Second line
            std::int16_t lower = imm & 0xFFFF;
            instrTwo = std::format("ori {} {} {}", regOne, regOne, lower);
        }
    }
    else if (stringVector[0] == "move")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "blt")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "bgt")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "ble")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "bge")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "beqz")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "bnez")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "not")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "neg")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "seq")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "sne")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "sle")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "sge")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "seq")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else if (stringVector[0] == "seq")
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    else
    {
        throw std::runtime_error("pseudocode not supported: " + stringVector[0]);
    }
    // Adding new instructions
    if (!instrOne.empty())
    {
        Instruction curInstr(instrOne, pc, this->labelTable, this->dataTable);
        this->instructions.push_back(curInstr);
        pc += 4;
    }
    if (!instrTwo.empty())
    {
        Instruction curInstr(instrTwo, pc, this->labelTable, this->dataTable);
        this->instructions.push_back(curInstr);
        pc += 4;
    }

    return pc;
}