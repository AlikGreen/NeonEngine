#pragma once
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace Neon
{
struct Camera
{
public:
    bool autoAspectRatio = true;
    glm::vec4 bgColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    void setAspectRatio(const float ratio)
    {
        if(aspectRatio != ratio)
        {
            aspectRatio = ratio;
            projectionDirty = true;
        }
    }

    [[nodiscard]] float getAspectRatio() const
    {
        return aspectRatio;
    }

    void setFov(const float fov)
    {
        if(this->fov != fov)
        {
            this->fov = fov;
            projectionDirty = true;
        }
    }

    [[nodiscard]] float getFov() const
    {
        return fov;
    }

    void setNear(const float near)
    {
        if(nearClip != near)
        {
            nearClip = near;
            projectionDirty = true;
        }
    }

    [[nodiscard]] float getNear() const
    {
        return nearClip;
    }

    void setFar(const float far)
    {
        if(farClip != far)
        {
            farClip = far;
            projectionDirty = true;
        }
    }

    [[nodiscard]] float getFar() const
    {
        return farClip;
    }

    [[nodiscard]] const glm::mat4& getProjectionMatrix()
    {
        if (projectionDirty)
        {
            updateProjectionMatrix();
        }
        return projectionMatrix;
    }
private:
    float aspectRatio = 16.0f/9.0f;

    float fov = 60.0f;
    float nearClip = 0.1f;
    float farClip = 1000.0f;

    bool projectionDirty = true;
    glm::mat4 projectionMatrix{};

    void updateProjectionMatrix()
    {
        projectionMatrix = glm::perspective(
            glm::radians(fov),
            aspectRatio,
            nearClip,
            farClip
        );
        projectionDirty = false;
    }
};
}
