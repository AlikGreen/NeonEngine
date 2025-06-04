#pragma once
#include "graphics/api/window.h"
#include <SDL3/SDL.h>

namespace Neon
{
class WindowOGL final : public Window
{
public:
    explicit WindowOGL(const WindowCreationOptions& creationOptions);
    Ref<Device> createDevice() override;

    void run() override;
    void close() override;
    void pollEvents() override;

    uint32_t getWidth() override;
    uint32_t getHeight() override;
    glm::ivec2 getSize() override;

    void setWidth(uint32_t width) override;
    void setHeight(uint32_t height) override;
    void setSize(glm::ivec2 size) override;

    std::string getTitle() override;
    void setTitle(std::string title) override;

    void swapBuffers() const;
private:
    WindowCreationOptions creationOptions;
    SDL_Window* handle{};
};
}
