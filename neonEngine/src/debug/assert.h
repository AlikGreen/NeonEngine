#pragma once

#include <source_location>

#include "assertionException.h"


namespace Neon
{
class Assert
{
public:
    template <typename... Args>
    static void check(const bool condition, const char* message, Args... args)
    {
        if(condition) return;
        if constexpr (sizeof...(args) == 0)
            throw AssertionException(message);
        else
        {
            const std::string formattedMessage = std::vformat(message, std::make_format_args(args...));
            throw AssertionException(formattedMessage.c_str());
        }
    }
};
}