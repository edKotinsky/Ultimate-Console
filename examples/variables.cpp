/*
 * This example demonstrates Ultimate Console variables
 * Variable contain three syntax components: name of a variable,
 * equality symbol and a value: variable = value; and this
 * construction must ends with EOL ';', '\n' or EOF '\0' symbol.
 */

#include "argument.hpp"
#include "interface.hpp"
#include "ucerr.hpp"
#include <ostream>
#include <ulticon.hpp>
#include <iostream>

int main(int, char**)
{
    int intValue = 0;
    std::string stringValue;
    bool exit = false;

    try 
    {
        do 
        {
            UC::dictionary_t dictionary = UC::createDictionary();

            UC::setInput(dictionary, std::cin);

            UC::IntArgument intArg(intValue);
            UC::StringArgument strArg(stringValue);
            UC::BoolArgument exitArg(exit, "true", "false");

            UC::addVariable(dictionary, "int-value", intArg);
            UC::addVariable(dictionary, "string-value", strArg);
            UC::addVariable(dictionary, "exit", exitArg);

            UC::run(dictionary);

            std::cout << "intValue    = " << intValue << std::endl;
            std::cout << "stringValue = " << stringValue << std::endl;
            std::cout << "exitValue   = " << exit << std::endl;

        } while (!exit); 
    }

    catch (UC::component_error const& e)
    {
        UC::printError(e);
    }

    return 0;
}