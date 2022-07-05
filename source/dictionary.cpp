#include "dictionary.hpp"

#include "lexer.hpp"
#include "synalyzer.hpp"
#include "semalyzer.hpp"

namespace UC 
{
    void Dictionary::_run()
        {
            while (st == dictionary_state::running)
            {
                try
                {
                    if (input == nullptr)
                        throw std::logic_error("No input given");

                    if (greetEnable) std::cout << grtng;
                    std::list<std::string> lexems = uclex::parse(*input.get());

                    #ifdef UC_DEBUG
                        size_t i = 0;
                        for (auto it : lexems)
                        {
                            std::cerr << "debug: lexems[" << i++ << "]: " << it << std::endl;
                        }
                            
                    #endif

                    std::list<ucsyn::Token> tokens = ucsyn::tokenize(lexems);

                    #ifdef UC_DEBUG
                        i = 0;
                        for (auto it : tokens)
                        {
                            std::cerr << "debug: tokens[" << i << "]: ";
                            switch (it.action)
                            {
                            case ucsyn::action::argument:
                                std::cerr << "<argument>   ";
                                break;

                            case ucsyn::action::assign_value:
                                std::cerr << "<assignment> ";
                                break;
                            
                            case ucsyn::action::command:
                                std::cerr << "<command>    ";
                                break;

                            case ucsyn::action::EOL:
                                std::cerr << "<EOL>        ";
                                break;

                            case ucsyn::action::key:
                                std::cerr << "<key>        ";
                                break;

                            case ucsyn::action::no_act:
                                std::cerr << "<>           ";
                                break;

                            case ucsyn::action::option:
                                std::cerr << "<option>     ";
                                break;
                            }
                            std::cerr << it.lexem << std:: endl;
                        }
                    #endif

                    ucsem::execute(tokens, cmds, vars);

                    if (input->eof()) st = dictionary_state::end_of_file;

                    #ifdef UC_DEBUG
                        switch (st)
                        {
                        case dictionary_state::running:
                            std::cerr << "debug: state = running" << std::endl;
                            break;

                        case dictionary_state::error:
                            std::cerr << "debug: state = error" << std::endl;
                            break;

                        case dictionary_state::end_of_file:
                            std::cerr << "debug: state = end_of_file" << std::endl;
                            break;

                        case dictionary_state::stopped:
                            std::cerr << "debug: state = stopped" << std::endl;
                            break;
                        }
                    #endif
                    
                }
                catch (const UC::component_error &e)
                {
                    st = dictionary_state::error;
                    throw;
                }
            }
        }
} // namespace UC