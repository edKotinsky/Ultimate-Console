#include "ucerr.hpp"

#include <iostream>

namespace UC {
    void printError(const component_error& error)
    {
        error_t code = error.code();

        switch (code) 
        {
        case error_code::lexer_incorrect_key:
            std::cerr << "uc::lexer: incorrect key " 
                      << error.what() << std::endl;
            break;

        case error_code::lexer_incorrect_name:
            std::cerr << "uc::lexer: incorrect name "
                      << error.what() << std::endl;
            break;

        case error_code::lexer_unclosed_q_block:
            std::cerr << "uc::lexer: unclosed querry block "
                      << error.what() << std::endl;
            break;
        
        case error_code::syn_option_name_req:
            std::cerr << "uc::syntax analyzer: missing option name " 
                      << error.what() << std::endl;
            break;

        case error_code::syn_missing_value:
            std::cerr << "uc::syntax analyzer: missing option value " 
                      << error.what() << std::endl;
            break;
        
        case error_code::syn_missing_eol:
            std::cerr << "uc::syntax analyzer: missing EOL " 
                      << error.what() << std::endl;
            break;

        case error_code::sem_argument_required:
            std::cerr << "uc::semantic analyzer: argument after the key required " 
                      << error.what() << std::endl;
            break;

        case error_code::sem_command_got_twice:
            std::cerr << "uc::semantic analyzer: command transferred twice " 
                      << error.what() << std::endl;
            break;

        case error_code::sem_command_required:
            std::cerr << "uc::semantic analyzer: command does not exist " 
                      << error.what() << std::endl;
            break;

        case error_code::sem_missing_option_name:
            std::cerr << "uc::semantic analyzer: missing option name " 
                      << error.what() << std::endl;
            break;

        case error_code::sem_option_value_required:
            std::cerr << "uc::semantic analyzer: option requires value " 
                      << error.what() << std::endl;
            break;

        case error_code::cmd_command_does_not_exist:
            std::cerr << "uc::command: command does not exist " 
                      << error.what() << std::endl;
            break;

        case error_code::cmd_key_does_not_exist:
            std::cerr << "uc::command: key does not exist " 
                      << error.what() << std::endl;
            break;
    
        case error_code::cmd_option_does_not_exist:
            std::cerr << "uc::command: option does not exist " 
                      << error.what() << std::endl;
            break;

        case error_code::cmd_too_many_args:
            std::cerr << "uc::command: too many arguments transferred " 
                      << error.what() << std::endl;
            break;

        default:
            std::cerr << "uc: undefined error " 
                      << error.what() << std::endl;
            break;
        }
    }
} // namespace uc