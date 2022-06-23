#include <stdexcept>
#include "synalyzer.hpp"
#include "ucerr.hpp"

namespace ucsyn
{
    std::vector<Token> tokenize(std::vector<std::string> &lexems)
    {
        state st = state::initial;
        event ev = event::ddash;
        std::vector<Token> tokens;
        std::string lexem;
        auto it = lexems.begin();
        bool exit = false;
        action act = action::no_act;

        while (!exit)
        {
            if (it == lexems.end())
                throw UC::component_error(UC::error_code::syn_missing_eol);
            lexem = std::move(*it);
            ev = eventKind(lexem);
            if (st < 0)
                throw std::logic_error("synalyzer: state is less than 0");
            st = static_cast<state>(states[st][ev]);

            switch (st)
            {
            case state::initial:
                break;

            case state::read_ddash:
                [[fallthrough]];

            case state::read_dash:
                [[fallthrough]];

            case state::read_slash:
                [[fallthrough]];

            case state::read_eq:
                act = action::no_act;
                break;

            case state::_command_or_arg:
                if (it == lexems.begin())
                    act = action::command;
                else
                    act = action::argument;
                st = state::initial;
                break;
            
            case state::_option:
                act = action::option;
                st = state::initial;
                break;
            
            case state::_key_seq:
                act = action::key;
                st = state::initial;
                break;
            
            case state::_err_name_req:
                throw UC::component_error(UC::error_code::syn_option_name_req);
            
            case state::_assign_value:
                act = action::assign_value;
                st = state::initial;
                break;

            case state::_err_val_req:
                throw UC::component_error(UC::error_code::syn_missing_value);

            case state::_exit:
                act = action::EOL;
                exit = true;
                break;
            }
            if (act != action::no_act)
            {
                if (act == action::key) 
                    disassembly_key_sequence(std::move(lexem), tokens);
                else
                    tokens.emplace_back(act, std::move(lexem));
            }
                
            it++;
        }
        return tokens;
    }

    void disassembly_key_sequence(std::string &&lexem, std::vector<Token> &tokenVector)
    {
        for (auto it : lexem)
            tokenVector.emplace_back(action::key, std::string(1, it));  
    }

    event eventKind(std::string const &lexem)
    {
        if (lexem.size() > 3)
            return event::word;
        switch (fnv1a(lexem.c_str()))
        {
        case fnv1a("-"):
            return event::dash;
        case fnv1a("--"):
            return event::ddash;
        case fnv1a("="):
            return event::eq_eq;
        case fnv1a(":"):
            return event::eq_ddot;
        case fnv1a("EOL"):
            return event::EOL;
        default:
            return event::word;
        }
    }
} // namespace syn