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

        const char* formattedMessage = format(message, args...);

        throw AssertionException(formattedMessage);
    }
private:
    template<typename T>
    static std::string toString(const T& v)
    {
        std::ostringstream oss;
        oss << v;
        return oss.str();
    }

    template<typename... Args>
    static const char* format(const char* message, Args... args)
    {
        thread_local std::string buf;
        buf = message;

        (void)std::initializer_list<int>
        {
            ( [&]()
            {
                auto p = buf.find("{}");
                if (p != std::string::npos)
                    buf.replace(p, 2, toString(args));
            }(), 0 )...
        };

        return buf.c_str();
    }
};
}