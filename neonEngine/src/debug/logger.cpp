#include "logger.h"

namespace Neon
{
    bool Logger::consoleOutput = true;
    LogLevel Logger::minLevel = LogLevel::INFO;

    std::mutex Logger::mutex;
    // should open file in init and close in shutdown
    std::ofstream Logger::logFile;
    std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> Logger::timers;


    void Logger::setLogLevel(const LogLevel level)
    {
        minLevel = level;
    }

    void Logger::setConsoleOutput(const bool enabled)
    {
        consoleOutput = enabled;
    }

    void Logger::log(const LogLevel level, const std::string &component, const std::string &message)
    {
        if (level < minLevel) return;

        std::lock_guard lock(mutex);

        const std::time_t now = std::time(nullptr);
        const std::tm* tm = std::localtime(&now);

        std::stringstream ss;
        ss << "[" << std::put_time(tm, "%d-%m-%Y %H:%M:%S") << "] ";

        switch (level)
        {
            case LogLevel::TRACE:   ss << "[TRACE] "; break;
            case LogLevel::DEBUG:   ss << "[DEBUG] "; break;
            case LogLevel::INFO:    ss << "[INFO] "; break;
            case LogLevel::WARNING: ss << "[WARNING] "; break;
            case LogLevel::ERROR:   ss << "[ERROR] "; break;
            case LogLevel::FATAL:   ss << "[FATAL] "; break;
        }

        ss << "[" << component << "] " << message;

        if (logFile.is_open()) {
            logFile << ss.str() << "\n";
            logFile.flush();
        }

        if (consoleOutput) {
            std::cout << ss.str() << "\n";
        }
    }

    void Logger::trace(const std::string &component, const std::string &message)
    {
        log(LogLevel::TRACE, component, message);
    }

    void Logger::debug(const std::string &component, const std::string &message)
    {
        log(LogLevel::DEBUG, component, message);
    }

    void Logger::info(const std::string &component, const std::string &message)
    {
        log(LogLevel::INFO, component, message);
    }

    void Logger::warning(const std::string &component, const std::string &message)
    {
        log(LogLevel::WARNING, component, message);
    }

    void Logger::error(const std::string &component, const std::string &message)
    {
        log(LogLevel::ERROR, component, message);
    }

    void Logger::fatal(const std::string &component, const std::string &message)
    {
        log(LogLevel::FATAL, component, message);
    }

    void Logger::startTimer(const std::string &name)
    {
        timers[name] = std::chrono::high_resolution_clock::now();
    }

    float Logger::endTimer(const std::string &name, const bool logResult)
    {
        const auto endTime = std::chrono::high_resolution_clock::now();

        if (!timers.contains(name)) {
            warning("Profiler", "Attempted to end timer '" + name + "' that wasn't started");
            return 0.0f;
        }

        const auto startTime = timers[name];
        const double duration = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()) / 1000.0;

        if (logResult)
        {
            debug("Profiler", name + " took " + std::to_string(duration) + " ms");
        }

        timers.erase(name);
        return static_cast<float>(duration);
    }
}
