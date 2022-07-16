#include "trace.hpp"

#include <fstream>
#include <stdexcept>

namespace UC::TRACE
{
    std::ofstream trace;
    
    void init_trace()
    {
        if (!TRACE::trace.is_open())
            TRACE::trace.open("trace.log");
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