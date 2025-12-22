#pragma once
#include "imGuiWindow.h"

namespace Neon
{
class StatsWindow final : public ImGuiWindow
{
public:
    explicit StatsWindow();

    void render() override;
};
}
