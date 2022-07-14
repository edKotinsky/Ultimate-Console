/**
    @file boolalphaoption.hpp
*/
#pragma once

#include "ucerr.hpp"
#include <include/option.hpp>

namespace UC
{
    /**
        @brief BoolalphaOption provides an option for bool values

        Option contains long name, short name, some value and 
        execution method. When execution method is called and
        the value passed into it, this method compares it with
        two strings: true and false. If the value is "true",
        bool variable sets to true, if "false" - to false.
        If value does not match with these strings, method
        throws an exception.
    */
    struct BoolalphaOption : Option
    {
        BoolalphaOption(std::string longName, char shortName, bool &refToValue, 
        std::string stringTrue = "true", std::string stringFalse = "false")
            : Option(longName, shortName, true), val(refToValue), 
            trueStr(stringTrue), falseStr(stringFalse) {}

        BoolalphaOption(std::string longName, bool &refToValue,
        std::string stringTrue = "true", std::string stringFalse = "false")
            : Option(longName, '\0', true, no_key), 
            val(refToValue), trueStr(stringTrue), falseStr(stringFalse) {}

        virtual void 
        execute([[maybe_unused]] std::string &&value) override final
        {
            if (value == trueStr)
                val = true;
            else if (value == falseStr)
                val = false;
            else 
                throw UC::component_error
                    (error_code::opt_boola_string, value);
        }

        virtual std::shared_ptr<Option> clone() const override
        {
            return std::make_shared<BoolalphaOption>(*this);
        }

    private:
        bool &val;
        std::string trueStr;
        std::string falseStr;
    };
}