#pragma once

#include <include/argument.hpp>

namespace UC
{
    /**
        @brief BoolArgument class provides an argument with bool type

        BoolArgument can get the word, which must correspond to 
        stringTrue or stringFalse values; by default these values are
        "true" and "false", but user can change it
    */

    struct BoolArgument : Argument
    {
    
        /**
            @brief BoolArgument ctor gets a reference 
            to user's bool variable 

            Also ctor can get two strings, which determines the true and
            the false words; by default these strings are "true" and "false"

            @param[in,out] refToValue is a lvalue reference
            @param[in] stringTrue
            @param[in] stringFalse
        */
        BoolArgument(bool &refToValue, 
                        std::string stringTrue = "true", 
                        std::string stringFalse = "false")
            : ref(refToValue), trueStr(stringTrue), 
            falseStr(stringFalse) {}

        BoolArgument(BoolArgument const& other) = default;

        virtual std::shared_ptr<Argument> clone() const override
        {
            return std::make_shared<BoolArgument>(*this);
        }

        /**
            @brief execute method

            Gets a value and compares it with two strings: stringTrue and
            stringFalse, which by default are "true" and "false"

            If a value matches to stringTrue, bool variable will be set to
            "true". If a value matches to stringFalse, bool variable will
            be set to "false"

            Otherwise if a value does not match with stringTrue and stringFalse
            values, method will throw an exception 
            runtime_error "BoolArgument: value is not bool"

            @param[in] value
        */

        void execute(std::string &&value) override
        {
            if (value == trueStr) ref = true;
            else if (value == falseStr) ref = false;
            else throw std::runtime_error("BoolArgument: value is not bool"); 
        }
        
    private:
        bool &ref;
        std::string trueStr;
        std::string falseStr;
    };
}