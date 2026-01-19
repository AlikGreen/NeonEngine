#pragma once
#include <functional>

#include "core/system.h"
#include <windows.h>

#include "log.h"

namespace Neon
{
class ScriptingSystem final : public System
{
public:
    void startup() override;
    void update() override;
    void shutdown() override;
private:
    template<typename Res, typename... ArgTypes>
    std::function<Res(ArgTypes...)> getFunction(const char* name)
    {
        using FunctionPtr = Res(*)(ArgTypes...);

        FARPROC rawAddr = GetProcAddress(m_scriptLib, name);

        if (rawAddr == nullptr)
        {
            Log::error("Failed to find function '{}'", name);
            return nullptr;
        }

        return reinterpret_cast<FunctionPtr>(rawAddr);
    }

    HMODULE m_scriptLib = nullptr;

    std::function<void()> m_vFnUpdate = nullptr;
};
}
