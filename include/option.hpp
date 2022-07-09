#pragma once

#include <memory>
#include <stdexcept>
#include <string>

namespace UC
{
    const bool no_key = false;
    const bool no_assignment = false;

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
} // namespace cmd
