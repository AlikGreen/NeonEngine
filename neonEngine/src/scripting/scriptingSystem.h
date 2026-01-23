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
    template<typename Res, typename... Args>
    std::function<Res(Args...)> loadFunction(const char* symbolName)
    {
        using FunctionPtr = Res(*)(Args...);

        FARPROC rawAddr = GetProcAddress(m_runtimeHandle, symbolName);

        if (rawAddr == nullptr)
        {
            DWORD error = GetLastError();
            Log::error("Failed to find function '{}' - Error: {}", symbolName, error);
            return nullptr;
        }

        Log::info("Found function '{}' at address: {:p}", symbolName, reinterpret_cast<void*>(rawAddr));

        auto funcPtr = reinterpret_cast<FunctionPtr>(rawAddr);
        return std::function<Res(Args...)>(funcPtr);
    }

    HMODULE m_runtimeHandle = nullptr;

    std::function<void()> m_updateCallback = nullptr;
};
}
