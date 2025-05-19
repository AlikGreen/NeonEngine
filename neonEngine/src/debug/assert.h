#pragma once
#include <source_location>

#include "assertAction.h"

namespace Neon
{
class Assert
{
public:
    static AssertAction assertAction;
    static void check(
        bool condition,
        const std::string& message = "",
        const std::source_location& location = std::source_location::current());
};
}
