/**
    @file callback.hpp
    @brief Callback function wrappers header
*/

#pragma once

namespace UC
{
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
} // namespace uc
