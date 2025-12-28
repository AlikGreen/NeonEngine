#pragma once
#include <utility>

#include "core/event.h"

namespace Neon
{
    class DropFileEvent final : public Event
    {
    public:
        explicit DropFileEvent(std::string path) : path(std::move(path)) { };

        [[nodiscard]] std::string getPath() const { return path; }
    private:
        std::string path;
    };
}
