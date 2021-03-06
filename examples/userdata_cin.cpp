/**
    @file userdata_cin.cpp
    @brief This example demonstrates commands, options and arguments of
    Ultimate Console
*/

#include <iostream>
#include <memory>

#include <ulticon.hpp>

/*
    Include optional headers of ultimate console. You can not
    include them, if you don't wanna use classes and functions,
    which them provide.
*/

// void printError(const UC::component_error &e)
#include <ulticon/printerror.hpp>

// options
#include <ulticon/stringoption.hpp>
#include <ulticon/booloption.hpp>
#include <ulticon/intoption.hpp>
#include <ulticon/callbackoption.hpp>

// arguments
#include <ulticon/stringargument.hpp>
#include <ulticon/intargument.hpp>
//#include <ulticon/boolargument.hpp>

// example class
struct UserData
{
    void printUserData()
    {
        using std::cout;
        using std::endl;
        cout << endl;
        cout << "Print Userdata values" << endl;
        cout << "This is the test class made for ulticon library demonstration" << endl;

        cout << endl;
        cout << "strValue  = " << strValue << endl;
        cout << "intValue  = " << intValue << endl;

        cout << std::boolalpha;
        cout << "boolValue = " << boolValue << endl;

        cout << std::noboolalpha;
        cout << "strArg    = " << strArg << endl;
        cout << "intArg    = " << intArg << endl;
        cout << endl;
    }

    void help()
    {
        using std::cout;
        using std::endl;

        cout << endl;
        cout << "Using: userdata [ key [key value] ] [ option = [option value] ] [args...]" << endl;
        cout << "This is the test command userdata for ulticon library demonstration" << endl;

        cout << endl;
        cout << "Arguments required by options, required by corresponding keys too." << endl;
        cout << "In the start of a key sequence must be '-', in the start of an option must be '--'" << endl;
        cout << "\t-s --string      string option" << endl;
        cout << "\t-i --int         int option" << endl;
        cout << "\t-b --bool        bool option" << endl;
        cout << "\t-h --help        callback option (calls Userdata::help)" << endl;
        cout << endl;
    }

    std::string strValue;
    int intValue = 0;
    bool boolValue = false;

    std::string strArg;
    int intArg = 0;
};

int main(int, char**)
{
    using namespace std;

    UserData ud;

    try
    {
        // first of all create dictionary
        UC::dictionary_t d0 = UC::createDictionary();

        // specify the input; in this example we're gonna get data from standard input
        UC::setInput(d0, cin);

        // create the command with name "userdata" and attach it to dictionary
        // UC::callback allows you to pass class method
        UC::command_t comd = UC::addCommand(d0, "userdata", 
            UC::callback(ud, &UserData::printUserData));

        // adding options
        UC::addOption(comd, 
            UC::StringOption("string", 's', ud.strValue));
        UC::addOption(comd,
            UC::IntOption("int", 'i', ud.intValue));
        UC::addOption(comd,
            UC::BoolOption("bool", 'b', ud.boolValue));
        UC::addOption(comd,
            UC::CallbackOption("help", 'h', UC::callback(ud, &UserData::help)));
        
        // adding arguments
        UC::addArgument(comd, UC::StringArgument(ud.strArg));
        UC::addArgument(comd, UC::IntArgument(ud.intArg));

        std::cout << "Ultimate Console example: Userdata" << std::endl;
        std::cout << std::endl;
        std::cout << "Usage: userdata [OPTION]... [STRING ARGUMENT]"
                     " [INT ARGUMENT]" 
                  << std::endl;
        std::cout << " -s, --string=VAL" << std::endl;
        std::cout << " -i, --int=VAL"    << std::endl;
        std::cout << " -b, --bool"       << std::endl;
        std::cout << " -h, --help"       << std::endl;
        std::cout << std::endl;

        cout << "Enter the command: ";
        // this is the main function - it gets data from input source, disassemblies it
        // finds names in lists and executes it
        UC::run(d0);
    }
    catch (runtime_error &e)
    {
        cout << "runtime_error: " << e.what() << endl;
    }
    catch (logic_error &e)
    {
        cout << "logic_error: " << e.what() << endl;
    }
    catch (UC::component_error &e)
    {
        // UC::component_error provides error messages like pair "error code - word"
        // it's done so that you can override your own error messages or call standart UC::printError
        UC::printError(e);
    }

    cout << "End. Press any key to quit" << endl;
    cin.clear();
    cin.get();

    return 0;
}