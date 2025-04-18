#pragma once

#include "../core/system.h"
#include "backend/graphicsPipeline.h"
#include "backend/physicalDevice.h"
#include "backend/window.h"


namespace Neon
{
    struct Vertex
    {
        glm::vec2 position;
        glm::vec3 color;
    };

    template<typename T>
    class VertexBuffer;

    class RenderSystem final : public System
    {
    public:
        explicit RenderSystem(const WindowOptions &windowOptions);

        void startup() override;
        void shutdown() override;
        void render() override;

        [[nodiscard]] PhysicalDevice* getDevice() const;
        [[nodiscard]] Window* getWindow() const;
    private:
        Window* window = nullptr;
        PhysicalDevice* physicalDevice = nullptr;
        GraphicsPipeline* pipeline = nullptr;
        VertexBuffer<Vertex>* vertexBuffer = nullptr;
    };
}
