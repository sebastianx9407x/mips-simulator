#include "Data.hpp"
#include <stdexcept>
#include <iostream>

Data::Data() {}

Data::Data(std::string &dataline, u_int32_t address) : dataline(dataline), address(address)
{
    std::size_t colonPos = this->dataline.find(':');
    if (colonPos == std::string::npos)
    {
        throw std::runtime_error("Data not properly formated with no colon");
    }
    this->label = this->dataline.substr(0, colonPos);
    // Must handle for value
    this->val = this->dataline.substr(colonPos + 1);
}
Data::~Data()
{
}