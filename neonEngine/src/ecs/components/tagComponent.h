#pragma once
#include <string>
#include <utility>
#include <vector>

namespace Neon
{
    struct Tag
    {
        explicit Tag(std::string name) : name(std::move(name)) { };
        std::string name{};
        std::vector<std::string> tags{};
    };
}
