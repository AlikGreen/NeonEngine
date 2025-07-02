#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <ctime>

namespace Neon
{
    void Logger::log(const LogLevel level, const std::string &message)
    {
        const std::time_t now = std::time(nullptr);
        const std::tm* tm = std::localtime(&now);

        std::stringstream ss;
        ss << "[" << std::put_time(tm, "%d-%m-%Y %H:%M:%S") << "] ";

        switch (level)
        {
            case LogLevel::Info:    ss << "[INFO] "; break;
            case LogLevel::Warning: ss << "[WARNING] "; break;
            case LogLevel::Error:   ss << "[ERROR] "; break;
        }

        ss << message;

        std::cout << ss.str() << "\n";
    }
}