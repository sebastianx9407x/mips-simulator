#ifndef HELPERS_HPP
#define HELPERS_HPP


#include <vector>
#include <string>
#include <bitset>
#include <cstdint>
#include <sstream>

std::vector<std::string> split(const std::string &s, char delim);

template <typename T>
std::string vectorToString(const std::vector<T> &vec)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        oss << vec[i];
        if (i != vec.size() - 1)
        {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}

void validateVectorSize(int expSize, const std::vector<std::string> &toks);

std::string toBinaryString(int32_t value, std::size_t bitWidth);

bool fitsIn16Bits(std::int32_t value);

bool fitsIn32Bits(std::int32_t value);

bool isHexadecimal(const std::string &str);
bool isInteger(const std::string &str);
std::int32_t handleValue(const std::string &str);

#endif