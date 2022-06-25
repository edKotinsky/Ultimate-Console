#include <memory>
#include <stdexcept>

#include <ucconf.hpp>
#include "dictionary.hpp"
#include "interface.hpp"

namespace UC
{
    dictionary_t createDictionary()
    {
        return std::make_unique<Dictionary>();
    }

    void setInput(dictionary_t& dictionary, std::istream &inputStream)
    { dictionary->setInput(std::make_unique<input_data>(inputStream)); }

    void setInput(dictionary_t& dictionary, int argCount, char **args)
    { dictionary->setInput(std::make_unique<input_data>(args, argCount)); }

    void showGreeting(dictionary_t& dictionary, bool enable)
    { dictionary->greeting(enable); }

    void setGreeting(dictionary_t& dictionary, std::string greeting)
    { dictionary->addGreeting(greeting); } 

    void addVariable(dictionary_t& dictionary, std::string &&name, Argument &argument)
    { 
        std::shared_ptr<Variable> tmp = std::make_shared<Variable>(name, argument);
        dictionary->addVariable(tmp); 
    }

    std::shared_ptr<Command> addCommand(dictionary_t& dictionary, std::string &&name, std::function<void()> callback)
    { 
        std::shared_ptr<Command> tmp = std::make_shared<Command>(name, callback);
        dictionary->addCommand(tmp);
        return tmp;
    }

    void addOption(command_t command, Option &option)
    { command->addOption(option); }

    void addOption(command_t command, Option &&option)
    {
        command->addOption(option.clone());
    }

    void addArgument(command_t command, Argument &argument)
    { command->addArgument(argument); }

    void addArgument(command_t command, Argument &&argument)
    {
        command->addArgument(argument.clone());
    }

    dictionary_state run(dictionary_t& dictionary) 
    {
        dictionary->run();
        return dictionary->state();
    }

} // namespace UC