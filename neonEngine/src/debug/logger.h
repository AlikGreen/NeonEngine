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
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class Logger
    {
    private:
        static std::mutex mutex;
        static std::ofstream logFile;
        static LogLevel minLevel;
        static bool consoleOutput;

        // Performance metrics
        static std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> timers;

        // Helper function to format strings with {} placeholders
        template<typename... Args>
        static std::string format(const std::string& format_str, Args&&... args)
        {
            std::string result = format_str;
            std::stringstream ss;

            // Pack arguments into stringstream
            ((ss << std::forward<Args>(args)), ...);
            std::string packed_args = ss.str();

            // Simple implementation - replace {} with arguments in order
            size_t arg_index = 0;
            size_t pos = 0;
            ss.str("");
            ss.clear();
            ((ss << std::forward<Args>(args) << '\0'), ...);
            std::string all_args = ss.str();

            // More robust approach using fold expression
            auto replace_next = [&](const auto& arg) {
                size_t found = result.find("{}", pos);
                if (found != std::string::npos) {
                    std::stringstream arg_ss;
                    arg_ss << arg;
                    result.replace(found, 2, arg_ss.str());
                    pos = found + arg_ss.str().length();
                }
            };

            (replace_next(args), ...);
            return result;
        }

    public:
        static void setLogLevel(LogLevel level);
        static void setConsoleOutput(bool enabled);

        static void log(LogLevel level, const std::string& component, const std::string& message);

        // Convenience methods with format support
        static void trace(const std::string& component, const std::string& message);
        static void debug(const std::string& component, const std::string& message);
        static void info(const std::string& component, const std::string& message);
        static void warning(const std::string& component, const std::string& message);
        static void error(const std::string& component, const std::string& message);
        static void fatal(const std::string& component, const std::string& message);

        // Template versions with format support
        template<typename... Args>
        static void trace(const std::string& component, const std::string& format_str, Args&&... args)
        {
            trace(component, format(format_str, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void debug(const std::string& component, const std::string& format_str, Args&&... args)
        {
            debug(component, format(format_str, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void info(const std::string& component, const std::string& format_str, Args&&... args)
        {
            info(component, format(format_str, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void warning(const std::string& component, const std::string& format_str, Args&&... args)
        {
            warning(component, format(format_str, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void error(const std::string& component, const std::string& format_str, Args&&... args)
        {
            error(component, format(format_str, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void fatal(const std::string& component, const std::string& format_str, Args&&... args)
        {
            fatal(component, format(format_str, std::forward<Args>(args)...));
        }

        // Performance tracking
        static void startTimer(const std::string& name);
        static float endTimer(const std::string& name, bool logResult = true);
    };
}