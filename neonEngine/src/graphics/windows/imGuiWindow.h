#pragma once
#include <string>
#include <utility>

namespace Neon
{
class ImGuiWindow
{
public:
    virtual ~ImGuiWindow() = default;
    explicit ImGuiWindow(std::string name) : name(std::move(name)) {};

    virtual void render() = 0;

    std::string getName() { return this->name; }

    bool open = true;
protected:
    std::string name;
};
}
