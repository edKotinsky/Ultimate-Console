/**
    @file trace.hpp

    @brief tprintf
*/
#pragma once

#include <fstream>

#if defined (UC_TRACE) || defined (ULTICON_TRACE)
    #define INIT_TRACE UC::TRACE::init_trace
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
    /**
        @brief tprintf prints debug info to trace.log

        Character '%' in explanation string is replaced by 
        corresponding argument. If after first persent goes second
        persent, function prints one persent symbol into trace.log.
        If single persent symbols more than arguments, function
        will throw an exception. If number of arguments is more 
        than persents, too.

        @param[in] str is an explanation string
        @param[in] args variable number of arguments
    */
    template<typename... Args>
    void tprintf(const char* str, Args... args)
    {
        if (!TRACE::trace.is_open())
            throw std::runtime_error("trace: file is not opened");
        size_t i = 0;
        TRACE::prnt(str, i, args...);
    }
}