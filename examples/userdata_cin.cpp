#include "argument.hpp"
#include "callback.hpp"
#include "interface.hpp"
#include "option.hpp"
#include <iostream>
#include <memory>
// #include <ucconf.hpp>

#include <ulticon.hpp>

struct UserData
{
    void printUserData()
    {
        using std::cout;
        using std::endl;
        cout << endl;
        cout << "Print Userdata values" << endl;
        cout << "This is the test class made for ulticon library demonstration" << endl;
        cout << "Ultimate Console v" << ULTICON_VERSION << endl;

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
        cout << "Ultimate Console v" << ULTICON_VERSION << endl;

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
        UC::dictionary_t d0 = UC::createDictionary();
        UC::setInput(d0, cin);

        UC::showGreeting(d0, true);
        UC::setGreeting(d0, "Enter the command: ");

        UC::command_t comd = UC::addCommand(d0, "userdata", 
            UC::callback(ud, &UserData::printUserData));

        UC::addOption(comd, 
            UC::StringOption("string", 's', ud.strValue));
        UC::addOption(comd,
            UC::IntOption("int", 'i', ud.intValue));
        UC::addOption(comd,
            UC::BoolOption("bool", 'b', ud.boolValue));
        UC::addOption(comd,
            UC::CallbackOption("help", 'h', UC::callback(ud, &UserData::help)));
        
        UC::addArgument(comd, UC::StringArgument(ud.strArg));
        UC::addArgument(comd, UC::IntArgument(ud.intArg));

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
        UC::printError(e);
    }

    cout << "End. Press any key to quit" << endl;
    cin.clear();
    cin.get();

    return 0;
}