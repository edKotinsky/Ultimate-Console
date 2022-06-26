#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <functional>

namespace UC
{
    const bool no_short_name = false;
    const bool asgnmt_is_no_req = false;

    /**
        @brief Option pure virtual base class

        Option contains long name, short name, some value and 
        execution method. When option is passed, run function
        calls its execution method. This method knows, how to
        change the value, which been given to Option.
    */
    struct Option
    {
        /**
            @brief Option ctor

            If you creating your own Option, you need to know,
            what are his parameters doing. longName and shortName
            are names. 
            
            isValueRequired indicates, is it necessary to pass 
            value to option or not. It usually determines at the 
            start and does not changes. For example, StringOption
            ctor sets this variable to true, and BoolOption to false.
            
            sNameAllowed indicates, has the particular object one 
            character name or not. You need to specify two ctors 
            of your option: ctor with char shortName and without 
            it. In ctor with it you must pass true to sNameAllowed, 
            without it - false. Otherwise you will get undefined behavior.

            @param[in] longName name of option
            @param[in] shortName key of an option
            @param[in] isValueRequired specifies, is option requires value or not
            @param[in] isNameAllowed specifies, has option object key name or not
        */
        Option(std::string longName, char shortName,
               bool isValueRequired = true, bool sNameAllowed = true);

        Option() = delete;
        virtual ~Option() = default;

        /**
            @brief returns key name of an option
            @return one character key name
        */
        virtual char getShortName() = 0;

        /**
            @brief returns name of an option
            @return long std::string name
        */
        virtual const std::string &getLongName() = 0;

        /**
            @brief this function is necessary for internal logic

            It will contain one string:
            return std::make_shared<SomeOption>(*this);

            @return std::shared_ptr<Option> 
        */
        virtual std::shared_ptr<Option> clone() const = 0;

        /**
            @brief execute method

            This is the main method of an option. When option
            is found in lists, disassembler invokes this method
            and, if option isValueRequired = true, passes an
            argument to it. Or throws an exception, if for this
            option value is not given.

            @param[in] value
        */
        virtual void execute(std::string &&value = "") = 0;

        bool valueAssignmentReq()
        {
            return isValueReq;
        }

    protected:
        std::string const lName;
        char const sName;
        bool isValueReq;
    };

    /**
        @brief BoolOption provides an option for bool values

        Option contains long name, short name, some value and 
        execution method. When execution method is called,
        it inverses stored value
    */
    struct BoolOption : Option
    {
        BoolOption(std::string longName, char shortName, bool &refToValue)
            : Option(longName, shortName, asgnmt_is_no_req), val(refToValue) {}

        BoolOption(std::string longName, bool &refToValue)
            : Option(longName, '\0', no_short_name, asgnmt_is_no_req), val(refToValue) {}

        ~BoolOption() = default;

        virtual char getShortName() override final
        {
            return sName;
        }

        virtual const std::string &getLongName() override final
        {
            return lName;
        }

        virtual void execute([[maybe_unused]] std::string &&value) override final
        {
            val = !val;
        }

        virtual std::shared_ptr<Option> clone() const override
        {
            return std::make_shared<BoolOption>(*this);
        }

    private:
        bool &val;
    };

    /**
        @brief StringOption provides an option for std::string values

        Option contains long name, short name, some value and 
        execution method. When disassembler invokes execute method,
        it passes the value into this method.
    */
    struct StringOption : Option
    {
        StringOption(std::string longName, char shortName, std::string &refToValue)
            : Option(longName, shortName, true), val(refToValue) {}

        StringOption(std::string longName, std::string &refToValue)
            : Option(longName, '\0', true, no_short_name), val(refToValue) {}

        ~StringOption() = default;

        virtual char getShortName() override final
        {
            return sName;
        }

        virtual const std::string &getLongName() override final
        {
            return lName;
        }

        virtual void execute([[maybe_unused]] std::string &&value) override final
        {
            val = std::move(value);
        }

        virtual std::shared_ptr<Option> clone() const override
        {
            return std::make_shared<StringOption>(*this);
        }

    private:
        std::string &val;
    };

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
            : Option(longName, '\0', true, no_short_name), val(refToValue) {}

        ~IntOption() = default;

        virtual char getShortName() override final
        {
            return sName;
        }

        virtual const std::string &getLongName() override final
        {
            return lName;
        }

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

    /**
        @brief CallbackOption is a wrapper for user function

        Option contains long name, short name, some value and 
        execution method. When disassembler invokes execution
        method, it calls user function.
    */
    struct CallbackOption : Option
    {
        CallbackOption(std::string longName, char shortName, std::function<void()> refToValue)
            : Option(longName, shortName, asgnmt_is_no_req), val(refToValue) {}

        CallbackOption(std::string longName, std::function<void()> refToValue)
            : Option(longName, '\0', no_short_name, asgnmt_is_no_req), val(refToValue) {}

        ~CallbackOption() = default;

        virtual char getShortName() override final
        {
            return sName;
        }

        virtual const std::string &getLongName() override final
        {
            return lName;
        }

        virtual void execute([[maybe_unused]] std::string &&value) override final
        {
            val();
        }

        virtual std::shared_ptr<Option> clone() const override
        {
            return std::make_shared<CallbackOption>(*this);
        }

    private:
        std::function<void()> val;
    };

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
            : Option(longName, '\0', true, no_short_name), 
            val(refToValue), trueStr(stringTrue), falseStr(stringFalse) {}

        virtual char getShortName() override final
        {
            return sName;
        }

        virtual const std::string &getLongName() override final
        {
            return lName;
        }

        virtual void execute([[maybe_unused]] std::string &&value) override final
        {
            if (value == trueStr)
                val = true;
            else if (value == falseStr)
                val = false;
            else 
                throw std::runtime_error("String given to BoolalphaOption is not a bool value");
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

} // namespace cmd
