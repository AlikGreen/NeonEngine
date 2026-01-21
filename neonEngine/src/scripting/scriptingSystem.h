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
            DWORD error = GetLastError();
            Log::error("Failed to find function '{}' - Error: {}", name, error);
            return nullptr;
        }

        Log::info("Found function '{}' at address: {:p}", name, (void*)rawAddr);

        FunctionPtr funcPtr = reinterpret_cast<FunctionPtr>(rawAddr);
        return std::function<Res(ArgTypes...)>(funcPtr);
    }

    HMODULE m_scriptLib = nullptr;

    std::function<void()> m_vFnUpdate = nullptr;
};
}
