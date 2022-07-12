#include <uccmd.hpp>
#include "ulticon.hpp"
#include "ucconf.hpp"
#include <ios>
#include <memory>

namespace UC
{
    Option::Option(std::string longName, char shortName,
                   bool isValueRequired, bool sNameAllowed)
        : lName(longName), sName(shortName), isValueReq(isValueRequired)
    {
        if (!longName.size())
            throw std::logic_error("Option::Option: name is empty");
        if (sNameAllowed && !shortName)
            throw std::logic_error("Option::Option: key is empty");
    }

    const std::vector<std::shared_ptr<Option>>::iterator 
    Command::findOptionShortName(std::string const &name)
    {
        auto it = sNameVec.begin();
        auto optvecit = optvec.begin();

        while (it != sNameVec.end())
        {
            #ifdef UC_DEBUG
                std::cout << "debug: findOptionShortName:name: " 
                    << name << std::endl;
                std::cout << "debug: findOptionShortName:it:   " 
                    << *it << std::endl;
            #endif

            if (*it == name[0]) return optvecit;
            optvecit++;
            it++;    
        }
        throw UC::component_error
            (UC::error_code::cmd_key_does_not_exist, name);
    }

    const std::vector<std::shared_ptr<Option>>::iterator 
    Command::findOptionLongName(std::string const &name)
    {
        auto it = optvec.begin();

        while (it != optvec.end())
        {
            if ((*it)->getLongName() == name)
                return it;
            it++;
        }
        throw UC::component_error
            (UC::error_code::cmd_option_does_not_exist, name);
    }

    void Command::setArgumentValue(std::string &&value)
    {
        if (argCounter == argvec.size())
            throw UC::component_error
                    (UC::error_code::cmd_too_many_args);
        argvec[argCounter]->execute(std::move(value));
        argCounter++;
    }

    void Command::addOption(Option &opt)
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

    void Command::addOption(std::shared_ptr<Option> optsptr)
    {
        #ifdef UC_DEBUG
            std::cerr << 
                "debug: command:addOption(std::shared_ptr<Option>): "
                << optsptr->getLongName() << " : "
                << optsptr->getShortName() << std::endl;
        #endif

        char sname = optsptr->getShortName();
        if (sname)
            sNameVec.push_back(sname);
        optvec.push_back(std::move(optsptr));
    }

} // namespace cmd
