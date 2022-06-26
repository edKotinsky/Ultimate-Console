#include "callback.hpp"
#include "interface.hpp"
#include "option.hpp"
#include "ucerr.hpp"
#include <iostream>
#include <string>

#include <ulticon.hpp>

// example class
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
        // first of all create dictionary
        UC::dictionary_t dict = UC::createDictionary();

        // specify the input; in this example we're gonna get data from console args
        UC::setInput(dict, argc, argv);

        // create the command with name "userdata" and attach it to dictionary
        // UC::callback allows you to pass class method
        UC::command_t consoleArgs = UC::addCommand(dict, 
            "command", 
            UC::callback(conArgs, &ConsoleArgs::print));

        // adding options
        UC::addOption(consoleArgs, UC::StringOption("value1", conArgs.val1));
        UC::addOption(consoleArgs, UC::IntOption("value2", conArgs.val2));
        UC::addOption(consoleArgs, UC::BoolOption("value3", conArgs.val3));

        // this is the main function - it gets data from input source, disassemblies it
        // finds names in lists and executes it
        UC::run(dict);

    } catch (UC::component_error const& e) {
        UC::printError(e);
    }

    return 0;
}