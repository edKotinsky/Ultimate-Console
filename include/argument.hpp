#pragma once

#include <memory>
#include <stdexcept>
#include <string>

namespace UC
{
    /**
        @brief Base Argument class

        Argument is a word passed after the command, has not name,
        but Arguments has serial number in the Command class,
        which determines by order, in which these Arguments were passed

        Argument has one pure virtual method execute
    */
    struct Argument
    {
        virtual ~Argument() = default;

        virtual std::shared_ptr<Argument> clone() const = 0;

        /**
            @brief Pure virtual Argument's method

            If you want to create your custom argument, you need to 
            override it. 
        */

        virtual void execute(std::string &&str) = 0;
    };

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
                    throw std::runtime_error("IntArgument: value is not a number");

            ref = std::stoi(value, nullptr);
        }

    private:
        int &ref;
    };

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
} // namespace uc
