/**
    @file callbackoption.hpp
*/
#pragma once

#include <include/option.hpp>

#include <functional>

namespace UC
{
    /**
        @brief CallbackOption is a wrapper for user function

        Option contains long name, short name, some value and 
        execution method. When disassembler invokes execution
        method, it calls user function.
    */
    struct CallbackOption : Option
    {
        CallbackOption(std::string longName, char shortName, 
        std::function<void()> refToValue)
            : Option(longName, shortName, no_assignment), val(refToValue) {}

        CallbackOption(std::string longName, 
        std::function<void()> refToValue)
            : Option(longName, '\0', no_key, no_assignment), val(refToValue) {}

        ~CallbackOption() = default;

        virtual void 
        execute([[maybe_unused]] std::string &&value) override final
        {
            val();
        }

        virtual std::shared_ptr<Option> 
        clone() const override
        {
            return std::make_shared<CallbackOption>(*this);
        }

    private:
        std::function<void()> val;
    };

}