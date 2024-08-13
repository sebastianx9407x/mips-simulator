#include "MIPS.hpp"
#include "MIPSParser.hpp"
#include "Instruction.hpp"
#include "Helpers.hpp"
#include <string>
#include <vector>
#include <cstdint>

const std::unordered_map<std::string, RegisterInfo> registerMap = {
    {"$zero", {0, toBinaryString(0)}},
    {"$at", {1, toBinaryString(1)}},
    {"$v0", {2, toBinaryString(2)}},
    {"$v1", {3, toBinaryString(3)}},
    {"$a0", {4, toBinaryString(4)}},
    {"$a1", {5, toBinaryString(5)}},
    {"$a2", {6, toBinaryString(6)}},
    {"$a3", {7, toBinaryString(7)}},
    {"$t0", {8, toBinaryString(8)}},
    {"$t1", {9, toBinaryString(9)}},
    {"$t2", {10, toBinaryString(10)}},
    {"$t3", {11, toBinaryString(11)}},
    {"$t4", {12, toBinaryString(12)}},
    {"$t5", {13, toBinaryString(13)}},
    {"$t6", {14, toBinaryString(14)}},
    {"$t7", {15, toBinaryString(15)}},
    {"$s0", {16, toBinaryString(16)}},
    {"$s1", {17, toBinaryString(17)}},
    {"$s2", {18, toBinaryString(18)}},
    {"$s3", {19, toBinaryString(19)}},
    {"$s4", {20, toBinaryString(20)}},
    {"$s5", {21, toBinaryString(21)}},
    {"$s6", {22, toBinaryString(22)}},
    {"$s7", {23, toBinaryString(23)}},
    {"$t8", {24, toBinaryString(24)}},
    {"$t9", {25, toBinaryString(25)}},
    {"$k0", {26, toBinaryString(26)}},
    {"$k1", {27, toBinaryString(27)}},
    {"$gp", {28, toBinaryString(28)}},
    {"$sp", {29, toBinaryString(29)}},
    {"$fp", {30, toBinaryString(30)}},
    {"$ra", {31, toBinaryString(31)}}};

// Define and initialize the static const map of instructions
const std::unordered_map<std::string, InstructionInfo> instructionMap = {
    // Arithmetic and Logical Instructions
    {"add", {"000000", "100000"}},
    {"addu", {"000000", "100001"}},
    {"sub", {"000000", "100010"}},
    {"subu", {"000000", "100011"}},
    {"mult", {"000000", "011000"}},
    {"multu", {"000000", "011001"}},
    {"div", {"000000", "011010"}},
    {"divu", {"000000", "011011"}},
    {"and", {"000000", "100100"}},
    {"or", {"000000", "100101"}},
    {"xor", {"000000", "100110"}},
    {"nor", {"000000", "100111"}},
    {"sll", {"000000", "000000"}},
    {"srl", {"000000", "000010"}},
    {"sra", {"000000", "000011"}},
    {"slt", {"000000", "101010"}},
    {"sltu", {"000000", "101011"}},

    // Data Transfer Instructions
    {"lw", {"100011", std::nullopt}},
    {"sw", {"101011", std::nullopt}},
    {"lb", {"100000", std::nullopt}},
    {"sb", {"101000", std::nullopt}},
    {"lbu", {"100100", std::nullopt}},
    {"lh", {"100001", std::nullopt}},
    {"sh", {"101001", std::nullopt}},
    {"lui", {"001111", std::nullopt}},

    // Branch and Jump Instructions
    {"beq", {"000100", std::nullopt}},
    {"bne", {"000101", std::nullopt}},
    {"bgtz", {"000111", std::nullopt}},
    {"bltz", {"000001", std::nullopt}},
    {"j", {"000010", std::nullopt}},
    {"jal", {"000011", std::nullopt}},
    {"jr", {"000000", "001000"}},

    // Immediate Instructions
    {"addi", {"001000", std::nullopt}},
    {"addiu", {"001001", std::nullopt}},
    {"andi", {"001100", std::nullopt}},
    {"ori", {"001101", std::nullopt}},
    {"xori", {"001110", std::nullopt}},
    {"slti", {"001010", std::nullopt}},
    {"sltiu", {"001011", std::nullopt}},

    // Special Instructions
    {"nop", {"000000", "000000"}},
    {"syscall", {"000000", "001100"}}};

int main()
{
    std::string filename = "assembly_files/example1.asm";
    MIPS mips(filename);

    return 0;
}

MIPS::MIPS(const std::string &filename)
    : parser(filename), labelTable(parser.labelTable), dataTable(parser.dataTable), instructions(parser.instructions), global(parser.global)
{
}

MIPS::~MIPS()
{
}