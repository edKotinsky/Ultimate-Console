/**
    @file variable.hpp
    @brief Variable
*/
#pragma once

#include "argument.hpp"

namespace UC
{
    /**
        @brief Variable class

        Variable contains a value, wrapped into an Argument's child
        class. Variable does not require any commands before it.
        Syntax of a variable is: variable-name = value
    */
    class Variable
    {
    public:
        Variable(std::string name, Argument& value)
            : n(name), val(value.clone()) {}

        Variable(std::string name, Argument&& value)
            : n(name), val(value.clone()) {}

        Variable() = delete;
        Variable(const Variable&) = delete;
        ~Variable() = default;

        inline const std::string &getName() const
        { return n; }

        inline void execute (std::string &&value) const
        { val->execute(std::move(value)); }

    private:
        std::string n;
        std::shared_ptr<Argument> val;
    };
}