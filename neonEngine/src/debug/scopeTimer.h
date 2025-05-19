#pragma once

namespace Neon
{
    class ScopeTimer
    {
    private:
        std::string name;

    public:
        explicit ScopeTimer(std::string  timerName);
        ~ScopeTimer();
    };
}
