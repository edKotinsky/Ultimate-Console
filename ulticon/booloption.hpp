/**
    @file booloption.hpp
*/
#pragma once

#include <include/option.hpp>

namespace UC 
{
    /**
        @brief BoolOption provides an option for bool values

        Option contains long name, short name, some value and 
        execution method. When execution method is called,
        it inverses stored value
    */
    struct BoolOption : Option
    {
        BoolOption(std::string longName, char shortName, bool &refToValue)
            : Option(longName, shortName, no_assignment), 
                val(refToValue) {}

        BoolOption(std::string longName, bool &refToValue)
            : Option(longName, '\0', no_key, 
                no_assignment), val(refToValue) {}

        ~BoolOption() = default;

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
            val = !val;
        }

        virtual std::shared_ptr<Option> 
        clone() const override
        {
            return std::make_shared<BoolOption>(*this);
        }

    private:
        bool &val;
    };
}