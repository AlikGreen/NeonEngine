#pragma once
#include "imGuiWindow.h"

#include <neonLog/neonLog.h>

namespace Neon
{
class ConsoleWindow final : public ImGuiWindow, public Log::Stream
{
public:
    explicit ConsoleWindow();

    void render() override;
    void handle(std::string formatted, std::string raw, Level level) override;
private:
    std::vector<std::pair<std::string, Level>> messages;
};
}
