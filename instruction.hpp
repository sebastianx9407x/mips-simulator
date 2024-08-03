#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>
#include <cstring>
#include <iostream>

class Instruction {
public: 
    Instruction();
    ~Instruction();

private:
    char* ASMInstruction;
    char* Mnemonic;
    char* rdName;
    char* rsName;
    char* rtName;
    int16_t Imm;
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;
    char* Opcode;
    char* Funct;
    char* RD;
    char* RS;
    char* RT;
    char* IMM;
}

#endif