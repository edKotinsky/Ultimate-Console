#include <ios>
#include <iostream>
#include <string>

#include <ulticon.hpp>

#include <ulticon/stringoption.hpp>
#include <ulticon/booloption.hpp>
#include <ulticon/intoption.hpp>
#include <ulticon/boolalphaoption.hpp>

// example class
struct ConsoleArgs
{
    void print()
    {
        std::cout << "ConsoleArgs" << std::endl;
        std::cout << "string = " << stropt << std::endl;
        std::cout << "int = " << intopt << std::endl;
        std::cout << std::boolalpha;
        std::cout << "bool = " << boolopt << std::endl;
        std::cout << "bool = " << boola << std::endl;
    }

    std::string stropt;
    int intopt = 0;
    bool boolopt = false;
    bool boola = false;
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
        UC::addOption(consoleArgs, UC::StringOption("string", conArgs.stropt));
        UC::addOption(consoleArgs, UC::IntOption("int", conArgs.intopt));
        UC::addOption(consoleArgs, UC::BoolOption("bool", conArgs.boolopt));
        UC::addOption(consoleArgs, UC::BoolalphaOption("boolalpha", conArgs.boola));

        // this is the main function - it gets data from input source, disassemblies it
        // finds names in lists and executes it
        UC::run(dict);

    } catch (UC::component_error const& e) {
        UC::printError(e);
    }

    return 0;
}