#pragma once
#include <string>
#include <utility>

namespace Neon
{
class Window
{
public:
    virtual ~Window() = default;
    explicit Window(std::string name) : name(std::move(name)) {};

    virtual void render() = 0;

    std::string getName() { return this->name; }
    [[nodiscard]] bool isOpen() const { return this->m_open; }
    void close() { m_open = false; }
    void open() { m_open = true; }
protected:
    std::string name;
private:
    bool m_open = false;
};
}
