#include "uccmd.hpp"
#include "ulticon.hpp"
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

    const std::vector<std::unique_ptr<Option>>::iterator 
    Command::findOptionShortName(std::string const &name)
    {
        std::vector<char>::iterator it = sNameVec.begin();
        std::vector<std::unique_ptr<Option>>::iterator optvecit = optvec.begin();

        while (it != sNameVec.end())
        {
            if (*it == name[0]) return optvecit;
            optvecit++;
            it++;    
        }
        throw UC::component_error
                (UC::error_code::cmd_key_does_not_exist, 
                 name);
    }

    const std::vector<std::unique_ptr<Option>>::iterator 
    Command::findOptionLongName(std::string const &name)
    {
        std::vector<std::unique_ptr<Option>>::iterator it = optvec.begin();

        while (it != optvec.end())
        {
            if ((*it)->getLongName() == name)
                return it;
            it++;
        }
        throw UC::component_error
                (UC::error_code::cmd_option_does_not_exist, 
                 name);
    }

    void Command::setArgumentValue(std::string &&value)
    {
        if (argCounter == argvec.size())
            throw UC::component_error
                    (UC::error_code::cmd_too_many_args);
        argvec[argCounter]->execute(std::move(value));
        argCounter++;
    }

} // namespace cmd

// I DON'T KNOW WHY IT DOES NOT WORK but linker says:
// undefined reference to «uccmd::CommandList<UC::Command>::getCommand(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)»

// namespace uccmd
// {
//     template <class T>
//     typename std::vector<std::shared_ptr<T>>::iterator 
//     CommandList<T>::getCommand(std::string const &name)
//     {
//         typename std::vector<std::shared_ptr<T>>::iterator it = commands.begin();
//         for (; it != commands.end(); ++it)
//             if ((*it)->getName() == name)
//                 return it;
//         throw UC::component_error
//                 (UC::error_code::cmd_command_does_not_exist, 
//                  name);
//     }
// } // namespace uccmd