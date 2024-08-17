#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <vector>
#include <optional>

struct InstructionInfo
{
    std::string opcode;               // The opcode in binary string form
    std::optional<std::string> funct; // The function in binary string form (optional)
};

// Define a structure to hold the register information
struct RegisterInfo
{
    uint32_t decVal;    // The integer representation
    std::string binStr; // The binary string representation
};

class Instruction
{
public:
    // Constructors
    Instruction();
    Instruction(const std::string &curInstruction);
    ~Instruction();
    // Mapping sizes
    static const std::unordered_map<std::string, int> LAYOUT_INPUT_SIZES;
    // Mapping instructions to parser function
    static const std::unordered_map<std::string, std::function<void(Instruction &, std::vector<std::string> &)>> MNEMONIC_FUNCTION_MAP;
    // Mapping instructions to their binary/decimal representaion
    static const std::unordered_map<std::string, InstructionInfo> INSTRUCTIONMAP;
    // Mapping registers to their binary/decimal representaions
    static const std::unordered_map<std::string, RegisterInfo> REGISTER_MAP;
    // Attributes
    std::string ASMInstruction;
    std::string mnemonic;
    std::string rdName;
    std::string rsName;
    std::string rtName;
    int16_t imm;
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;
    std::string opcode;
    std::optional<std::string> funct;
    std::string rdBit;
    std::string rsBit;
    std::string rtBit;
    std::string immBit;
    std::string label;
    std::string data;
    // Method
    friend std::ostream &operator<<(std::ostream &os, const Instruction &instruction);

private:
    // checking if enough tokens avaibale for instructions
    static void validateVectorSize(const Instruction &instr, std::string layout, const std::vector<std::string> &toks);
    // checking registers validate
    static RegisterInfo validateRegister(const std::string &reg);
    // Setting register values
    static void setRegisters(std::string &reg, std::string &regName, uint8_t &dec, std::string &bit);
    // Setting offset
    static void setOffset(std::string &offset, Instruction &instr);
    // parse instructions
    static void parseInstruction(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $d, $s, $t
    static void parseDST(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $s $t
    static void parseST(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $s
    static void parseS(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $d, $t imm
    static void parseDTIMM(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $t, $s imm
    static void parseTSIMM(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $t, imm
    static void parseTIMM(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $s, $t, offset
    static void parseSTOFF(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $t, offset($s)
    static void parseTOFFS(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic $s, offset
    static void parseSOFF(Instruction &instr, std::vector<std::string> &toks);
    // mnemonic target
    static void parseTARG(Instruction &instr, std::vector<std::string> &toks);
    // syscall
    static void parseSyscall(Instruction &instr, std::vector<std::string> &toks);
};

#endif