#include <optional>
#include <pthread.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "argument.hpp"
#include "semalyzer.hpp"
#include "synalyzer.hpp"
#include "ucerr.hpp"
#include "variable.hpp"
#include "uccmd.hpp"

namespace ucsem
{
    size_t ignoreNoAct(std::vector<ucsyn::Token> &tokenVector, size_t tokenIdx);

    void execute(std::vector<ucsyn::Token> &tokens, 
                 uccmd::CommandList<UC::Command> &uclist, 
                 uccmd::CommandList<UC::Variable> &varList)
    {
        size_t tokenIt = 0;
        ucsyn::Token tok;
        size_t event = 0;
        state st = state::initial;
        state prevst = state::initial;
        bool exit = false;
        std::string commandName;

        auto commandIdx = uclist.end();
        auto variable = varList.end();
        std::vector<std::unique_ptr<UC::Option>>::iterator option;

        while (!exit)
        {
            tokenIt = ignoreNoAct(tokens, tokenIt);
            tok = std::move(tokens.at(tokenIt));

            event = static_cast<size_t>(tok.action);
            prevst = st;
            st = static_cast<state>(states[st][event]);

            if (prevst == state::command && st != state::_variable)
            {
                commandIdx = uclist.getCommand(commandName);
                if (commandIdx == uclist.end())
                {
                    throw UC::component_error
                    (UC::error_code::cmd_command_does_not_exist, 
                    commandName);
                }
            }

            switch (st)
            {
            case state::initial: break;

            case state::command:
                commandName = tok.lexem;
                break;

            case state::_no_cmd:
                throw UC::component_error
                    (UC::error_code::sem_command_required);

            case state::_option_lname:
                st = state::command;
                option = (*commandIdx)->findOptionLongName(tok.lexem);

                if (!(*option)->valueAssignmentReq())
                {
                    (*option)->execute();
                    break;
                }

                tok = std::move(tokens.at(++tokenIt));

                if (!(tok.action == ucsyn::action::assign_value))
                    throw UC::component_error
                        (UC::error_code::sem_option_value_required);

                (*option)->execute(std::move(tok.lexem));
                break;

            case state::_option_sname:
            {
                st = state::command;

                option = (*commandIdx)->findOptionShortName(tok.lexem);

                if (!(*option)->valueAssignmentReq())
                {
                    (*option)->execute();
                    break;
                }

                size_t argFindIt = tokenIt;
                while (tokens.at(argFindIt).action != ucsyn::action::argument)
                {
                    argFindIt++;
                    if (argFindIt == tokens.size() ||
                        tokens.at(argFindIt).action == ucsyn::action::option ||
                        tokens.at(argFindIt).action == ucsyn::action::EOL)
                        throw UC::component_error
                            (UC::error_code::sem_argument_required);
                }

                tok = std::move(tokens[argFindIt]);
                tokens[argFindIt].action = ucsyn::action::no_act;

                (*option)->execute(std::move(tok.lexem));
                break;
            }

            case state::_arg:
                (*commandIdx)->setArgumentValue(std::move(tok.lexem));
                st = state::command;
                break;

            case state::_exit:
                if (commandIdx != uclist.end())
                {
                    (*commandIdx)->execute();
                    (*commandIdx)->resetArgumentCounter();
                }
                exit = true;
                break;

            case state::_variable:
                variable = varList.getCommand(commandName);
                if (variable == varList.end())
                {
                    throw UC::component_error
                    (UC::error_code::cmd_command_does_not_exist, 
                    commandName);
                }
                (*variable)->execute(std::move(tok.lexem));
                st = state::initial;
                break;

            case state::_er_dcmd:
                throw UC::component_error
                    (UC::error_code::sem_command_got_twice);
            }
            tokenIt++;
        }
    }

    size_t ignoreNoAct(std::vector<ucsyn::Token> &tokenVector, size_t tokenIdx)
    {
        if (tokenVector.at(tokenIdx).action != ucsyn::action::no_act) 
            return tokenIdx;
        if (tokenIdx == tokenVector.size()) 
            throw std::logic_error("sem::execute: missing EOL");
        return ignoreNoAct(tokenVector, ++tokenIdx);
    }

} // namespace sem
