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
    // Memory
    bool write(const void *data);
    uint8_t read(uint32_t address);
    std::uint32_t address;

private:
    std::vector<uint8_t> memory;
    bool resize();
};

#endif
