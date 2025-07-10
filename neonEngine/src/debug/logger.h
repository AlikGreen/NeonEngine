#pragma once
#include <string>
#include <mutex>
#include <format>
#include <chrono>


namespace Neon
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error,
    };

    class Logger
    {
    public:
        static void log(LogLevel level, const std::string& message);

        template<typename... Args>
        static void info(const std::string& fmt, const Args&... args)
        {
            // now args are lvalues and bind to make_format_args
            auto fmtArgs = std::make_format_args(args...);
            log(LogLevel::Info,
                std::vformat(fmt, fmtArgs));
        }

        template<typename... Args>
        static void warning(const std::string& fmt, const Args&... args)
        {
            // now args are lvalues and bind to make_format_args
            auto fmtArgs = std::make_format_args(args...);
            log(LogLevel::Warning,
                std::vformat(fmt, fmtArgs));
        }

        template<typename... Args>
        static void error(const std::string& fmt, const Args&... args)
        {
            // now args are lvalues and bind to make_format_args
            auto fmtArgs = std::make_format_args(args...);
            log(LogLevel::Error,
                std::vformat(fmt, fmtArgs));
        }
    };
}