#include "consoleWindow.h"

#include <imgui.h>
#include <neonLog/neonLog.h>

namespace Neon
{
    ConsoleWindow::ConsoleWindow()
        : ImGuiWindow("Console"), Stream(Level::Trace)
    {
        addStream(this);
    }

    void ConsoleWindow::render()
    {
        std::optional<size_t> pendingDeleteIndex;

        for (size_t i = 0; i < messages.size(); ++i)
        {
            const auto& [msg, level] = messages[i];

            ImGui::PushID(static_cast<int>(i));

            ImGui::Selectable(msg.c_str());

            if (ImGui::BeginPopupContextItem("MessageContext"))
            {
                if (ImGui::MenuItem("Copy"))
                {
                    ImGui::SetClipboardText(msg.c_str());
                }

                if (ImGui::MenuItem("Delete"))
                {
                    pendingDeleteIndex = i;
                }

                ImGui::EndPopup();
            }

            ImGui::PopID();
        }

        if (pendingDeleteIndex.has_value())
        {
            messages.erase(messages.begin() + static_cast<std::ptrdiff_t>(*pendingDeleteIndex));
        }
    }


    void ConsoleWindow::handle(std::string formatted, std::string raw, Level level)
    {
        messages.emplace_back(raw, level);
    }
}
