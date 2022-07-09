#pragma once

#include <include/argument.hpp>

namespace UC
{
    /**
        @brief StringArgument class

        StringArgument can get any word with any characters; if 
        a word contains spaces, it must be in quotation marks like this:
        "example word"
    */
    struct StringArgument : Argument
    {

        /**
            @brief StringArgument ctor gets a reference 
            to user's std::string variable

            When StringArgument is executing, it changes the value
            by given reference

            @param[in,out] refToValue is a lvalue reference
        */

        StringArgument(std::string &refToValue)
            : ref(refToValue) {}
        ~StringArgument() = default;

        StringArgument(StringArgument const& other) = default;

        virtual std::shared_ptr<Argument> clone() const override
        {
            return std::make_shared<StringArgument>(*this);
        }

        void execute(std::string &&value) override
        {
            ref = value;
        }

    private:
        std::string &ref;
    };
}