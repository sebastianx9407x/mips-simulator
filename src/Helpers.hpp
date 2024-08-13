#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <vector>
#include <string>
#include <bitset>
#include <cstdint>

std::vector<std::string> split(const std::string &s, char delim);

std::string toBinaryString(uint32_t value);

#endif