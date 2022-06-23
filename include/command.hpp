#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

#include <ucconf.hpp>
#include "argument.hpp"
#include "option.hpp"

using function_t = std::function<void()>;

namespace UC
{
    /**
        @brief Command class

        Command contains the command name and lists of the options and the arguments
    */

    class Command
    {
    public:
        Command(std::string name, function_t callback)
            : n(name), cb(callback) {}

        inline void addArgument(Argument &arg)
        {
            #ifdef UC_DEBUG
                std::cerr << "debug: command.addArgument" << std::endl;
            #endif

            argvec.emplace_back(&arg);
        }

        void addOption(Option &opt)
        {

            #ifdef UC_DEBUG
                    std::cerr << "debug: command.addOption: "
                  << opt.getLongName() << " : "
                  << opt.getShortName() << std::endl;
            #endif

            char sname = opt.getShortName();
            if (sname)
                sNameVec.push_back(sname);
            optvec.emplace_back(&opt);
        }

        inline const std::string &getName()
        {
            return n;
        }

        const std::vector<Option *>::iterator
        findOptionShortName(std::string const &name);

        const std::vector<Option *>::iterator
        findOptionLongName(std::string const &name);

        void setArgumentValue(std::string &&value);

        inline void resetArgumentCounter()
        {
            argIt = argvec.begin();
        }

        inline void setOptionValue(std::vector<Option *>::iterator optionIt,
                            std::string &&value)
        {
            (*optionIt)->execute(std::move(value));
        }

        inline void execute()
        {
            cb();
        }

        Command(Command &) = default;
        Command(Command &&) = delete;
        ~Command() = default;

    private:
        std::string n;
        function_t cb;

        std::vector<Argument *> argvec;
        std::vector<Argument *>::iterator argIt;
        size_t argCounter = 0;

        std::vector<char> sNameVec;
        std::vector<Option *> optvec;
    };


} // namespace uc
