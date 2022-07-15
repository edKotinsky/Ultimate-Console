#include "dictionary.hpp"

#include <uctrace.hpp>
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

                    std::list<std::string> lexems = uclex::parse(*input.get());

                    #ifdef UC_TRACE
                        size_t i = 0;
                        for (auto it : lexems)
                            UC::tprintf("Dictionary::_run: \
lexems[%] %\n", i++, it);
                    #endif

                    std::list<ucsyn::Token> tokens = ucsyn::tokenize(lexems);

                    #ifdef UC_TRACE
                        i = 0;
                        for (auto it : tokens)
                            UC::tprintf("Dictionary::_run: \
tokens[%] type % lexem %\n", i, static_cast<int>(it.action), it.lexem);
                    #endif

                    ucsem::execute(tokens, cmds, vars);

                    if (input->eof()) st = dictionary_state::end_of_file;

                    #ifdef UC_TRACE
                        UC::tprintf("Dictionary::_run: state = %", 
                            static_cast<int>(st));
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