#include "scopeTimer.h"

#include <utility>

#include "logger.h"

namespace Neon
{
    ScopeTimer::ScopeTimer(std::string timerName) : name(std::move(timerName))
    {
        Logger::startTimer(name);
    }

    ScopeTimer::~ScopeTimer()
    {
        Logger::endTimer(name);
    }
}
