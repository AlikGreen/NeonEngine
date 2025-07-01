#pragma once
#include <exception>
#include <string>

namespace Neon
{
class AssertionException final : public std::exception
{
public:
    explicit AssertionException(const char* message) : message(message) {  }

    [[nodiscard]] const char* what() const noexcept override
    {
        return ("ASSERTION FAILED\n"+message).c_str();
    }
private:
    std::string message{};
};
}
