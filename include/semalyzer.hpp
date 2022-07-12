/**
    @file semalyzer.hpp
    @brief Semantic analyzer
*/
#pragma once

#include "uccmd.hpp"
#include "synalyzer.hpp"
#include "variable.hpp"

namespace ucsem
{
    const int states[2][6] = {{  1, -1, -1, -1, -1, -5},
                              { -7, -4, -2, -3, -6, -5}};

    enum state
    {
        initial = 0,
        command = 1,

        _variable = -6,
        _no_cmd = -1,
        _option_sname = -2,
        _option_lname = -3,
        _arg = -4,
        _exit = -5,
        _er_dcmd = -7
    };

    enum class command_type
    {
        cmd, var
    };

    void execute(std::list<ucsyn::Token> &tokens, 
        uccmd::CommandList<UC::Command> &cmdlist, 
        uccmd::CommandList<UC::Variable> &varList);
} // namespace sem
