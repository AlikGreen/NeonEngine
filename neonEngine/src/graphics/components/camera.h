#pragma once
#include <tiny_gltf.h>

#include "asset/assetRef.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "graphics/frustum.h"
#include "graphics/materialShader.h"

namespace Neon
{
struct Camera
{
public:
    bool matchWindowSize = true;
    glm::vec4 bgColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    void setWidth(uint32_t width);
    [[nodiscard]] uint32_t getWidth() const;

    void setHeight(uint32_t height);
    [[nodiscard]] uint32_t getHeight() const;

    void setFov(float fov);
    [[nodiscard]] float getFov() const;

    void setNear(float near);
    [[nodiscard]] float getNear() const;

    void setFar(float far);
    [[nodiscard]] float getFar() const;

    Frustum getFrustum(const glm::mat4 &view);
    [[nodiscard]] const glm::mat4& getProjectionMatrix();

    void setSkyboxMaterial(AssetRef<MaterialShader> material);
    [[nodiscard]] AssetRef<MaterialShader> getSkyboxMaterial() const;

    Rc<RHI::Framebuffer> getFramebuffer();
    Rc<RHI::TextureView> getDepthTexture();
    Rc<RHI::TextureView> getColorTexture();
private:
    float fov = 60.0f;
    float nearClip = 0.1f;
    float farClip = 1000.0f;

    uint32_t width  = 1;
    uint32_t height = 1;

    bool projectionDirty = true;
    bool fbDirty = true;

    glm::mat4 projectionMatrix{};
    glm::mat4 viewMatrix{};

    Frustum frustum{};

    Rc<RHI::Framebuffer> framebuffer;
    Rc<RHI::TextureView> colorView;
    Rc<RHI::TextureView> depthView;

    AssetRef<MaterialShader> skyboxMaterial;

    void updateProjectionMatrix();
    void updateFramebuffer();
};
}
