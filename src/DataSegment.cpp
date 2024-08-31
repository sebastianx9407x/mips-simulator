#include "DataSegment.hpp"
#include "Globals.hpp"

DataSegment::DataSegment() : memory(DATA_SEGMENT_SIZE), address(DATA_START)
{
}

bool DataSegment::write(const void *data)
{
    // const uint8_t byteData = static_cast<const uint8_t *>(data);
    return true;
}

uint8_t read(uint32_t address)
{
    return 0;
}