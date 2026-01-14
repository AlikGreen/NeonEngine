#pragma once
#include "device.h"
#include "core/components/transformComponent.h"
#include "graphics/image.h"
#include "graphics/components/camera.h"

namespace Neon::Editor
{
class GameWindow
{
public:
    void init();
    void render();
private:
    void renderBillboards(const Transform& camTransform, Camera& camera);

    Rc<RHI::Device> m_device;
    Rc<RHI::Pipeline> m_pipeline;

    Rc<RHI::Buffer> m_uniformBuffer;

    Rc<RHI::Sampler> m_gizmoSampler;
    Rc<RHI::TextureView> m_lightTextureView{};
};
}
