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
} // namespace uc
