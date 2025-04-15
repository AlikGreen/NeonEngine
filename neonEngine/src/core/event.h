#pragma once

namespace Neon
{
    class Event
    {
    public:
        virtual ~Event() = default;

        void cancel()
        {
            canceled = true;
        }

        [[nodiscard]] bool isCanceled() const
        {
            return canceled;
        }
    private:
        bool canceled = false;
    };
}