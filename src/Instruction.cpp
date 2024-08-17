#include "Instruction.hpp"
#include "Helpers.hpp"
#include <stdexcept>
#include <format>
// Mapping Instructions to the correct size for inputs
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

// Mapping Instructions to their functions that parse them
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

// Mapping Instructions to their opcode and function values
const std::unordered_map<std::string, InstructionInfo> Instruction::INSTRUCTIONMAP = {
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
    {"li", {"001101", std::nullopt}},

    // Special Instructions
    {"nop", {"000000", "000000"}},
    {"syscall", {"000000", "001100"}}};

// Mapping Registers to their binary and decimal representations
const std::unordered_map<std::string, RegisterInfo> Instruction::REGISTER_MAP = {
    {"$zero", {0, "00000"}},
    {"$at", {1, "00001"}},
    {"$v0", {2, "00010"}},
    {"$v1", {3, "00011"}},
    {"$a0", {4, "00100"}},
    {"$a1", {5, "00101"}},
    {"$a2", {6, "00110"}},
    {"$a3", {7, "00111"}},
    {"$t0", {8, "01000"}},
    {"$t1", {9, "01001"}},
    {"$t2", {10, "01010"}},
    {"$t3", {11, "01011"}},
    {"$t4", {12, "01100"}},
    {"$t5", {13, "01101"}},
    {"$t6", {14, "01110"}},
    {"$t7", {15, "01111"}},
    {"$s0", {16, "10000"}},
    {"$s1", {17, "10001"}},
    {"$s2", {18, "10010"}},
    {"$s3", {19, "10011"}},
    {"$s4", {20, "10100"}},
    {"$s5", {21, "10101"}},
    {"$s6", {22, "10110"}},
    {"$s7", {23, "10111"}},
    {"$t8", {24, "11000"}},
    {"$t9", {25, "11001"}},
    {"$k0", {26, "11010"}},
    {"$k1", {27, "11011"}},
    {"$gp", {28, "11100"}},
    {"$sp", {29, "11101"}},
    {"$fp", {30, "11110"}},
    {"$ra", {31, "11111"}}};

Instruction::Instruction()
{
    // Constructor implementation
}
Instruction::Instruction(const std::string &curInstruction)
    : ASMInstruction(curInstruction)
{
    std::vector tokens = split(curInstruction, ' ');
    std::string mnemonic = tokens[0];
    if (Instruction::INSTRUCTIONMAP.find(mnemonic) == Instruction::INSTRUCTIONMAP.end())
    {
        throw std::runtime_error("Mnemonic not found: " + mnemonic);
    }
    this->mnemonic = mnemonic;
    this->opcode = Instruction::INSTRUCTIONMAP.at(this->mnemonic).opcode;
    this->funct = Instruction::INSTRUCTIONMAP.at(this->mnemonic).funct;

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
void Instruction::validateVectorSize(const Instruction &instr, std::string layout, const std::vector<std::string> &toks)
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
 * Validates if a register is valid and returns the infor
 */
RegisterInfo Instruction::validateRegister(const std::string &reg)
{
    try
    {
        RegisterInfo regInfo = Instruction::REGISTER_MAP.at(reg);
        return regInfo;
    }
    catch (const std::out_of_range &e)
    {
        throw std::runtime_error("Invalid register: " + reg);
    }
}

/**
 * Setting a register to their according values
 */
void Instruction::setRegisters(std::string &reg, std::string &regName, uint8_t &dec, std::string &bit)
{
    RegisterInfo regInfo = validateRegister(reg);
    regName = reg;
    dec = regInfo.decVal;
    bit = regInfo.binStr;
}

/**
 * Setting a register to their according values
 */
void Instruction::setOffset(std::string &offset, Instruction &instr)
{
    // Check if lable or value
    if (isInteger(offset) || isHexadecimal(offset))
    {
        std::int32_t imm = handleValue(offset);
        if (!fitsIn16Bits(imm))
        {
            std::string output = std::format("Instruction: {} contains invalid immediate", instr.ASMInstruction);
            throw std::out_of_range(output);
        }
        instr.imm = static_cast<std::int16_t>(imm);
        instr.immBit = toBinaryString(instr.imm, 16);
    }
    else
    {
        instr.label = offset;
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
    // Size check
    validateVectorSize(instr, "DST", toks);
    // Register $d
    setRegisters(toks[1], instr.rdName, instr.rd, instr.rdBit);
    // Register $s
    setRegisters(toks[2], instr.rsName, instr.rs, instr.rsBit);
    // Register $t
    setRegisters(toks[3], instr.rtName, instr.rt, instr.rtBit);
}

/**
 * Format:
 * mnemonic $s, $t
 */
void Instruction::parseST(Instruction &instr, std::vector<std::string> &toks)

{
    // Size check
    validateVectorSize(instr, "ST", toks);
    // Register $s
    setRegisters(toks[1], instr.rsName, instr.rs, instr.rsBit);
    // Register $t
    setRegisters(toks[2], instr.rtName, instr.rt, instr.rtBit);
}

/**
 * Format:
 * mnemonic $s
 */
void Instruction::parseS(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "S", toks);
    // Register $s
    setRegisters(toks[1], instr.rsName, instr.rs, instr.rsBit);
}

/**
 * Format:
 * mnemonic $d, $t imm
 */
void Instruction::parseDTIMM(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "DTIMM", toks);
    // Register $d
    setRegisters(toks[1], instr.rdName, instr.rd, instr.rdBit);
    // Register $t
    setRegisters(toks[2], instr.rtName, instr.rt, instr.rtBit);
    // Immediate
    // Check if lable or value
    if (isInteger(toks[3]) || isHexadecimal(toks[3]))
    {
        std::int32_t imm = handleValue(toks[3]);
        if (!fitsIn16Bits(imm))
        {
            std::string output = std::format("Instruction: {} contains invalid immediate", instr.ASMInstruction);
            throw std::out_of_range(output);
        }
        instr.imm = static_cast<std::int16_t>(imm);
        instr.immBit = toBinaryString(instr.imm, 5);
    }
    else
    {
        throw std::invalid_argument("Invalid immediate: " + instr.ASMInstruction);
    }
}

