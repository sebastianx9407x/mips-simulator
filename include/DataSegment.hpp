#ifndef DATASEGMENT_H
#define DATASEGMENT_H

#include "vector"
#include <cstdint>

class DataSegment
{
public:
    // Constructor
    DataSegment();
    ~DataSegment();
    // Mememory
    bool write(uint8_t value);
    uint8_t read(uint32_t address);
    std::uint32_t size;

private:
    std::vector<uint8_t> memory;
};

#endif
