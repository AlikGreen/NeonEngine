#pragma once
#include "core/event.h"

namespace Neon
{
    class DropFileEvent final : public Event
    {
    public:
        explicit DropFileEvent(const char* path) : path(path) { };

        [[nodiscard]] const char* getPath() const { return path; }
    private:
        const char* path;
    };
}
