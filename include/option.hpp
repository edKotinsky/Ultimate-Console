#pragma once

#include <memory>
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
        Option(std::string longName, char shortName,
               bool isValueRequired = true, bool sNameAllowed = true);

        Option() = delete;
        virtual ~Option() = default;

        virtual char getShortName() = 0;
        virtual const std::string &getLongName() = 0;

        virtual std::unique_ptr<Option> clone() const = 0;

        virtual void execute(std::string && = "") = 0;

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
        @brief BoolOption provides option for bool values

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

        virtual std::unique_ptr<Option> clone() const override
        {
            return std::make_unique<BoolOption>(*this);
        }

    private:
        bool &val;
    };

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

        virtual std::unique_ptr<Option> clone() const override
        {
            return std::make_unique<StringOption>(*this);
        }

    private:
        std::string &val;
    };

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

        virtual std::unique_ptr<Option> clone() const override
        {
            return std::make_unique<IntOption>(*this);
        }

    private:
        int &val;
    };

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

        virtual std::unique_ptr<Option> clone() const override
        {
            return std::make_unique<CallbackOption>(*this);
        }

    private:
        std::function<void()> val;
    };

} // namespace cmd
