#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <cstdint>
class Data
{
public:
    Data();
    Data(std::string &dataline, u_int32_t address);
    ~Data();
    uint32_t address;
    std::string dataline;
    std::string label;
    std::string directive;
    std::string val;

private:
    void processData(std::string &dataline);
};

#endif