/**
    @file interface.hpp
    @brief The header for API
*/

#pragma once

#include "dictionary.hpp"

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

    /**
        @brief addVariable adds variable to dictionary

        Variable is a class, which contain the name string and a reference to
        a value; when Variable executes, it changes this value
        This function has a parameter Argument&& argument because 
        reference to a value was provided by Argument derived classes
        Gets and rvalue-reference to Argument

        @param[in,out] dictionary
        @param[in] name
        @param[in] argument
    */
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

    /**
        @brief addArgument adds argument to a command

        Argument has only the reference to a value, it has not name.
        
        @param[in,out] command
        @param[in,out] argument
    */
    void addArgument(command_t command, Argument &argument);

    /**
        @brief addArgument adds argument to a command

        Argument has only the reference to a value, it has not name.
        Gets an rvalue-reference to an argument

        @param[in,out] command
        @param[in] argument
    */
    void addArgument(command_t command, Argument &&argument);

    /**
        @brief The main function where all the magick happens

        This function disassemblies, translates the lexems,
        finds commands, options, arguments and variables in
        lists and then executes all.

        Note than if something throw the exception, your data may 
        be in invalid state. For example, you have three variables:
        int var1 = 0
        string var2 = ""
        bool var3 = false
        and options: int-variable, string-variable and bool-variable. 
        The command is "my-command". The input string is:
        my-command --int-variable=123 --string-variable= --bool-variable
        Error will occure after "--string-variable", because there are no
        value. Function will throw the exception "missed value", and your 
        data will be in this state:
        var1 = 123
        string var2 = ""
        bool var3 = false

        @param[in,out] dictionary
        @return dictionary_state
    */
    dictionary_state run(dictionary_t& dictionary);

    /**
        @brief callback

        Callback function allows user to pass a pointer to class method 
        with any arguments number like a pointer to a void(void) function 

        @param[in,out] object is a reference to user's class object
        @param[in] f is a pointer to class method
        @param[in] args is a template variadic parameter
        @return pointer to a void(void) type function
    */

    template <typename T, typename... Args>
    auto callback(T &object, void (T::*f)(Args &...args), Args &...args)
    {
        return [f, &object, &args...]() -> void
        { (object.*f)(args...); };
    }

    /**
        @brief callback

        Callback function allows user to pass a pointer to function with
        arguments and wrap it into a pointer to void(void) function

        @param[in] f is a pointer to function
        @param[in] args is a template variadic parameter
        @return pointer to a void(void) type function
    */

    template <typename... Args>
    auto callback(void (*f)(Args &...args), Args &...args)
    {
        return [f, &args...]() -> void
        { (*f)(args...); };
    }

    template <typename... Args>
    auto callback(void (*f)(Args const&...args), Args &...args)
    {
        return [f, &args...]() -> void
        { (*f)(args...); };
    }
} // namespace uc
