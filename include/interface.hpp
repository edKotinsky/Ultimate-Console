#pragma once

#include "argument.hpp"
#include "option.hpp"
#include "dictionary.hpp"

#include <iosfwd>
#include <string>
#include <functional>
#include <memory>

namespace UC
{
    using command_t = std::shared_ptr<UC::Command>;
    using dictionary_t = std::shared_ptr<UC::Dictionary>;

    /**
        @brief createDictionary is a function which returns dictionary_t

        Dictionary is a list of commands and variables.

        @return dictionary_t
    */
    dictionary_t createDictionary();

    /**
        @brief setInput function sets input stream to dictionary
    
        It can be std::istream or console arguments

        @param[in,out] dictionary
        @param[in] inputStream
    */
    void setInput(dictionary_t& dictionary, std::istream &inputStream);

    /**
        @brief setInput function sets input stream to dictionary
    
        It can be std::istream or console arguments

        @param[in,out] dictionary
        @param[in] argCount argc
        @param[in] args argv
    */
    void setInput(dictionary_t& dictionary, int argCount, char **args);

    /**
        @brief addCommand adds command to dictionary

        Command is a class, which contain the name, callback function,
        an array of arguments and an array of options

        @param[in,out] dictionary
        @param[in] name
        @param[in] callback
    */
    std::shared_ptr<Command>
    addCommand(dictionary_t& dictionary, 
                std::string &&name, 
                std::function<void()> callback);

    /**
        @brief addVariable adds variable to dictionary

        Variable is a class, which contain the name string and a reference to
        a value; when Variable executes, it changes this value
        This function has a parameter Argument& argument because 
        reference to a value was provided by Argument derived classes

        @param[in,out] dictionary
        @param[in] name
        @param[in] argument
    */
    void addVariable(dictionary_t& dictionary, 
                std::string &&name, Argument &argument);

    void addVariable(dictionary_t& dictionary, 
                std::string &&name, Argument &&argument);


    /**
        @brief addOption adds option to a command

        Option is a class, which contain the name string and a reference to
        a value; when executes, it changes this value

        @param[in,out] command
        @param[in] option
    */
    void addOption(command_t command, Option &option);

    /**
        @brief addOption adds option to a command

        Option is a class, which contain the name string and a reference to
        a value; when executes, it changes this value
        Gets an rvalue reference

        @param[in,out] command
        @param[in] option
    */
    void addOption(command_t command, Option &&option);

    void addArgument(command_t command, Argument &argument);

    void addArgument(command_t command, Argument &&argument);

    dictionary_state run(dictionary_t& dictionary);

    component_error getError();

    void printError(const component_error& error);
} // namespace uc
