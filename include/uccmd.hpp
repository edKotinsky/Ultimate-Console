#pragma once

#include "command.hpp"
#include "variable.hpp"
#include "ucerr.hpp"

#include <memory>

namespace uccmd
{
    template <class T>
    class CommandList
    {
    public:
        CommandList() = default;

        void addCommand(std::shared_ptr<T> &command)
        {
            if (commandExists(command->getName()))
                throw std::logic_error("Command with such name already exists");
            commands.push_back(command);
        }

        typename std::vector<std::shared_ptr<T>>::iterator 
        getCommand(std::string const &name)
        {
            typename std::vector<std::shared_ptr<T>>::iterator it = commands.begin();
            for (; it != commands.end(); ++it)
                if ((*it)->getName() == name)
                    return it;
            return commands.end();
        }

        typename std::vector<std::shared_ptr<T>>::iterator 
        end()
        {
            return commands.end();
        }

        ~CommandList() = default;
        CommandList(CommandList &) = delete;
        CommandList(CommandList &&) = delete;

    private:
        inline bool commandExists(std::string const &name)
        {
            for (auto it : commands)
                if (it->getName() == name)
                    return true;
            return false;
        }

        std::vector<std::shared_ptr<T>> commands;
    };
}
