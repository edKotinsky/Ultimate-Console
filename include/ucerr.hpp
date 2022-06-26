#pragma once

#include <string>

namespace UC
{
    using error_t = int;
    
    enum error_code
    {
        lexer_incorrect_key = -1,
        lexer_incorrect_name = -2,
        lexer_unclosed_q_block = -3,

        syn_option_name_req = -10,
        syn_missing_value = -11,
        syn_missing_eol = -12,

        sem_command_required = -20,
        sem_missing_option_name = -21,
        sem_argument_required = -22,
        sem_option_value_required = -23,
        sem_command_got_twice = -24,

        cmd_command_does_not_exist = -30,
        cmd_variable_does_not_exist = -31,
        cmd_key_does_not_exist = -32,
        cmd_option_does_not_exist = -33,
        cmd_too_many_args = -34
    };

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
