#pragma once

namespace Neon
{
    struct Component
    {

    };

    template <class T>
    concept DerivesComponent = std::is_base_of_v<Component, T>;
}