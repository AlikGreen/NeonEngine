#pragma once
#include <chrono>
#include <fstream>

#include "logLevel.h"

namespace Neon
{
class Logger
{
private:
    static std::mutex mutex;

    static std::ofstream logFile;
    static LogLevel minLevel;
    static bool consoleOutput;

    // Performance metrics
    static std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> timers;
public:
    static void setLogLevel(LogLevel level);
    static void setConsoleOutput(bool enabled);

    static void log(LogLevel level, const std::string& component, const std::string& message);

    // Convenience methods
    static void trace(const std::string& component, const std::string& message);
    static void debug(const std::string& component, const std::string& message);
    static void info(const std::string& component, const std::string& message);
    static void warning(const std::string& component, const std::string& message);
    static void error(const std::string& component, const std::string& message);
    static void fatal(const std::string& component, const std::string& message);

    // Performance tracking
    static void startTimer(const std::string& name);
    static float endTimer(const std::string& name, bool logResult = true);
};
}
