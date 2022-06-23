#pragma once

#include "argument.hpp"

namespace UC
{
    class Variable
    {
    public:
        Variable(std::string name, Argument& value)
            : n(name), val(value) {}

        Variable() = delete;
        Variable(const Variable&) = delete;
        ~Variable() = default;

        inline const std::string &getName() const
        { return n; }

        inline void execute (std::string &&value) const
        { val.execute(std::move(value)); }

    private:
        std::string n;
        Argument& val;
    };
}