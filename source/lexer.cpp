#include "lexer.hpp"
#include "trace.hpp"
#include "ucerr.hpp"

namespace uclex
{
    name_type lexemType(std::string &lexem)
    {
        if (lexem[0] == '-')
        {
            if (lexem[1] == '-')
            {
                return name_type::option;
            }

            if (lexem[1] >= '0' && lexem[1] <= '9')
                return name_type::other;
            return name_type::key;
        }
        return name_type::other;
    }

    std::list<std::string> parse(UC::input_data &iStr)
    {
        state st = state::initial;
        state prevst = state::initial;
        event ev = event::character;
        char ch;
        bool exit = false;
        std::string lexem;
        std::list<std::string> lexList;
        error_t error = 0;

        while (!exit)
        {
            prevst = st;
            iStr.get(ch);
            ev = charType(ch);
            st = getState(st, ev);

            #ifdef UC_TRACE
                UC::tprintf("uclex::parce: ch = % ev = % st = %\n", 
                ch, static_cast<int>(ev),static_cast<int>(st));
            #endif

            switch (st)
            {
            case state::initial:
                break;

            case state::read_key_sequence:
                if (prevst == state::read_single_dash)
                    lexList.push_back(std::move(lexem));
                [[fallthrough]];

            case state::read_option_name:
                if (prevst == state::read_double_dash)
                    lexList.push_back(std::move(lexem));
                [[fallthrough]];

            case state::read_single_dash:
                [[fallthrough]];

            case state::read_double_dash:
                [[fallthrough]];

            case state::read_word:
                lexem.push_back(ch);
                break;

            case state::read_word_in_q_marks:
                if (ch != '\"')
                    lexem.push_back(ch);
                break;

            case state::_return_lexem:
                if (lexem.empty())
                {
                    if (ev == event::eol)
                    {
                        lexList.emplace_back("EOL");
                        exit = true;
                    }
                    lexem.push_back(ch);
                    if (ev == event::equal)
                        lexList.push_back(std::move(lexem));
                }
                else
                {
                    if (ch != '\"')
                        iStr.putback(ch);
                    lexList.push_back(std::move(lexem));
                }
                st = state::initial;
                break;

            case state::_err_incorrect_key:
                error = UC::error_code::lexer_incorrect_key;
                break;

            case state::_err_incorrect_name:
                error = UC::error_code::lexer_incorrect_name;
                break;

            case state::_err_unclosed_q_block:
                error = UC::error_code::lexer_unclosed_q_block;
                break;

            default:
                throw std::logic_error("Something goes wrong");
            }

#ifdef LEX_DEBUG
            if (!lexList.empty() && st != prevst)
                UC::tprintf("uclex::parse: lexem = %\n", lexList.back());
#endif

            if (error != 0)
            {
                while (true)
                {
                    lexem.push_back(ch);
                    iStr.get(ch);
                    if (charType(ch) == event::eol || charType(ch) == event::space)
                        break;
                }
                if (!lexList.empty())
                    if (lexList.back() == "-" || lexList.back() == "--")
                        throw UC::component_error(error, lexList.back() + lexem);
                throw UC::component_error(error, std::move(lexem));
            }
        }

        return lexList;
    }

    inline state getState(state st, event ev)
    {
        if (st < 0)
            throw std::logic_error("State (array index) less than 0");
        return static_cast<state>(states[st][ev]);
    }

    event charType(char ch)
    {
        switch (ch)
        {
        case '-':
            return event::dash;
        case '\t':
            [[fallthrough]];
        case ' ':
            return event::space;
        case '=':
            return event::equal;
        case '\"':
            return event::quote;
        case ';':
            [[fallthrough]];
        case '\0':
            [[fallthrough]];
        case '\n':
            return event::eol;
        default:
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
                return event::character;
            if (ch >= '0' && ch <= '9')
                return event::number;
            return event::other_ch;
        }
    }
} // namespace lex
