#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <vector>
#include <string>
#include <bitset>
#include <cstdint>

std::vector<std::string> split(const std::string &s, char delim);

std::string toBinaryString(uint32_t value, size_t bitWidth);

bool fitsIn16Bits(std::int32_t value);

bool fitsIn32Bits(std::int32_t value);

bool isHexadecimal(const std::string &str);
bool isInteger(const std::string &str);
std::int32_t handleValue(const std::string &str);

#endif