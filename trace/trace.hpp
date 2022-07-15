#pragma once

#include <fstream>

#if defined (UC_TRACE) || defined (ULTICON_TRACE)
    #define INIT_TRACE UC::TRACE::init_trace
#else
    #define INIT_TRACE // nothing
#endif

namespace UC::TRACE
{
    extern std::ofstream trace;

    void init_trace();

    void prnt(const char*str, size_t& i);

    template<typename Arg, typename... Args>
    void prnt(const char *str, size_t& i, Arg arg, Args... args)
    {
        if (str[i] == '\0')
            throw std::runtime_error("trace: too many arguments");

        while (str[i] != '\0')
            switch (str[i])
            {
            case '%':
                if (str[++i] != '%') {
                    trace << arg;
                    prnt(str, i, args...);
                    break;
                }
                [[fallthrough]];
            default:
                trace << str[i++];
                break;
            }
    }
}

namespace UC
{
    template<typename... Args>
    void tprintf(const char* str, Args... args)
    {
        if (!TRACE::trace.is_open())
            throw std::runtime_error("trace: file is not opened");
        size_t i = 0;
        TRACE::prnt(str, i, args...);
    }
}