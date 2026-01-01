#include "camera.h"

#include "core/engine.h"
#include "graphics/graphicsSystem.h"


namespace Neon
{

    void Camera::setWidth(const uint32_t width)
    {
        if(this->width == width) return;

        this->width = width;
        projectionDirty = true;
        fbDirty = true;
    }

    uint32_t Camera::getWidth() const
    {
        return width;
    }

    void Camera::setHeight(const uint32_t height)
    {
        if(this->height == height) return;

        this->height = height;
        projectionDirty = true;
        fbDirty = true;
    }

    uint32_t Camera::getHeight() const
    {
        return height;
    }

    void Camera::setFov(const float fov)
    {
        if(this->fov == fov) return;

        this->fov = fov;
        projectionDirty = true;
    }

    float Camera::getFov() const
    {
        return fov;
    }

    void Camera::setNear(const float near)
    {
        if(nearClip == near) return;

        nearClip = near;
        projectionDirty = true;
    }

    float Camera::getNear() const
    {
        return nearClip;
    }

    void Camera::setFar(const float far)
    {
        if(farClip == far) return;

        farClip = far;
        projectionDirty = true;

    }

    float Camera::getFar() const
    {
        return farClip;
    }

    Frustum Camera::getFrustum(const glm::mat4 &view)
    {
        if(projectionDirty || view != this->viewMatrix)
        {
            this->viewMatrix = view;
            updateProjectionMatrix();
        }

        return frustum;
    }


    const glm::mat4 & Camera::getProjectionMatrix()
    {
        if (projectionDirty)
        {
            updateProjectionMatrix();
        }
        return projectionMatrix;
    }

    void Camera::setSkyboxMaterial(const AssetRef<MaterialShader> material)
    {
        skyboxMaterial = material;
    }

    AssetRef<MaterialShader> Camera::getSkyboxMaterial() const
    {
        return skyboxMaterial;
    }

    Rc<RHI::Framebuffer> Camera::getFramebuffer()
    {
        if(fbDirty)
        {
            updateFramebuffer();
            fbDirty = false;
        }

        return framebuffer;
    }

    Rc<RHI::TextureView> Camera::getDepthTexture()
    {
        return depthView;
    }

    Rc<RHI::TextureView> Camera::getColorTexture()
    {
        return colorView;
    }

    void Camera::updateProjectionMatrix()
    {
        float aspectRatio = 1.0f;
        if(width != 0 && height != 0)
        {
            aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        }
        projectionMatrix = glm::perspective(
            glm::radians(fov),
            aspectRatio,
            nearClip,
            farClip
        );

        frustum.update(projectionMatrix, viewMatrix);

        projectionDirty = false;
    }

    void Camera::updateFramebuffer()
    {
        const Rc<RHI::Device> device = Engine::getSystem<GraphicsSystem>()->getDevice();

        const RHI::TextureDescription depthDesc = RHI::TextureDescription::Texture2D(
                width,
                height,
                RHI::PixelFormat::D32FloatS8Uint,
                RHI::TextureUsage::DepthStencilTarget);

        const Rc<RHI::Texture> depthTex = device->createTexture(depthDesc);

        const auto depthViewDesc = RHI::TextureViewDescription(depthTex);
        depthView = device->createTextureView(depthViewDesc);

        const RHI::TextureDescription colDesc = RHI::TextureDescription::Texture2D(
                width,
                height,
                RHI::PixelFormat::R8G8B8A8Unorm,
                RHI::TextureUsage::ColorTarget);

        const Rc<RHI::Texture> colTex = device->createTexture(colDesc);

        const auto colViewDesc = RHI::TextureViewDescription(colTex);
        colorView = device->createTextureView(colViewDesc);

        const auto fbDesc = RHI::FramebufferDescription(depthView, colorView);
        framebuffer = device->createFramebuffer(fbDesc);
    }
}
