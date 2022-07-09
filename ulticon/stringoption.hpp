#pragma once

#include <include/option.hpp>

namespace UC
{
    /**
        @brief StringOption provides an option for std::string values

        Option contains long name, short name, some value and 
        execution method. When disassembler invokes execute method,
        it passes the value into this method.
    */
    struct StringOption : Option
    {
        StringOption(std::string longName, char shortName, 
                    std::string &refToValue)
            : Option(longName, shortName, true), val(refToValue) {}

        StringOption(std::string longName, std::string &refToValue)
            : Option(longName, '\0', true, no_key), 
                val(refToValue) {}

        ~StringOption() = default;

        virtual char 
        getShortName() override final
        {
            return sName;
        }

        virtual const std::string 
        &getLongName() override final
        {
            return lName;
        }

        virtual void 
        execute([[maybe_unused]] std::string &&value) override final
        {
            val = std::move(value);
        }

        virtual std::shared_ptr<Option> 
        clone() const override
        {
            return std::make_shared<StringOption>(*this);
        }

    private:
        std::string &val;
    };
}