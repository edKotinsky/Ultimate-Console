#pragma once

#include <string>
#include <stdexcept>

namespace ucargw
{
    struct argv_wrapper
    {
    public:
        argv_wrapper(char **argv, int argc, size_t startCount = 1)
        {
            if (argc < 0)
                throw std::logic_error("argv_wrapper::ctor: argc is less than 0");
            size_t count = static_cast<size_t>(argc);

            size_t prev = startCount;
            for (size_t i = startCount; i < count; ++i)
            {
                if (i > prev)
                {
                    prev++;
                    argstr.push_back(' ');
                }
                argstr += argv[i];
            }
            argstr.push_back('\0');
        }

        argv_wrapper() = default;
        ~argv_wrapper() = default;
        argv_wrapper(argv_wrapper&&) = default;
        argv_wrapper(const argv_wrapper &) = delete;

        inline char peek()
        {
            return argstr.at(0);
        }

        void get(char &ch)
        {
            if (argstr.size())
                ch = argstr.front();
            argstr.erase(0, 1);
        }

        void putback(char ch)
        {
            argstr.insert(0, 1, ch);
        }

        bool eof()
        {
            if (argstr.size())
                return false;
            return true;
        }

    private:
        std::string argstr;
    };
} // namespace ind
