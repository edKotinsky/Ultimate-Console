#include "ucerr.hpp"
#include "ulticon/printerror.hpp"

#include <iostream>

namespace UC {
    void printError(const component_error& error)
    {
        error_t code = error.code();

        switch (code) 
        {
        case error_code::lexer_incorrect_key:
            std::cerr << "uc::lexer: incorrect key";
            break;

        case error_code::lexer_incorrect_name:
            std::cerr << "uc::lexer: incorrect name";
            break;

        case error_code::lexer_unclosed_q_block:
            std::cerr << "uc::lexer: unclosed querry block";
            break;
        
        case error_code::syn_option_name_req:
            std::cerr << "uc::syntax analyzer: missed option name";
            break;

        case error_code::syn_missed_value:
            std::cerr << "uc::syntax analyzer: missed option value";
            break;
        
        case error_code::syn_missed_eol:
            std::cerr << "uc::syntax analyzer: missed EOL";
            break;

        case error_code::sem_argument_required:
            std::cerr << "uc::semantic analyzer: argument after the \
key required";
            break;

        case error_code::sem_command_required:
            std::cerr << "uc::semantic analyzer: command does not exist";
            break;

        case error_code::sem_missed_option_name:
            std::cerr << "uc::semantic analyzer: missed option name";
            break;

        case error_code::sem_option_value_required:
            std::cerr << "uc::semantic analyzer: option requires value";
            break;

        case error_code::cmd_command_does_not_exist:
            std::cerr << "uc::command: command does not exist";
            break;

        case error_code::cmd_key_does_not_exist:
            std::cerr << "uc::command: key does not exist";
            break;
    
        case error_code::cmd_option_does_not_exist:
            std::cerr << "uc::command: option does not exist";
            break;

        case error_code::cmd_too_many_args:
            std::cerr << "uc::command: too many arguments transferred";
            break;

        case error_code::opt_boola_string:
            std::cerr << "uc::boolalphaOption: string does not mean \
bool value";
            break;
                
        case error_code::opt_int_val_not_numeral:
            std::cerr << "uc::intOption: given string contains non \
numeral characters";
            break;

        case error_code::arg_bool_string:
            std::cerr << "uc::boolArgument: string not mean bool value";
            break;

        case error_code::arg_int_val_not_numeral:
            std::cerr << "uc::intArgument: given string contains non \
numeral characters";
            break;

        default:
            std::cerr << "uc: undefined error";
            break;
        }

        std::cerr << " " << error.what() << std::endl;
    }
} // namespace uc