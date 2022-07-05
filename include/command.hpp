#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <functional>

#include "ucconf.hpp"
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
                std::cerr << "debug: command:addArgument(Argument&)" << std::endl;
            #endif

            argvec.emplace_back(&arg);
        }

        inline void addArgument(std::shared_ptr<Argument> arguptr)
        {
            argvec.push_back(std::move(arguptr));
        }

        void addOption(Option &opt)
        {

            #ifdef UC_DEBUG
                std::cerr << "debug: command:addOption(Option&): "
                    << opt.getLongName() << " : "
                    << opt.getShortName() << std::endl;
            #endif

            char sname = opt.getShortName();
            if (sname)
                sNameVec.push_back(sname);
            optvec.emplace_back(&opt);
        }

        void addOption(std::shared_ptr<Option> optuptr)
        {
            #ifdef UC_DEBUG
                std::cerr << 
                    "debug: command:addOption(std::shared_ptr<Option>): "
                    << optuptr->getLongName() << " : "
                    << optuptr->getShortName() << std::endl;
            #endif
            char sname = optuptr->getShortName();
            if (sname)
                sNameVec.push_back(sname);
            optvec.push_back(std::move(optuptr));
        }

        inline const std::string &getName()
        {
            return n;
        }

        const std::vector<std::shared_ptr<Option>>::iterator
        findOptionShortName(std::string const &name);

        const std::vector<std::shared_ptr<Option>>::iterator
        findOptionLongName(std::string const &name);

        void setArgumentValue(std::string &&value);

        inline void resetArgumentCounter()
        {
            argIt = argvec.begin();
        }

        inline void setOptionValue(std::vector<std::shared_ptr<Option>>::iterator optionIt,
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

        std::vector<std::shared_ptr<Argument>> argvec;
        std::vector<std::shared_ptr<Argument>>::iterator argIt;
        size_t argCounter = 0;

        std::vector<char> sNameVec;
        std::vector<std::shared_ptr<Option>> optvec;
    };


} // namespace uc
