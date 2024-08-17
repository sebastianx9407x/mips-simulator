#include "Instruction.hpp"
#include "MIPS.hpp"
#include "Helpers.hpp"
#include <stdexcept>

const std::unordered_map<std::string, int> Instruction::LAYOUT_INPUT_SIZES = {
    {"DST", 4},      //  $d, $s, $t
    {"ST", 3},       // mult $s, $t
    {"S", 2},        // jr $s
    {"DTIMM", 4},    // sll $d, $t, shamt
    {"TSIMM", 4},    // addi $t, $s, imm
    {"TIMM", 3},     // lui $t, imm
    {"STOFF", 4},    // beq $s, $t, offset
    {"TOFFS", 3},    // lw $t, offset($s)
    {"SOFF", 3},     // bgtz $s, offset
    {"TARG", 2},     // j target
    {"SYSCALL", 1}}; // syscall

const std::unordered_map<std::string, std::function<void(Instruction &, std::vector<std::string> &)>> Instruction::MNEMONIC_FUNCTION_MAP = {
    {"add", parseDST},  // add $d, $s, $t
    {"addu", parseDST}, // addu $d, $s, $t
    {"sub", parseDST},  // sub $d, $s, $t
    {"subu", parseDST}, // subu $d, $s, $t
    {"and", parseDST},  // and $d, $s, $t
    {"or", parseDST},   // or $d, $s, $t
    {"xor", parseDST},  // xor $d, $s, $t
    {"nor", parseDST},  // nor $d, $s, $t
    {"slt", parseDST},  // slt $d, $s, $t
    {"sltu", parseDST}, // sltu $d, $s, $t

    {"mult", parseST},  // mult $s, $t
    {"multu", parseST}, // multu $s, $t
    {"div", parseST},   // div $s, $t
    {"divu", parseST},  // divu $s, $t

    {"jr", parseS}, // jr $s

    {"sll", parseDTIMM}, // sll $d, $t, shamt
    {"srl", parseDTIMM}, // srl $d, $t, shamt
    {"sra", parseDTIMM}, // sra $d, $t, shamt

    {"addi", parseTSIMM},  // addi $t, $s, imm
    {"addiu", parseTSIMM}, // addiu $t, $s, imm
    {"andi", parseTSIMM},  // andi $t, $s, imm
    {"ori", parseTSIMM},   // ori $t, $s, imm
    {"xori", parseTSIMM},  // xori $t, $s, imm
    {"slti", parseTSIMM},  // slti $t, $s, imm
    {"sltiu", parseTSIMM}, // sltiu $t, $s, imm

    {"lui", parseTIMM}, // lui $t, imm

    {"beq", parseSTOFF}, // beq $s, $t, offset
    {"bne", parseSTOFF}, // bne $s, $t, offset

    {"lw", parseTOFFS},  // lw $t, offset($s)
    {"sw", parseTOFFS},  // sw $t, offset($s)
    {"lb", parseTOFFS},  // lb $t, offset($s)
    {"sb", parseTOFFS},  // sb $t, offset($s)
    {"lbu", parseTOFFS}, // lbu $t, offset($s)
    {"lh", parseTOFFS},  // lh $t, offset($s)
    {"sh", parseTOFFS},  // sh $t, offset($s)

    {"bgtz", parseSOFF}, // bgtz $s, offset
    {"bltz", parseSOFF}, // bltz $s, offset

    {"j", parseTARG},   // j target
    {"jal", parseTARG}, // jal target

    {"syscall", parseSyscall} // syscall
};

Instruction::Instruction()
{
    // Constructor implementation
}
Instruction::Instruction(const std::string &curInstruction)
    : ASMInstruction(curInstruction)
{
    std::vector tokens = split(curInstruction, ' ');
    std::string mnemonic = tokens[0];
    if (MIPS::INSTRUCTIONMAP.find(mnemonic) == MIPS::INSTRUCTIONMAP.end())
    {
        throw std::runtime_error("Mnemonic not found: " + mnemonic);
    }
    this->mnemonic = mnemonic;
    this->opcode = MIPS::INSTRUCTIONMAP.at(this->mnemonic).opcode;
    this->funct = MIPS::INSTRUCTIONMAP.at(this->mnemonic).funct;

    // Adding registers
    parseInstruction(*this, tokens);
    std::cout << *this << std::endl;
}

Instruction::~Instruction()
{
    // Destructor implementation (can be empty if there's nothing to clean up)
}

// Define the operator<< function
std::ostream &operator<<(std::ostream &os, const Instruction &instruction)
{
    os << "Instruction: " << instruction.ASMInstruction << "\n"
       << "Mnemonic: " << instruction.mnemonic << "\n"
       << "Opcode: " << instruction.opcode << "\n"
       << "Funct: " << (instruction.funct ? *instruction.funct : "None") << "\n";
    return os;
}

/**
 * Validates if there are enough tokens for instruction
 */
void validateVectorSize(Instruction &instr, std::string layout, std::vector<std::string> &toks)
{
    try
    {
        int expectedSize = Instruction::LAYOUT_INPUT_SIZES.at(layout);

        if (toks.size() != expectedSize)
        {
            throw std::runtime_error("Incorrect number of tokens for instruction: " + instr.ASMInstruction);
        }
    }
    catch (const std::out_of_range &)
    {
        throw std::runtime_error("Layout not found in size mapping: " + layout);
    }
}

/**
 * Parses all instructions with specific layouts
 */
void Instruction::parseInstruction(Instruction &instr, std::vector<std::string> &toks)
{
    try
    {
        auto func = Instruction::MNEMONIC_FUNCTION_MAP.at(instr.mnemonic);
        func(instr, toks);
    }
    catch (const std::out_of_range &e)
    {
        throw std::runtime_error("Mnemonic not mapped to a function");
    }
}

/**
 * Format:
 * mnemonic $d, $s, $t
 */
void Instruction::parseDST(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $s, $t
 */
void Instruction::parseST(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $s
 */
void Instruction::parseS(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $t, $s imm
 */
void Instruction::parseDTIMM(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $t, $s imm
 */
void Instruction::parseTSIMM(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $t, imm
 */
void Instruction::parseTIMM(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $s, $t, offset
 */
void Instruction::parseSTOFF(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $t, offset($s)
 */
void Instruction::parseTOFFS(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic $s, offset
 */
void Instruction::parseSOFF(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * mnemonic target
 */
void Instruction::parseTARG(Instruction &instr, std::vector<std::string> &toks)
{
}

/**
 * Format:
 * syscall
 */
void Instruction::parseSyscall(Instruction &instr, std::vector<std::string> &toks)
{
}
