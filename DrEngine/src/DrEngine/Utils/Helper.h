#pragma once
#include <sstream>
#include <string>

class Helper
{
public:
    template <class T>
    static std::string toString(T i)
    {
        std::stringstream ss;
        ss << i;

        return ss.str();    
    }
};