/**
 * Format:
 * mnemonic $t, $s imm
 */
void Instruction::parseTSIMM(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "TSIMM", toks);
    // Register $t
    setRegisters(toks[1], instr.rtName, instr.rt, instr.rtBit);
    // Register $s
    setRegisters(toks[2], instr.rsName, instr.rs, instr.rsBit);
    // Immediate
    if (isInteger(toks[3]) || isHexadecimal(toks[3]))
    {
        std::int32_t imm = handleValue(toks[3]);
        if (!fitsIn16Bits(imm))
        {
            std::string output = std::format("Instruction: {} contains invalid immediate", instr.ASMInstruction);
            throw std::out_of_range(output);
        }
        instr.imm = static_cast<std::int16_t>(imm);
        instr.immBit = toBinaryString(instr.imm, 16);
    }
    else
    {
        throw std::invalid_argument("Invalid immediate: " + instr.ASMInstruction);
    }
}

/**
 * Format:
 * mnemonic $t, imm
 */
void Instruction::parseTIMM(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "TIMM", toks);
    // Register $t
    setRegisters(toks[1], instr.rtName, instr.rt, instr.rtBit);
    // Immediate
    if (isInteger(toks[2]) || isHexadecimal(toks[2]))
    {
        std::int32_t imm = handleValue(toks[2]);
        if (!fitsIn16Bits(imm))
        {
            std::string output = std::format("Instruction: {} contains invalid immediate", instr.ASMInstruction);
            throw std::out_of_range(output);
        }
        instr.imm = static_cast<std::int16_t>(imm);
        instr.immBit = toBinaryString(instr.imm, 16);
    }
    else
    {
        throw std::invalid_argument("Invalid immediate: " + instr.ASMInstruction);
    }
}

/**
 * Format:
 * mnemonic $s, $t, offset
 */
void Instruction::parseSTOFF(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "STOFF", toks);
    // Register $s
    setRegisters(toks[1], instr.rsName, instr.rs, instr.rsBit);
    // Register $t
    setRegisters(toks[2], instr.rtName, instr.rt, instr.rtBit);
    // Immediate
    setOffset(toks[2], instr);
}

/**
 * Format:
 * mnemonic $t, offset($s)
 */
void Instruction::parseTOFFS(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "TOFFS", toks);
    // Register $t
    setRegisters(toks[1], instr.rtName, instr.rt, instr.rtBit);
    // Offset
    std::string &combo = toks[2];
    // Find the positions of the parentheses
    int open = combo.find('(');
    int close = combo.find(')');
    // Check if both parentheses are present
    if (open != std::string::npos && close != std::string::npos)
    {
        // Offset
        std::string imm = combo.substr(0, open);
        setOffset(imm, instr);
        // Register $s
        std::string reg = combo.substr(open + 1, close - open - 1);
        setRegisters(reg, instr.rsName, instr.rs, instr.rsBit);
    }
    else
    {
        // Data label
        instr.data = toks[2];
    }
}

/**
 * Format:
 * mnemonic $s, offset
 */
void Instruction::parseSOFF(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "SOFF", toks);
    // Register $s
    setRegisters(toks[1], instr.rsName, instr.rs, instr.rsBit);
    // Immediate
    setOffset(toks[2], instr);
}

/**
 * Format:
 * mnemonic target
 */
void Instruction::parseTARG(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "TARG", toks);
    // Setting target
    instr.label = toks[1];
}

/**
 * Format:
 * syscall
 */
void Instruction::parseSyscall(Instruction &instr, std::vector<std::string> &toks)
{
    // Size check
    validateVectorSize(instr, "SYSCALL", toks);
}
