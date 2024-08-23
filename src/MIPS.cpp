#include "MIPS.hpp"
#include "Helpers.hpp"
#include <string>
#include <vector>
#include <cstdint>

int main()
{
    std::string filename = "assembly_files/example2_hello_world.asm";
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