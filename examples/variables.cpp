/*
 * This example demonstrates Ultimate Console variables
 * Variable contain three syntax components: name of a variable,
 * equality symbol and a value: variable = value; and this
 * construction must ends with EOL ';', '\n' or EOF '\0' symbol.
 */

#include <ostream>
#include <iostream>

#include <ulticon.hpp>

#include <ulticon/intargument.hpp>
#include <ulticon/stringargument.hpp>
#include <ulticon/boolargument.hpp>

int main(int, char**)
{
    int intValue = 0;
    std::string stringValue;
    bool exit = false;

    try 
    {
        do 
        {
            // first of all create dictionary
            UC::dictionary_t dictionary = UC::createDictionary();

            // specify the input; in this example we're gonna get data from standard input
            UC::setInput(dictionary, std::cin);

            // you can create arguments and options first and then pass it to add* functions
            UC::IntArgument intArg(intValue);
            UC::StringArgument strArg(stringValue);

            UC::addVariable(dictionary, "int-value", intArg);
            UC::addVariable(dictionary, "string-value", strArg);

            // or you can pass an rvalue straightaway
            UC::addVariable(dictionary, "exit", UC::BoolArgument(exit));

            // this is the main function - it gets data from input source, disassemblies it
            // finds names in lists and executes it
            UC::run(dictionary);

            std::cout << std::endl;
            std::cout << "int-value    = " << intValue << std::endl;
            std::cout << "string-value = " << stringValue << std::endl;
            std::cout << "exit         = " << exit << std::endl;
            std::cout << std::endl;

        } while (!exit); 
    }
    catch (UC::component_error const& e)
    {
        // UC::component_error provides error messages like pair "error code - word"
        // it's done so that you can override your own error messages or call standart UC::printError
        UC::printError(e);
    }

    return 0;
}