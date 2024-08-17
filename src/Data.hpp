#ifndef DATA_HPP
#define DATA_HPP

#include <string>

class Data
{
public:
    Data();
    Data(std::string &dataline);
    ~Data();

    std::string dataline;
    std::string label;
    std::string directive;
    std::string val;

private:
    void processData(std::string &dataline);
};

#endif