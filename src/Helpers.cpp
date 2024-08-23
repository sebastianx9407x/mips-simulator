#include "Helpers.hpp"
#include <sstream>
#include <iostream>
#include <limits>
#include <regex>

std::vector<std::string> split(const std::string &s, char delim)
{

    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        if (!item.empty()) // Only add non-empty items
        {
            result.push_back(item);
        }
    }

    return result;
}

void validateVectorSize(int expSize, const std::vector<std::string> &toks)
{
    if (toks.size() != expSize)
    {
        throw std::runtime_error("Incorrect number of tokens for instruction: " + vectorToString(toks));
    }
}

// Function to convert a signed integer to a binary string
std::string toBinaryString(int32_t value, std::size_t bitWidth)
{
    // Check if bitWidth is valid and if the value can be represented in the given bitWidth
    if (bitWidth == 0 || value >= (1 << (bitWidth - 1)) || value < -(1 << (bitWidth - 1)))
    {
        throw std::out_of_range("Value exceeds the bit width range.");
    }

    std::ostringstream oss;

    // Handle negative values for signed integers
    if (value < 0)
    {
        value = (1 << bitWidth) + value; // Convert negative value to its two's complement form
    }

    // Create a bitset with the maximum size (32 bits) and get its string representation
    std::bitset<32> bits(value);
    std::string bitString = bits.to_string();

    // Extract the rightmost `bitWidth` bits
    std::string result = bitString.substr(32 - bitWidth);

    // Ensure the result has the correct bit width by padding with zeros if necessary
    if (result.length() < bitWidth)
    {
        result = std::string(bitWidth - result.length(), '0') + result;
    }

    return result;
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

bool isInteger(const std::string &str)
{
    std::regex integerRegex("^[+-]?\\d+$");
    return std::regex_match(str, integerRegex);
}

bool isHexadecimal(const std::string &str)
{
    std::regex hexRegex("^0[xX][0-9a-fA-F]+$");
    return std::regex_match(str, hexRegex);
}