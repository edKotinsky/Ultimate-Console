#include "callback.hpp"
#include "interface.hpp"
#include "option.hpp"
#include "ucerr.hpp"
#include <ios>
#include <iostream>
#include <string>

#include <ulticon.hpp>

struct Example
{
    void print()
    {
        std::cout << "Example method called" << std::endl;
        std::cout << "val1 = " << val1 << std::endl;
        std::cout << "val2 = " << val2 << std::endl;
        std::cout << "val3 = " << val3 << std::endl;
        std::cout << std::boolalpha;
        std::cout << "val4 = " << val4 << std::endl;
        std::cout << "val5 = " << val5 << std::endl;
    }

    std::string val1;
    std::string val2;
    std::string val3;
    bool val4 = false;
    bool val5 = false;
};

int main(int, char**)
{
    Example ex;

    try 
    {
        UC::dictionary_t dict = UC::createDictionary();

        UC::setInput(dict, std::cin);

        UC::showGreeting(dict, true);
        UC::setGreeting(dict, "Please, enter a command: ");

        UC::command_t example = 
            UC::addCommand(dict, 
            "command", 
            UC::callback(ex, &Example::print));
        
        UC::StringOption str0("a", 'a', ex.val1);
        UC::StringOption str1("b", 'b', ex.val2);
        UC::StringOption str2("c", 'c', ex.val3);
        UC::BoolOption bool0("d", 'D', ex.val4);
        UC::BoolOption bool1("e", 'E', ex.val5);

        UC::addOption(example, str0);
        UC::addOption(example, str1);
        UC::addOption(example, str2);
        UC::addOption(example, bool0);
        UC::addOption(example, bool1);

        UC::run(dict);
    } 
    catch (UC::component_error const& e) 
    {
        UC::printError(e);    
    }

    return 0;
}