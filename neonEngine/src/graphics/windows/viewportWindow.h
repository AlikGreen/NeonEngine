#pragma once
#include "imGuiWindow.h"

namespace Neon
{
class ViewportWindow final : public ImGuiWindow
{
public:
    explicit ViewportWindow();

    void render() override;
};
}
