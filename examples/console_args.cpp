#include "callback.hpp"
#include "interface.hpp"
#include "option.hpp"
#include "ucerr.hpp"
#include <iostream>
#include <string>

#include <ulticon.hpp>

struct ConsoleArgs
{
    void print()
    {
        std::cout << "ConsoleArgs" << std::endl;
        std::cout << "val1 = " << val1 << std::endl;
        std::cout << "val2 = " << val2 << std::endl;
        std::cout << "val3 = " << val3 << std::endl;
    }

    std::string val1;
    int val2 = 0;
    bool val3 = false;
};

int main(int argc, char** argv)
{
    ConsoleArgs conArgs;

    for (int i = 0; i < argc; ++i)
        std::cout << argv[i];
    std::cout << std::endl;

    try {
        UC::dictionary_t dict = UC::createDictionary();
        UC::setInput(dict, argc, argv);

        UC::command_t consoleArgs = UC::addCommand(dict, 
            "command", 
            UC::callback(conArgs, &ConsoleArgs::print));

        UC::StringOption opt1("value1", conArgs.val1);
        UC::IntOption opt2("value2", conArgs.val2);
        UC::BoolOption opt3("value3", conArgs.val3);

        UC::addOption(consoleArgs, opt1);
        UC::addOption(consoleArgs, opt2);
        UC::addOption(consoleArgs, opt3);

        UC::run(dict);

    } catch (UC::component_error const& e) {
        UC::printError(e);
    }

    return 0;
}