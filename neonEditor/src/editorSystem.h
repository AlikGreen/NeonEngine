#pragma once
#include "core/system.h"

namespace Neon::Editor
{
    class EditorSystem final : public Neon::System
    {
    public:
        void startup() override;
        void update() override;
        void event(Neon::Event *event) override;
    };
}