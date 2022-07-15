#include "trace.hpp"

#include <fstream>
#include <stdexcept>

namespace UC::TRACE
{
    std::ofstream trace;
    
    void init_trace()
    {
        TRACE::trace.open("trace.log");
        if (!TRACE::trace.is_open())
            throw std::runtime_error("trace: file is not opened");
    }

    void prnt(const char*str, size_t& i)
    {
        while (str[i] != '\0')
            switch (str[i])
            {
            case '%':
                throw std::runtime_error("trace: too many %");
            default:
                trace << str[i++];
                break;
            }
    }
}