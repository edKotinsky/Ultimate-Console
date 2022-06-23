#include <iosfwd>
#include <string>
#include "indata.hpp"

namespace UC
{
    input_data::input_data(std::istream &inputStream)
        : istr(&inputStream), args() {}

    input_data::input_data(char **argv, int argc)
        : istr(nullptr), args(argv, argc) {}

    void input_data::get(char &ch)
    {
        if (istr == nullptr) 
        {
            args.get(ch);
            return;
        }
        istr->get(ch);
    }

    int input_data::peek()
    {
        if (istr == nullptr)
            return args.peek();
        return istr->peek();
    }

    void input_data::putback(char ch)
    {
        if (istr == nullptr)
        {
            args.putback(ch);
            return;
        }
        istr->putback(ch);
    }

    bool input_data::eof()
    {
        if (istr == nullptr)
            return args.eof();
        if (!istr->rdbuf()->in_avail()) return true;
        return false;
    }
} // namespace ind
