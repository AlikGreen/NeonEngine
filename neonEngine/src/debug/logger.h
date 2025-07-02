#pragma once
#include <string>
#include <mutex>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <sstream>

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
        static void info(const std::string& format_str, Args&&... args)
        {
            info(LogLevel::Info, std::vformat(format_str, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void warning(const std::string& format_str, Args&&... args)
        {
            log(LogLevel::Warning, std::vformat(format_str, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void error(const std::string& format_str, Args&&... args)
        {
            log(LogLevel::Error, std::vformat(format_str, std::forward<Args>(args)...));
        }
    };
}