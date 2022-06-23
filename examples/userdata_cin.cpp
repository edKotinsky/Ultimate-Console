#include "interface.hpp"
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

        UC::StringOption option1("string", 's', ud.strValue);
        UC::IntOption    option2("int", 'i', ud.intValue);
        UC::BoolOption   option3("bool", 'b', ud.boolValue);
        UC::CallbackOption  help("help", 
            UC::callback(ud, &UserData::help));

        UC::StringArgument arg1(ud.strArg);
        UC::IntArgument    arg2(ud.intArg);

        UC::addOption(comd, option1);
        UC::addOption(comd, option2);
        UC::addOption(comd, option3);
        UC::addOption(comd, help);

        UC::addArgument(comd, arg1);
        UC::addArgument(comd, arg2);
        
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