/**
    @file ucerr.hpp
    @brief Header with component_error class and Ulticon error codes
*/

#pragma once

#include <string>

namespace UC
{
    using error_t = int;

    /**
        @brief Error types of Ultimate Console
        Meaning of the prefixes: 
        lexer - lexic analyzer
        syn - syntax analyzer
        sem - semantic analyzer
        cmd - command    
    */
    enum error_code
    {
        lexer_incorrect_key = -1,           ///< Incorrect option one character name
        lexer_incorrect_name = -2,          ///< Incorrect option long name
        lexer_unclosed_q_block = -3,        ///< Unclosed quotation marks

        syn_option_name_req = -10,          ///< Missed name of an option
        syn_missing_value = -11,            ///< After option must be the value, which is missed
        syn_missing_eol = -12,              ///< Missed end-of-a-line symbol

        sem_command_required = -20,         ///< Missed command name or command does not exist
        sem_missing_option_name = -21,      ///< Missed option name or option does not exist
        sem_argument_required = -22,        ///< After the key must be the value
        sem_option_value_required = -23,    ///< Option requires value, which is missed
        sem_command_got_twice = -24,        ///< Passed second command (in fact it is impossible)

        cmd_command_does_not_exist = -30,   ///< No command with such name found
        cmd_variable_does_not_exist = -31,  ///< No variable with such name found
        cmd_key_does_not_exist = -32,       ///< No option with such key found
        cmd_option_does_not_exist = -33,    ///< No option with such long name found
        cmd_too_many_args = -34             ///< Arguments in read string more, than in commands argument list
    };

    /**
        @brief Class that provide errors

        In fact this class is a wrapper for pair "error code - string".
        It allows to write your own error messages according to the
        error codes.
    */
    class component_error
    {
    public:
        component_error(error_t errorCode, std::string wrongSequence)
            : _code(errorCode), _sequence(wrongSequence) {}
        component_error(error_t errorCode, char wrongCharacter)
            : _code(errorCode), _sequence(1, wrongCharacter) {}

        component_error(error_t errorCode)
            : _code(errorCode), _sequence() {}

        component_error() = delete;
        ~component_error() = default;

        inline error_t code() const { return _code; }

        inline const char* what() const { return _sequence.c_str(); }

    private:
        error_t _code;
        std::string _sequence;
    };
} // namespace uc
