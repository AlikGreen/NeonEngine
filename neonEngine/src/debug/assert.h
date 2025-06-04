#pragma once
#include <source_location>
#include <format>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "assertAction.h"
#include "logger.h"

namespace Neon
{
class Assert
{
public:
    static AssertAction assertAction;

    // Simple check with message only
    static void check(
        bool condition,
        const std::string& message = "",
        const std::source_location& location = std::source_location::current());

    // Templated check with format string and arguments (auto-captures location)
    template<typename... Args>
    static void check(const bool condition, const std::string& format, Args&&... args,
                     const std::source_location& location = std::source_location::current())
    {
        check_impl(condition, format, location, std::forward<Args>(args)...);
    }

private:
    // Private implementation that does the actual work
    template<typename... Args>
    static void check_impl(const bool condition, const std::string& format,
                          const std::source_location& location, Args&&... args)
    {
        if (condition) return;

        std::string message;
        if constexpr (sizeof...(args) > 0)
        {
            message = std::vformat(format, std::make_format_args(args...));
        }
        else
        {
            message = format;
        }

        const std::string fullMessage = message + "\n" +
                                        "  Function:  " + location.function_name() + "\n" +
                                        "  File:      " + location.file_name() + "\n" +
                                        "  Line:      " + std::to_string(location.line());

        Logger::fatal("ASSERTION FAILED", fullMessage);

        switch (assertAction)
        {
            case AssertAction::LogAndThrow:
                throw std::runtime_error(fullMessage);
            case AssertAction::LogAndAbort:
                std::abort();
            case AssertAction::LogOnly:
                break;
        }
    }
};
}