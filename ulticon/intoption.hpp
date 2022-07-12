/**
    @file intoption.hpp
*/
#pragma once

#include <include/option.hpp>

namespace UC
{
    /**
        @brief IntOption provides an option for std::string values

        Option contains long name, short name, some value and 
        execution method. When disassembler invokes execute method,
        it passes the value into this method. This value can contain
        only numeral characters.
    */
    struct IntOption : Option
    {
        IntOption(std::string longName, char shortName, int &refToValue)
            : Option(longName, shortName), val(refToValue) {}

        IntOption(std::string longName, int &refToValue)
            : Option(longName, '\0', true, no_key), val(refToValue) {}

        ~IntOption() = default;

        virtual void execute([[maybe_unused]] std::string &&value) override final
        {
            val = std::stoi(value, nullptr);
        }

        virtual std::shared_ptr<Option> clone() const override
        {
            return std::make_shared<IntOption>(*this);
        }

    private:
        int &val;
    };

}