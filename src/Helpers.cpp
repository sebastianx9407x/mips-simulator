#include "Helpers.hpp"
#include <sstream>
#include <iostream>
#include <cstdint>
#include <limits>

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

// Function to convert an integer to a binary string
std::string toBinaryString(uint32_t value)
{
    std::bitset<32> bits(value);
    return bits.to_string();
}

bool fitsIn16Bits(std::int32_t value)
{
    return value >= std::numeric_limits<std::int16_t>::min() && value <= std::numeric_limits<std::int16_t>::max();
}

bool fitsIn32Bits(std::int32_t value)
{
    return value >= std::numeric_limits<std::int32_t>::min() && value <= std::numeric_limits<std::int32_t>::max();
}

std::int32_t handleValue(const std::string &str)
{
    std::int32_t value;
    // Check for hexadecimal format
    if (str.rfind("0x", 0) == 0)
    {
        value = std::stoi(str, nullptr, 16); // Convert from hex
    }
    else
    {
        value = std::stoi(str, nullptr, 10); // Convert from decimal
    }
    return value;
}