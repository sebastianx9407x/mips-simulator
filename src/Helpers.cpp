#include "Helpers.hpp"
#include <sstream>
#include <iostream>
#include <cstdint>

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