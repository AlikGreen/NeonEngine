#pragma once

#include "core/event.h"


namespace Neon
{
class TextInputEvent final : public Event
{
public:
    explicit TextInputEvent(const char* text) : text(text) { };

    [[nodiscard]] const char* getText() const { return text; }
private:
    const char* text;
};
}
