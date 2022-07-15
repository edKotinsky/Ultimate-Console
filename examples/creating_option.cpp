/**
    @file creating_option.cpp
    @brief Example how to create your option

    Compile it and try to enter
    print --word="This" --word="is" -w "an" --word=example
    Play with this string for better knowing about the
    Ultimate Console syntax and semantics.
*/
#include "interface.hpp"
#include "option.hpp"
#include "ucerr.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include <ulticon.hpp>

// #include <ulticon/printerror.hpp>

#include <ulticon/stringoption.hpp>

using strl_t = std::list<std::string>;



// custom option
struct StringListOption : UC::Option
{
    // you can define one ctor with name, key and  reference
    StringListOption(std::string name, char key, strl_t& ref)
    : UC::Option(name,          // long name
                 key,          // short name (key)
                 true),  // is this option requires value assingment
                 reflist(ref) {}

    // or you can define one ctor with only name and reference
    // so you will not can specify the key (short one character 
    // name) of your option
    StringListOption(std::string name, strl_t& ref)
    : UC::Option(name,          // long name
                 true,         // short name (key)
                 false), // is this option requires value assingment
                 reflist(ref) {}

    // or you can define both ctors.
    // as well, you can create ctor without any reference

    // well, you just need to define this
    std::shared_ptr<Option> clone() const
    {
        return std::make_shared<StringListOption>(*this);
    }

    // this is the main method of the Option
    // here you can do anything you want
    void execute(std::string &&value)
    {
        reflist.push_back(value);
    }

    // if your option does not require value,
    // just type [[maybe_unused]] before value
    // like here:
    // void execute([[maybe_unused]] std::string&&)

private:
    strl_t &reflist;
};

struct HelpOption : UC::Option
{
    HelpOption()
    : UC::Option("help", true, false) {}

    std::shared_ptr<Option> clone() const
    {
        return std::make_shared<HelpOption>(*this);
    }

    void execute([[maybe_unused]]std::string&& = "")
    {
        std::cout << "Print help and terminate" << std::endl;
        std::cout << "This is an demonstrative example of Ultimate Console library" << std::endl;
        std::cout << "Usage: print --word=str -w str" << std::endl;
        exit(0);
    }
};

void printWords(strl_t &words, HelpOption &opt)
{
    for (auto it : words)
        std::cout << it << " ";
    std::cout << std::endl;

    if (words.empty())
        opt.execute();
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    strl_t words;

    try
    {
        UC::dictionary_t dict = UC::createDictionary();

        // you can set as input standard input stream cin,
        // command-line arguments or your own stream
        // uncomment one line below and comment another
        // if you want to change input source

        UC::setInput(dict, std::cin);
        // UC::setInput(dict, argc, argv);

        HelpOption help;

        UC::command_t print = UC::addCommand(dict, "print", 
            UC::callback(&printWords, words, help));

        UC::addOption(print, StringListOption("word", 'w', words));
        UC::addOption(print, help);

        std::cout << "Ultimate Console example: User's Option" 
                  << std::endl;
        std::cout << std::endl;
        std::cout << "Commands: print" 
                  << std::endl;
        std::cout << "Options: word(w), help" 
                  << std::endl;
        std::cout << std::endl;
        std::cout << "Usage: command [option]" 
                  << std::endl;
        std::cout << " -w, --word=VALUE word to be printed" 
                  << std::endl;
        std::cout << "     --help       print help and terminate" 
                  << std::endl;
        std::cout << std::endl;

        std::cout << "> ";

        UC::run(dict);
    }
    catch (UC::component_error const& e)
    {
        // UC::component_error provides error messages 
        // like pair "error code - word" it's done so 
        // that you can override your own error messages
        // or call standart UC::printError

        // uncomment the line below and line #include in
        // the beginning of this file to try standart
        // error printing function

        // UC::printError(e);

        std::cout << "Ultimate Console: component_error: " <<
            e.code() << " what: " << e.what() << std::endl;
    }

    return 0;
}