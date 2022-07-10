/**
    @file synalyzer.hpp
    @brief Syntax analyzer
*/

#pragma once

#include <list>
#include <string>

// FNV1-a hash, 32 bit
inline constexpr std::uint32_t fnv1a(const char *str, std::uint32_t hash = 2166136261UL)
{
    return *str ? fnv1a(str + 1, (hash ^ uint32_t(*str)) * uint32_t(16777619ULL)) : hash;
}

namespace ucsyn
{
    /*
     * Enum action provides types of actions for
     * semantic analyzer.
     */
    enum class action
    {
        command = 0,
        argument = 1,
        key  = 2,
        option = 3,
        assign_value = 4,
        EOL = 5,
        no_act = -1
    };

    const int states[5][6] = {{1, 2, 4, 4, -8, -1},
                              {-5, -5, -5, -5, -5, -2},
                              {-5, -5, -5, -5, -5, -3},
                              {-5, -5, -5, -5, -5, -4},
                              {-7, -7, -7, -7, -7, -6}};

    /*
     * Enumeration state provides names for all
     * states of Finite State Machine.
     * Finite state names begins with _
     */
    enum state
    {
        initial = 0,
        read_ddash = 1,
        read_dash = 2,
        read_slash = 3,
        read_eq = 4,

        _command_or_arg = -1,
        _option = -2,
        _key_seq = -3,
        _err_name_req = -5,
        _assign_value = -6,
        _err_val_req = -7,
        _exit = -8
    };

    enum event
    {
        ddash = 0,
        dash = 1,
        eq_eq = 2,
        eq_ddot = 3,
        EOL = 4,
        word = 5
    };

    struct Token
    {
        Token() { action = ucsyn::action::no_act; }
        Token(ucsyn::action action, std::string lexem)
            : action(action), lexem(lexem) {}
        ucsyn::action action;
        std::string lexem;
    };

    event eventKind(std::string const &lexem);
    void disassembly_key_sequence(std::string &&lexem, std::list<Token> &tokenVector);
    std::list<Token> tokenize(std::list<std::string> &lexems);
} // namespace syn