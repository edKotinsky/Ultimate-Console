#pragma once

#include <iostream>
#include <string>
#include <list>

#include <ucconf.hpp>

#include "indata.hpp"

namespace uclex
{
    const int states[7][8] = {{5, 5, 5, 1, -1, 0, 6, -1},
                              {3, -2, -2, 2, -2, -2, -2, -2},
                              {4, -3, 4, -3, -3, -3, -3, -3},
                              {3, -2, -2, -2, -2, -1, -2, -1},
                              {4, -3, 4, 4, -1, -1, -3, -1},
                              {5, 5, 5, 5, 5, -1, 5, -1},
                              {6, 6, 6, 6, 6, 6, -1, -4}};

    enum state
    {
        initial = 0,
        read_single_dash = 1,
        read_double_dash = 2,
        read_key_sequence = 3,
        read_option_name = 4,
        read_word = 5,
        read_word_in_q_marks = 6,

        _return_lexem = -1,
        _err_incorrect_key = -2,
        _err_incorrect_name = -3,
        _err_unclosed_q_block = -4
    };

    enum event
    {
        character = 0,
        other_ch = 1,
        number = 2,
        dash = 3,
        equal = 4,
        space = 5,
        quote = 6,
        eol = 7
    };

    inline state getState(state st, event ev);
    event charType(char ch);
    std::list<std::string> parse(UC::input_data &iStr);

    enum class name_type
    {
        key,
        option,
        other
    };

    name_type lexemType(std::string &lexem);
} // namespace lex
