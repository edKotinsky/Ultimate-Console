/**
    @file indata.hpp
    @brief Wrapper for std::istream and command-line arguments
*/

#pragma once

#include <istream>

#include "argw.hpp"

namespace UC
{
    class input_data
    {
    public:
        input_data(std::istream &inputStream);
        input_data(char **argv, int argc);

        input_data() = delete;
        ~input_data() = default;

        input_data(const input_data&) = delete;
        input_data(input_data&&) = default;
        input_data& operator=(input_data const&) = delete;
        input_data& operator=(input_data&&) = delete;

        void get(char &ch);
        int peek();
        void putback(char ch);
        bool eof();

    private:
        std::istream *istr;
        ucargw::argv_wrapper args;
    };
}