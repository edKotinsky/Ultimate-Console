/**
    @file intargument.hpp
*/
#pragma once

#include "ucerr.hpp"
#include <include/argument.hpp>

namespace UC
{
    /**
        @brief IntArgument class provides an argument with int type

        IntArgument can get the word, which contain only numeral characters
    */
    struct IntArgument : Argument
    {

        /**
            @brief IntArgument ctor gets a reference 
            to user's std::string variable

            When IntArgument is executing, it changes the value
            by given reference

            @param[in,out] refToValue is a lvalue reference
        */

        IntArgument(int &refToValue)
            : ref(refToValue) {}
        ~IntArgument() = default;

        IntArgument(IntArgument const& other) = default;

        virtual std::shared_ptr<Argument> clone() const override
        {
            return std::make_shared<IntArgument>(*this);
        }

        /**
            @brief execute
        */

        void execute(std::string &&value) override
        {
            for (auto it : value)
                if (it < '0' || it > '9')
                    throw UC::component_error
                        (error_code::arg_int_val_not_numeral, value);

            ref = std::stoi(value, nullptr);
        }

    private:
        int &ref;
    };
}