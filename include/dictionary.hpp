/**
    @file dictionary.hpp
    @brief Dictionary
*/

#pragma once

#include "uccmd.hpp"
#include "indata.hpp"
#include "variable.hpp"

namespace UC
{
    enum class dictionary_state
    {
        running,
        stopped,
        end_of_file,
        error
    };

    class Dictionary
    {
    public:
        Dictionary() 
        { st = dictionary_state::running; }

        ~Dictionary() = default;

        Dictionary(const Dictionary &) = delete;

        void setInput(std::unique_ptr<input_data> inputData)
        { input = std::move(inputData); }

        inline void addCommand(std::shared_ptr<Command> &command)
        { cmds.addCommand(command); }

        inline void addVariable(std::shared_ptr<Variable> &variable)
        { vars.addCommand(variable); }

        inline void run()
        { _run(); }

        inline void stop()
        { st = dictionary_state::stopped; }
        
        inline void reset()
        { st = dictionary_state::running; }

        dictionary_state state()
        { return st; }

    private:
        void _run();

        std::unique_ptr<input_data> input;
        std::string grtng;
        dictionary_state st = dictionary_state::stopped;
        uccmd::CommandList<Command> cmds;
        uccmd::CommandList<Variable> vars;
    };
}