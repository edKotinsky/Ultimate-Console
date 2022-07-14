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
        lexer_incorrect_key = -1,           
        ///< Incorrect option key
        ///< (keys can consists of a...z, A...Z)
        lexer_incorrect_name = -2,          
        ///< Incorrect option name 
        ///< (option names can contain only these characters:
        ///< a...z, A...Z, -, 0...9)
        lexer_unclosed_q_block = -3,        
        ///< Unclosed quotation marks ("something )

        syn_option_name_req = -10,          
        ///< Missed name of an option (--???; -???)
        syn_missed_value = -11,            
        ///< No value given to an option (--option = ???; -o ???)
        syn_missed_eol = -12,              
        ///< Missed end-of-a-line symbol

        sem_command_required = -20,         
        ///< Missed command name or command does not exist
        sem_missed_option_name = -21,
        ///< Missed option name or option does not exist
        ///< (--option = ???; -o ???)
        sem_argument_required = -22,
        ///< No value given to an option (-o ???)
        sem_option_value_required = -23,
        ///< No value given to an option (--option = ???)

        cmd_command_does_not_exist = -30,
        ///< No command found with this name
        cmd_variable_does_not_exist = -31,
        ///< No variable found with this name
        cmd_key_does_not_exist = -32,
        ///< No option found with this key
        cmd_option_does_not_exist = -33,
        ///< No option found with this name
        cmd_too_many_args = -34,
        ///< More arguments passed than are available in the command

        opt_boola_string = -35,
        ///< Incorrect string given to BoolalphaOption 
        opt_int_val_not_numeral = -36,
        ///< Incorrect string given to IntOption (string contains 
        ///< non numeral characters)
        
        arg_bool_string = -37,
        ///< Incorrect string given to BoolArgument
        arg_int_val_not_numeral = -38,
        ///< Incorrect string given to IntArgument (string contains 
        ///< non numeral characters)
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
